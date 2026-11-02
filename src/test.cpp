import std;
import linked_list;
import tasks;

namespace {

void expect(bool condition, const char *message) {
  if (!condition)
    throw std::runtime_error(message);
}

bool run_one(const char *name, void (*fn)()) {
  try {
    fn();
    std::cout << "  PASS: " << name << '\n';
    return true;
  } catch (const std::exception &e) {
    std::cout << "  FAIL: " << name << " -- " << e.what() << '\n';
    return false;
  }
}

/* ---- individual tests ---------------------------------------------- */

void test_default_constructor() {
  linked_list<int> l;
  expect(l.empty(), "empty() on default-constructed list");
  expect(l.size() == 0, "size() == 0 on default-constructed list");
}

void test_random_fill_constructor() {
  linked_list<int> l(10, 42u, 1, 100);
  expect(l.size() == 10, "random-fill produces requested count");
  for (std::size_t i = 0; i < l.size(); ++i)
    expect(l[i] >= 1 && l[i] <= 100, "random values in [1, 100]");
}

void test_push_tail_push_head() {
  linked_list<int> l;
  l.push_tail(1);
  l.push_tail(2);
  l.push_tail(3);
  expect(l.size() == 3, "size after 3 push_tail");
  expect(l[0] == 1 && l[1] == 2 && l[2] == 3, "contents after push_tail");

  l.push_head(0);
  expect(l.size() == 4, "size after push_head");
  expect(l[0] == 0 && l[1] == 1 && l[2] == 2 && l[3] == 3,
         "contents after push_head");
}

void test_modulo_indexing() {
  linked_list<int> l;
  l.push_tail(10);
  l.push_tail(20);
  l.push_tail(30);
  expect(l[3] == 10, "index 3 wraps to element 0");
  expect(l[4] == 20, "index 4 wraps to element 1");
  expect(l[100] == l[100 % 3], "large index equals modulo result");
}

void test_empty_index_throws() {
  linked_list<int> l;
  bool threw = false;
  try {
    (void) l[0];
  } catch (const std::out_of_range &) {
    threw = true;
  }
  expect(threw, "operator[] on empty list throws std::out_of_range");
}

void test_copy_constructor() {
  linked_list<int> a;
  a.push_tail(1);
  a.push_tail(2);
  linked_list<int> b(a);
  expect(b.size() == 2, "copy has same size");
  expect(b[0] == 1 && b[1] == 2, "copy has same contents");

  a.push_tail(3);
  expect(b.size() == 2, "copy is independent of source");
}

void test_assignment() {
  linked_list<int> a;
  a.push_tail(1);
  a.push_tail(2);
  linked_list<int> b;
  b = a;
  expect(b.size() == 2 && b[0] == 1 && b[1] == 2,
         "assignment copies contents");

  b = b;
  expect(b.size() == 2, "self-assignment preserves contents");
}

void test_pop_head() {
  linked_list<int> l;
  l.push_tail(1);
  l.push_tail(2);
  l.pop_head();
  expect(l.size() == 1 && l[0] == 2, "pop_head removes first");
  l.pop_head();
  expect(l.empty(), "pop_head on single-element list empties it");

  bool threw = false;
  try {
    l.pop_head();
  } catch (const std::out_of_range &) {
    threw = true;
  }
  expect(threw, "pop_head on empty list throws");
}

void test_pop_tail() {
  linked_list<int> l;
  l.push_tail(1);
  l.push_tail(2);
  l.push_tail(3);
  l.pop_tail();
  expect(l.size() == 2 && l[0] == 1 && l[1] == 2, "pop_tail removes last");
  l.pop_tail();
  l.pop_tail();
  expect(l.empty(), "repeated pop_tail empties list");

  bool threw = false;
  try {
    l.pop_tail();
  } catch (const std::out_of_range &) {
    threw = true;
  }
  expect(threw, "pop_tail on empty list throws");
}

void test_delete_node() {
  linked_list<int> l;
  l.push_tail(1);
  l.push_tail(2);
  l.push_tail(1);
  l.push_tail(3);
  l.push_tail(1);
  l.delete_node(1);
  expect(l.size() == 2, "delete_node removes all matches");
  expect(l[0] == 2 && l[1] == 3, "remaining order preserved");

  l.delete_node(99);
  expect(l.size() == 2, "delete_node on absent value is a no-op");

  l.delete_node(2);
  l.delete_node(3);
  expect(l.empty(), "delete_node can empty the list");
}

void test_push_tail_list() {
  linked_list<int> a;
  a.push_tail(1);
  a.push_tail(2);
  linked_list<int> b;
  b.push_tail(3);
  b.push_tail(4);
  a.push_tail(b);
  expect(a.size() == 4, "push_tail(list) size");
  expect(a[0] == 1 && a[1] == 2 && a[2] == 3 && a[3] == 4,
         "push_tail(list) order");
  expect(b.size() == 2, "push_tail(list) does not consume source");
}

void test_push_head_list() {
  linked_list<int> a;
  a.push_tail(3);
  a.push_tail(4);
  linked_list<int> b;
  b.push_tail(1);
  b.push_tail(2);
  a.push_head(b);
  expect(a.size() == 4, "push_head(list) size");
  expect(a[0] == 1 && a[1] == 2 && a[2] == 3 && a[3] == 4,
         "push_head(list) order");
}

void test_merge_sorted_unique() {
  linked_list<int> a;
  int av[] = {1, 3, 5, 7};
  for (int v : av)
    a.push_tail(v);

  linked_list<int> b;
  int bv[] = {2, 3, 4, 5, 8};
  for (int v : bv)
    b.push_tail(v);

  linked_list<int> m = merge_sorted_unique(a, b);
  int exp[] = {1, 2, 3, 4, 5, 7, 8};
  std::size_t exp_n = sizeof(exp) / sizeof(exp[0]);
  expect(m.size() == exp_n, "merge size");
  for (std::size_t i = 0; i < exp_n; ++i)
    expect(m[i] == exp[i], "merge element");
}

void test_merge_with_empty() {
  linked_list<int> empty;
  linked_list<int> b;
  b.push_tail(1);
  b.push_tail(2);
  linked_list<int> m = merge_sorted_unique(empty, b);
  expect(m.size() == 2 && m[0] == 1 && m[1] == 2,
         "merge with empty left list");
}

void test_merge_both_empty() {
  linked_list<int> a;
  linked_list<int> b;
  linked_list<int> m = merge_sorted_unique(a, b);
  expect(m.empty(), "merge of two empty lists is empty");
}

void test_merge_collapses_duplicates_in_one_input() {
  linked_list<int> a;
  int av[] = {1, 1, 2, 2, 3};
  for (int v : av)
    a.push_tail(v);

  linked_list<int> b;
  linked_list<int> m = merge_sorted_unique(a, b);
  expect(m.size() == 3, "duplicates collapsed within single input");
  expect(m[0] == 1 && m[1] == 2 && m[2] == 3, "deduplicated contents");
}

void test_hanoi_zero_is_noop() {
  hanoi(0u); /* must print nothing and not crash */
  expect(true, "hanoi(0) is a no-op");
}

}  // namespace

