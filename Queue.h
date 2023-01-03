#ifndef Queue_H
#define Queue_H

#include <iostream>
#include <new>

template <class T> class Node {
public:
  T m_value;
  Node<T> *m_next;
};

template <class T> class Queue {
public:
  Queue();
  Queue(const Queue &queue);
  Queue &operator=(const Queue &queue);
  ~Queue();
  Queue &pushBack(const T &val);
  T &front();
  Queue &popFront();
  int size() const;

  class Iterator;
  Iterator begin();
  Iterator end();

  class ConstIterator;
  ConstIterator begin() const;
  ConstIterator end() const;

  class EmptyQueue {};

private:
  Node<T> *m_queue;
  int m_size;
};

template <class T> typename Queue<T>::Iterator Queue<T>::begin() {
  return Iterator(this, this->m_queue);
}

template <class T> typename Queue<T>::Iterator Queue<T>::end() {
  Node<T> *ptr = m_queue;
  while (ptr->m_next) {
    ptr = ptr->m_next;
  }
  return Iterator(this, ptr);
}
template <class T> typename Queue<T>::ConstIterator Queue<T>::begin() const {
  return ConstIterator(this, this->m_queue);
}

template <class T> typename Queue<T>::ConstIterator Queue<T>::end() const {
  Node<T> *ptr = m_queue;
  while (ptr->m_next) {
    ptr = ptr->m_next;
  }
  return ConstIterator(this, ptr);
}

template <class T> class Queue<T>::Iterator {
  Queue<T> *m_queue;
  Node<T> *m_node;
  Iterator(Queue<T> *queue, Node<T> *node);
  friend class Queue<T>;

public:
  T &operator*();
  Iterator &operator++();
  bool operator!=(const Iterator &iterator);
  class InvalidOperation {};
};

template <class T> class Queue<T>::ConstIterator {
  const Queue<T> *m_queue;
  Node<T> *m_node;
  ConstIterator(const Queue<T> *queue, Node<T> *node);
  friend class Queue<T>;

public:
  const T &operator*() const;
  ConstIterator &operator++();
  bool operator!=(const ConstIterator &iterator) const;
  class InvalidOperation {};
};

template <class T> Queue<T>::Queue() : m_queue(new Node<T>), m_size(0) {
  m_queue->m_next = nullptr;
}

template <class T>
Queue<T>::Queue(const Queue &queue) : m_queue(new Node<T>), m_size(0) {
  m_queue->m_next = nullptr;
  for (const T &elem : queue) {
    pushBack(elem);
  }
}

template <class T> Queue<T>::~Queue() {
  while (m_queue) {
    Node<T> *to_delete = m_queue;
    m_queue = m_queue->m_next;
    delete to_delete;
  }
}

template <class T>
Queue<T>::Iterator::Iterator(Queue<T> *queue, Node<T> *node)
    : m_queue(queue), m_node(node) {}

template <class T> T &Queue<T>::Iterator::operator*() {
  return m_node->m_value; // replaced node with m_node
}

template <class T>
Queue<T>::ConstIterator::ConstIterator(const Queue<T> *queue, Node<T> *node)
    : m_queue(queue), m_node(node) {}

template <class T> const T &Queue<T>::ConstIterator::operator*() const {
  return m_node->m_value; // replaced node with m_node
}

template <class T>
typename Queue<T>::Iterator &Queue<T>::Iterator::operator++() {
  if (!(*this != m_queue->end()))
    throw(Queue<T>::Iterator::InvalidOperation());
  m_node = m_node->m_next;
  return *this;
}

template <class T>
typename Queue<T>::ConstIterator &Queue<T>::ConstIterator::operator++() {
  if (!(*this != m_queue->end()))
    throw(Queue<T>::ConstIterator::InvalidOperation());
  m_node = m_node->m_next;
  return *this;
}

template <class T> bool Queue<T>::Iterator::operator!=(const Iterator &i) {
  return m_node != i.m_node;
}

template <class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator &i) const {
  return m_node != i.m_node;
}

template <class T> Queue<T> &Queue<T>::pushBack(const T &val) {
  Node<T> *newNode;
  try {
    newNode = new Node<T>;
  } catch (const std::bad_alloc &e) {
    this->~Queue();
    throw;
  }
  if (!m_size) {
    newNode->m_value = val;
    newNode->m_next = m_queue;
    m_queue = newNode;
    m_size++;
  } else {
    Node<T> *ptr = m_queue;
    while (ptr->m_next->m_next) {
      ptr = ptr->m_next;
    }
    newNode->m_value = val;
    newNode->m_next = ptr->m_next;
    ptr->m_next = newNode;
    m_size++;
  }

  return *this;
}

template <class T> Queue<T> &Queue<T>::popFront() {
  if (!m_size) {
    throw(Queue<T>::EmptyQueue());
  }
  Node<T> *to_delete = m_queue;
  m_queue = m_queue->m_next;
  delete to_delete;
  m_size--;
  return *this;
}

template <class T, class Condition>
Queue<T> filter(const Queue<T> &queue1, Condition c) {
  Queue<T> result = Queue<T>();
  for (const T &elem : queue1) {
    if (c(elem)) {
      result.pushBack(elem);
    }
  }
  return result;
}

template <class T, class Condition>
void transform(Queue<T> &queue1, Condition c) {
  for (T &it : queue1) {
    c(it);
  }
}

template <class T> T &Queue<T>::front() {
  if (!m_size) {
    throw(Queue<T>::EmptyQueue());
  }
  return m_queue->m_value;
}

template <class T> int Queue<T>::size() const { return m_size; }

#endif
