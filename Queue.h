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
  T &front() const;
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

template <class T> 
typename Queue<T>::ConstIterator Queue<T>::end() const
{
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


template <class T> 
class Queue<T>::ConstIterator 
{
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

template <class T> 
Queue<T>::Queue()
{
  Node<T>* newNode;
  try{
    newNode= new Node<T>;
  }
  catch(const std::bad_alloc &e)
  {
    throw;
  }
  newNode->m_next=nullptr;
  m_queue=newNode;
  m_size=0;
}

template <class T>
Queue<T>::Queue(const Queue &queue) 
{
  Node<T>* newNode;
  try{
    newNode=new Node<T>;
  }
  catch(const std::bad_alloc &e)
  {
    throw;
  }
  newNode->m_next=nullptr;
  m_size=0;
  m_queue=newNode;
  try{
    for (const T &elem : queue) {
      pushBack(elem);
    }
  }
  catch (const std::bad_alloc &e){
    this->~Queue();
    throw;
  }
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue &queue)
{
  if(this==&queue)
  {
    return *this;
  }

  Node<T>* ptr = m_queue;
  if(ptr == nullptr){
    throw Queue<T>::EmptyQueue();
  }

  Node<T>* old_queue = m_queue;
  int old_queue_size = m_size;
  try{
    m_queue = new Node<T>;
    m_queue->m_next = nullptr;
    m_size = 0;
  }
  catch(const std::bad_alloc &e){
    m_queue = old_queue;
    m_size = old_queue_size;
    throw;
  }

  try{
    for(const T &elem : queue){
      pushBack(elem);
    }
  }
  catch(const std::bad_alloc &e){
    ptr = m_queue;
    Node<T>* to_delete;
    while(ptr){
      to_delete = ptr;
      ptr = ptr->m_next;
      delete to_delete;
    }    
    m_queue = old_queue;
    m_size = old_queue_size;
    throw;
  }

  ptr = old_queue;
  Node<T>* to_delete;
  while(ptr){
    to_delete = ptr;
    ptr = ptr->m_next;
    delete to_delete;
  }

  return *this;
}


/*template<class T>
Queue<T>& Queue<T>::operator=(const Queue &queue)
{
  if(this==&queue)
  {
    return *this;
  }

  Node<T>* ptr = m_queue;
  if(ptr == nullptr){ //to be checked
    throw Queue<T>::EmptyQueue();
  }

  Queue<T> old= Queue(*this); 
  ptr = m_queue;
  Node<T>* to_delete; 
  while(ptr->m_next)
  {
    to_delete=ptr;
    ptr=ptr->m_next;
    delete to_delete;
    m_size--;
  } 
  try{
    for (const T &elem : queue) 
    {
      pushBack(elem);
    }
  }
  catch (const std::bad_alloc &e)
  {
    while(ptr->m_next)
  {
    to_delete=ptr;
    ptr=ptr->m_next;
    delete to_delete;
    m_size--;
  } 
    m_queue = old.m_queue;
    m_size = old.m_size;
    //old.~Queue();
    throw;
  }
  old.~Queue();
  ptr = old_qeueu;
  Node<T>* to_delete; 
  while(ptr)
  {
    to_delete=ptr;
    ptr=ptr->m_next;
    delete to_delete;
  }  
  
  return *this;
}*/

/*
template<class T>
Queue<T>& Queue<T>::operator=(const Queue &queue)
{
  if(this==&queue)
  {
    return *this;
  }
  Node<T>* newNode;
  try{
    newNode= new Node<T>;
  }
  catch (const std::bad_alloc &e) {
    throw;
  }
  Queue<T>* to_copy;
  to_copy->m_queue = newNode;
  to_copy->m_size = 0;
  newNode->m_next=nullptr;

  try{
    for (const T &elem : queue)
    {
      to_copy->pushBack(elem);
    }
  }catch (const std::bad_alloc &e) {
    to_copy->~Queue();
    throw;
  }


  while(to_copy->m_size)
  {
    to_copy->popFront();
  }
  try{
    for (const T &elem : queue)
    {
      to_copy->pushBack(elem);
    }
  }catch (const std::bad_alloc &e) {
    to_copy->~Queue();
    throw;
  }
  while(m_size)
  {
    popFront();
  }
  try{
    for (const T &elem : *to_copy)
    {
      pushBack(elem);
    }
  }catch (const std::bad_alloc &e) {
    to_copy->~Queue();
    throw;
  }
  if(to_copy)
    to_copy->~Queue();

  

  Node<T>* ptr = m_queue;
  if(ptr == nullptr){ //to be checked
    throw Queue<T>::EmptyQueue();
  }

  Node<T>* old_qeueu = m_queue;
  int old_queue_size = m_size;
  try{
     m_queue = new Node<T>;
     m_queue->m_next = nullptr;
     m_size = 0;
  }
  catch (const std::bad_alloc &e)
  {
    m_queue = old_qeueu;
    m_size = old_queue_size;
    throw;
  }

  try{
    for (const T &elem : queue) 
    {
      pushBack(elem);
    }
  }
  catch (const std::bad_alloc &e)
  {
    ptr = m_queue;
    Node<T>* to_delete; 
    while(ptr)
    {
      to_delete=ptr;
      ptr=ptr->m_next;
      delete to_delete;
    } 
    m_queue = old_qeueu;
    m_size = old_queue_size;
    throw;
  }
  
  ptr = old_qeueu;
  Node<T>* to_delete; 
  while(ptr)
  {
    to_delete=ptr;
    ptr=ptr->m_next;
    delete to_delete;
  } 
  
  return *this;
}*/



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

template <class T> 
Queue<T>& Queue<T>::pushBack(const T &val) {
  Node<T> *newNode;
  try {
    newNode = new Node<T>;
  } catch (const std::bad_alloc &e) {
    //this->~Queue();
    throw;
  }
  if (!m_size) 
  {
    newNode->m_value = val;
    newNode->m_next = m_queue;
    m_queue = newNode;
    m_size++;
  } 
  else 
  {
    Node<T> *ptr = m_queue;
    while (ptr->m_next->m_next) 
    {
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
  try{
    Queue<T> result = Queue<T>();
    for (const T &elem : queue1) {
      if (c(elem)) {
        result.pushBack(elem);
      }
    }
  return result;
  }
  catch (const std::bad_alloc &e)
  {
    throw std::bad_alloc();
  }
}

template <class T, class Condition>
void transform(Queue<T> &queue1, Condition c) {
  for (T &it : queue1) {
    c(it);
  }
}

template <class T> 
T &Queue<T>::front() const 
{
  if (!m_size) {
    throw(Queue<T>::EmptyQueue());
  }
  return m_queue->m_value;
}

template <class T> 
int Queue<T>::size() const 
{ 
  return m_size; 
}

#endif