int main() {
  std::cout << "=== Automated tests ===\n";
  bool all_ok = true;
  all_ok &= run_one("default constructor", test_default_constructor);
  all_ok &= run_one("random fill constructor", test_random_fill_constructor);
  all_ok &= run_one("push_tail / push_head", test_push_tail_push_head);
  all_ok &= run_one("modulo indexing", test_modulo_indexing);
  all_ok &= run_one("empty index throws", test_empty_index_throws);
  all_ok &= run_one("copy constructor", test_copy_constructor);
  all_ok &= run_one("assignment", test_assignment);
  all_ok &= run_one("pop_head", test_pop_head);
  all_ok &= run_one("pop_tail", test_pop_tail);
  all_ok &= run_one("delete_node", test_delete_node);
  all_ok &= run_one("push_tail(list)", test_push_tail_list);
  all_ok &= run_one("push_head(list)", test_push_head_list);
  all_ok &= run_one("merge_sorted_unique", test_merge_sorted_unique);
  all_ok &= run_one("merge with empty", test_merge_with_empty);
  all_ok &= run_one("merge both empty", test_merge_both_empty);
  all_ok &= run_one("merge collapses duplicates",
                    test_merge_collapses_duplicates_in_one_input);
  all_ok &= run_one("hanoi(0) is a no-op", test_hanoi_zero_is_noop);

  std::cout << "=== "
            << (all_ok ? "All tests passed" : "Some tests FAILED")
            << " ===\n";
  return all_ok ? 0 : 1;
}
