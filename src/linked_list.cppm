export module linked_list;

import std;

/* A node of the singly linked circular list. */
export template <typename T>
struct node {
  T data;
  node *next;

  explicit node(const T &value) : data(value), next(nullptr) {}
};

export template <typename T>
class linked_list {
public:
  /* Shorthand: inside this class, 'node' alone refers to the template,
     not to a specialization, so spell it out once here. */
  using node_type = node<T>;

  linked_list() : head_(nullptr), tail_(nullptr), size_(0) {
    contract_assert(empty() && head_ == nullptr && tail_ == nullptr);
  }

  linked_list(const linked_list &other)
      : head_(nullptr), tail_(nullptr), size_(0) {
    copy_from(other);
    contract_assert(size_ == other.size_);
  }

  linked_list(std::size_t count, unsigned int seed, T min_value, T max_value)
      requires std::integral<T>
      : head_(nullptr), tail_(nullptr), size_(0) {
    std::mt19937 engine(seed);
    std::uniform_int_distribution<T> dist(min_value, max_value);
    for (std::size_t i = 0; i < count; ++i)
      push_tail(dist(engine));
    contract_assert(size_ == count);
  }

  ~linked_list() { clear(); }

  linked_list &operator=(const linked_list &other) {
    if (this != &other) {
      linked_list tmp(other);
      swap(tmp);
    }
    contract_assert(size_ == other.size_);
    return *this;
  }

  void swap(linked_list &other) {
    node_type *tmp_head = head_;
    head_ = other.head_;
    other.head_ = tmp_head;

    node_type *tmp_tail = tail_;
    tail_ = other.tail_;
    other.tail_ = tmp_tail;

    std::size_t tmp_size = size_;
    size_ = other.size_;
    other.size_ = tmp_size;
  }

  std::size_t size() const { return size_; }
  bool empty() const { return size_ == 0; }

  void push_tail(const T &value) {
    node_type *new_node = new node_type(value);
    if (empty()) {
      head_ = new_node;
      tail_ = new_node;
      new_node->next = new_node;
    } else {
      new_node->next = head_;
      tail_->next = new_node;
      tail_ = new_node;
    }
    ++size_;
    contract_assert(tail_->next == head_);
  }

  void push_tail(const linked_list &other) {
    if (&other == this) {
      linked_list copy(other);
      push_tail(copy);
      return;
    }
    for (std::size_t i = 0; i < other.size_; ++i)
      push_tail(other[i]);
  }

  void push_head(const T &value) {
    node_type *new_node = new node_type(value);
    if (empty()) {
      head_ = new_node;
      tail_ = new_node;
      new_node->next = new_node;
    } else {
      new_node->next = head_;
      tail_->next = new_node;
      head_ = new_node;
    }
    ++size_;
    contract_assert(tail_->next == head_);
  }

  void push_head(const linked_list &other) {
    if (&other == this) {
      linked_list copy(other);
      push_head(copy);
      return;
    }
    for (std::size_t i = other.size_; i > 0; --i)
      push_head(other[i - 1]);
  }

  void pop_head() {
    if (empty())
      throw std::out_of_range("pop_head on empty list");
    if (size_ == 1) {
      delete head_;
      head_ = nullptr;
      tail_ = nullptr;
      size_ = 0;
    } else {
      node_type *old_head = head_;
      head_ = head_->next;
      tail_->next = head_;
      delete old_head;
      --size_;
    }
    contract_assert(empty() || tail_->next == head_);
  }

  void pop_tail() {
    if (empty())
      throw std::out_of_range("pop_tail on empty list");
    if (size_ == 1) {
      delete head_;
      head_ = nullptr;
      tail_ = nullptr;
      size_ = 0;
    } else {
      node_type *prev = head_;
      while (prev->next != tail_)
        prev = prev->next;
      prev->next = head_;
      delete tail_;
      tail_ = prev;
      --size_;
    }
    contract_assert(empty() || tail_->next == head_);
  }

  void delete_node(const T &value) {
    if (empty())
      return;
    node_type *new_head = nullptr;
    node_type *new_tail = nullptr;
    std::size_t kept = 0;
    node_type *current = head_;
    std::size_t original_size = size_;

    for (std::size_t i = 0; i < original_size; ++i) {
      node_type *next_node = current->next;
      if (current->data == value) {
        delete current;
      } else {
        if (new_tail == nullptr)
          new_head = current;
        else
          new_tail->next = current;
        new_tail = current;
        ++kept;
      }
      current = next_node;
    }

    head_ = new_head;
    tail_ = new_tail;
    size_ = kept;
    if (size_ > 0)
      tail_->next = head_;
    contract_assert(empty() || tail_->next == head_);
  }

  T &operator[](std::size_t index) { return at(index)->data; }
  const T &operator[](std::size_t index) const { return at(index)->data; }

private:
  node_type *at(std::size_t index) const {
    if (empty())
      throw std::out_of_range("index on empty list");
    std::size_t real_index = index % size_;
    contract_assert(real_index < size_);
    node_type *current = head_;
    for (std::size_t i = 0; i < real_index; ++i)
      current = current->next;
    return current;
  }

  void clear() {
    if (empty())
      return;
    node_type *current = head_;
    for (std::size_t i = 0; i < size_; ++i) {
      node_type *next_node = current->next;
      delete current;
      current = next_node;
    }
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
  }

  void copy_from(const linked_list &other) {
    for (std::size_t i = 0; i < other.size_; ++i)
      push_tail(other[i]);
    contract_assert(size_ == other.size_);
  }

  node_type *head_;
  node_type *tail_;
  std::size_t size_;
};

export template <typename T>
std::ostream &operator<<(std::ostream &os, const linked_list<T> &list) {
  os << "[";
  for (std::size_t i = 0; i < list.size(); ++i) {
    if (i > 0)
      os << ", ";
    os << list[i];
  }
  os << "]";
  return os;
}
