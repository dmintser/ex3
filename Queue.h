#ifndef Queue_H
#define Queue_H

template <class T> class Node {
  T m_value;
  T *m_next;
};

template <class T> class Queue {
  Node<T> *head;

public:
  Queue();
  Queue(const T &Queue);
  ~Queue();
  Queue &operator=(const T &Queue);

  bool pushBack(const Node<T> &element);
  T front();
  void popFront(); // we should change it later to return a referernce to the
                   // head of the updated Queue
  int size() const;
};

template <class T> Queue<T>::Queue<T> Queue<T> filter(const T &Queue);

/*class Queue
{
public:
Queue();
~Queue();
private:
    T m_value;
    Queue<T>* m_next;
};

template<class T>
Queue<T>::Queue():
    m_next(NULL)
{}

template<class T>
Queue<T>::~Queue()
{
    while(m_next)
    Queue<T> *to_delete=this;


}*/

#endif
