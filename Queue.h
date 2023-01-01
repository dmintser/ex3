#ifndef Queue_H
#define Queue_H

template <class T> class Node {
public:
  T m_value;
  Node<T> *m_next;
};

template <class T> class Queue {
public:
  Queue();
  ~Queue();
  Queue &pushBack(const T &val);
  T &front();
  Queue &popFront();
  int size() const;

  template <class Condition> Queue filter(Condition c) const;

  class Iterator;
  Iterator begin() const;
  Iterator end() const;

private:
  Node<T> *m_queue;
  int m_size;
};

template <class T> Queue<T> filter(const Queue<T> &);

template <class T> Queue<T> transform(const Queue<T> &, T (*transformation)(T));

// iterators

// Queue& Queue::pushBack(const T &val);

template <class T> typename Queue<T>::Iterator Queue<T>::begin() const {
  return Iterator(this, this->m_queue);
}

template <class T> typename Queue<T>::Iterator Queue<T>::end() const {
  Node<T> *ptr = m_queue;
  while (ptr->m_next) {
    ptr = ptr->m_next;
  }
  return Iterator(this, ptr);
}

template <class T> class Queue<T>::Iterator {
  const Queue<T> *m_queue;
  Node<T> *m_node;
  Iterator(const Queue<T> queue, Node<T> *node);
  friend class Queue<T>;

public:
  const T &operator*() const;
  Iterator &operator++();
  bool operator!=(const Iterator &iterator) const;
};
template <class T> Queue<T>::Queue() : m_queue(new Node<T>), m_size(0) {
  m_queue->next = nullptr;
}

template <class T> Queue<T>::~Queue() {
  while (m_queue) {
    Node<T> *to_delete = m_queue;
    m_queue = m_queue->next;
    delete to_delete;
  }
}

template <class T>
Queue<T>::Iterator::Iterator(const Queue<T> queue, Node<T> *node)
    : m_queue(queue), m_node(node) {}

template <class T> const T &Queue<T>::Iterator::operator*() const {
  return m_node->m_value; // replaced node with m_node
}

template <class T>
typename Queue<T>::Iterator &Queue<T>::Iterator::operator++() {
  m_node = m_node->m_next;
  return *this;
}

template <class T>
bool Queue<T>::Iterator::operator!=(const Iterator &i) const {
  return m_node != i.m_node;
}

template <class T> Queue<T> &Queue<T>::pushBack(const T &val) {
  Node<T> *newNode = new Node<T>;
  newNode->m_value = val;
  newNode->m_next = m_queue;
  m_queue = newNode;
  m_size++;
  return *this;
}

template <class T> Queue<T> &Queue<T>::popFront() {
  Node<T> *ptr = new Node<T>;
  while (ptr->m_next->m_next->m_next) {
    ptr = ptr->next;
  }
  Node<T> *to_delete = ptr->m_next;
  ptr->m_next = ptr->m_next->m_next;
  delete to_delete;
  delete ptr;
  return this; // removed *
}

template <class T>
template <class Condition>
Queue<T> Queue<T>::filter(Condition c) const {
  Queue<T> result;
  for (const T &elem : *this)
    if (c(elem))
      result.pushBack(*elem); // replaced *it with *elem
  return result;
}

template <class T> T &Queue<T>::front() {
  Node<T> *ptr = m_queue;
  while (ptr->m_next->m_next) {
    ptr = ptr->m_next;
  }
  return ptr->m_value;
}

template <class T> int Queue<T>::size() const { return m_size; }

template <class T>
Queue<T> transform(const Queue<T> &queue1, T (*transformation)(T)) {
  Node<T> *ptr = queue1.m_queue;
  while (ptr->m_next->m_next) {
    ptr->m_next = transformation(ptr->m_value);
    ptr = ptr->m_next;
  }
}

#endif
