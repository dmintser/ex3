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
  bool pushBack(const Node<T> &element);
  T front();
  void popFront(); // we should change it later to return a referernce to the
                   // head of the updated Queue
  int size() const;

private:
  Node<T> *m_queue;
  int m_size;
};

template <class T> Queue<T>::Queue() : m_queue(new Node<T>) {
  m_queue->next = nullptr;
}

template <class T> Queue<T> filter(const Queue<T> &);

template <class T> Queue<T> transform(const Queue<T> &);

// iterators

template <class T> Queue<T>::~Queue() {
  while (m_queue) {
    Node<T> *to_delete = m_queue;
    m_queue = m_queue->next;
    delete to_delete;
  }
}

#endif
