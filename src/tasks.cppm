export module tasks;

import std;
import linked_list;

/* Basic task 8: merge two ascending sorted lists without duplicates. */
export linked_list<int> merge_sorted_unique(const linked_list<int> &first,
                                            const linked_list<int> &second);

/* Advanced task 3: solve the Tower of Hanoi and print rods as lists. */
export void hanoi(unsigned int disk_count);
