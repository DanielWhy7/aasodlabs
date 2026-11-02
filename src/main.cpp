import std;
import linked_list;
import tasks;
using std::size_t;

static linked_list<int> read_sorted_list (const char *prompt){
  linked_list<int> list;
  std::cout << prompt;
  size_t count;
  std::cin >> count;
  for (size_t i = 0; i < count; ++i)
    {
      int value;
      std::cin >> value;
      list.push_tail (value);
    }
  return list;
}

int main (){
  std::cout << "Task 8: merging two sorted lists without duplicates\n";
  linked_list<int> list_a
      = read_sorted_list ("Enter first list (count then values): ");
  linked_list<int> list_b
      = read_sorted_list ("Enter second list (count then values): ");

  linked_list<int> merged = merge_sorted_unique (list_a, list_b);
  std::cout << "Merged: " << merged << "\n\n";

  std::cout << "Task 3: Tower of Hanoi\n";
  std::cout << "Enter number of disks: ";
  unsigned int disks;
  std::cin >> disks;
  hanoi (disks);

  return 0;
}
