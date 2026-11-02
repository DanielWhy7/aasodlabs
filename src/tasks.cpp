module tasks;

import std;
import linked_list;

linked_list<int> merge_sorted_unique(const linked_list<int> &first,
                                     const linked_list<int> &second) {
  linked_list<int> result;
  std::size_t i = 0;
  std::size_t j = 0;
  bool has_last = false;
  int last_value = 0;

  while (i < first.size() || j < second.size()) {
    int candidate;
    if (j >= second.size())
      candidate = first[i++];
    else if (i >= first.size())
      candidate = second[j++];
    else if (first[i] <= second[j])
      candidate = first[i++];
    else
      candidate = second[j++];

    if (!has_last || candidate != last_value) {
      result.push_tail(candidate);
      last_value = candidate;
      has_last = true;
    }
  }

  contract_assert(result.size() <= first.size() + second.size());
  return result;
}

/* ---- Tower of Hanoi (advanced task 3) -------------------------------- */

static void print_disk_field(unsigned int value, bool has_disk) {
  unsigned int printed;
  if (has_disk) {
    std::cout << '[' << value << ']';
    printed = 3;
    unsigned int v = value;
    while (v >= 10) {
      v /= 10;
      ++printed;
    }
  } else {
    std::cout << "[ ]";
    printed = 3;
  }
  for (unsigned int k = printed; k < 13; ++k)
    std::cout << ' ';
}

static void print_rod_cell(const linked_list<unsigned int> &rod,
                           unsigned int level) {
  unsigned int n = static_cast<unsigned int>(rod.size());
  if (level > n)
    print_disk_field(0, false);
  else
    print_disk_field(rod[n - level], true);
}

static void print_state(const linked_list<unsigned int> (&rods)[3],
                        unsigned int total) {
  std::cout << "A            B            C\n";
  std::cout << "============================\n";
  for (unsigned int level = total; level > 0; --level) {
    print_rod_cell(rods[0], level);
    print_rod_cell(rods[1], level);
    print_rod_cell(rods[2], level);
    std::cout << '\n';
  }
}

static void hanoi_recursive(linked_list<unsigned int> (&rods)[3],
                            unsigned int n, unsigned int from, unsigned int to,
                            unsigned int via, unsigned int &move_num,
                            unsigned int total) {
  if (n == 0)
    return;

  hanoi_recursive(rods, n - 1, from, via, to, move_num, total);

  unsigned int disk = rods[from][0];
  rods[from].pop_head();
  rods[to].push_head(disk);
  ++move_num;

  std::cout << "\nMove " << move_num << ": "
            << static_cast<char>('A' + from) << " -> "
            << static_cast<char>('A' + to) << "\n";
  print_state(rods, total);

  hanoi_recursive(rods, n - 1, via, to, from, move_num, total);
}

void hanoi(unsigned int disk_count) {
  if (disk_count == 0)
    return;

  linked_list<unsigned int> rods[3];

  for (unsigned int d = disk_count; d > 0; --d)
    rods[0].push_head(d);

  unsigned int move_num = 0;
  std::cout << "Initial state:\n";
  print_state(rods, disk_count);

  hanoi_recursive(rods, disk_count, 0, 2, 1, move_num, disk_count);
  std::cout << "\nTotal moves: " << move_num << "\n";
}
