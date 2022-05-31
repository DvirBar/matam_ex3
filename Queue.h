#ifndef MATAM_EX3_QUEUE_H
#define MATAM_EX3_QUEUE_H

#include <new>
#include <assert.h>

// TODO: Make it generic when finished testing
template<class T>
class Queue {
public:
    /**
     *  Constructor of Queue class.
     */
    Queue();
    
    /**
     *  Adds a new node with a value to the end of the queue.
     *
     *  @param value - the value to be inserted.
     */
    void pushBack(const T& value);
    
    /**
     *  Removes the first node of the queue.
     */
    void popFront();

    /**
     *  @return
     *      A reference to the first value in the queue.
     */
    T& front();

    const T& front() const;

    /**
     *  @return
     *      The size of the queue.
     */
    int size() const;
    
    
    class Iterator;
    
    Iterator begin();
    Iterator end();
    
    class ConstIterator;
    
    ConstIterator begin() const;
    ConstIterator end() const;
    
    ~Queue();

    Queue(const Queue& queue);
    Queue& operator=(const Queue& queue);
    /**
    *  A class for EmptyQueue exception.
    *
    *  Thrown when an invalid operation is executed on an iterator that
    *  points to the end of the queue.
    */
    class EmptyQueue {};
    
private:
    class QNode {
    public:
        T m_data;
        QNode* m_next;
        
        /**
         *  Constructor of QNode class.
         *
         *  @param data - a reference to data
         */
        QNode(const T& data);
        
        QNode(const QNode&) = default;
        QNode& operator=(const QNode&) = default;
    };

    QNode* m_front;
    QNode* m_back;
    int m_size;

    void emptyQueue();
    void copyQueue(const Queue& queue, Queue& newQueue);
    bool isEmpty() const;
};

template<class T>
class Queue<T>::Iterator {
public:
    /**
     *  Asterisk operator overloading.
     *
     *  @return
     *      The value the of the node the iterator currently points to.
     */
    T& operator*() const;
    
    /**
     *  Righthand side increment operator overloading.
     *
     *  Changes the node the iterator points to, to the next one.
     *
     *  @return
     *      A reference to the Iterator (which now points to the next node).
     */
    Iterator& operator++();
    
    /**
     *  Lefthand side increment operator overloading.
     *
     *  Changes the node the iterator points to, to the next one.
     *
     *  @return
     *      A copy of the last pointed to Iterator
     */
    Iterator operator++(int);
    
    /**
     *  Not equal operator overloading.
     *
     *  Checks if two iterators not point to the same node.
     *
     *  @return
     *      True if iterators are not equal.
     */
    const bool operator!=(Iterator iterator) const;
    
    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;
    
    /**
     *  A class for InvalidOperation exception.
     *
     *  Thrown when an invalid operation is executed on an iterator that
     *  points to the end of the queue.
     */
    class InvalidOperation {};
    
private:
    QNode* m_currentNode;
    
    Iterator(Queue* queue, QNode* node);
    
    friend class Queue;
};

template<class T>
class Queue<T>::ConstIterator {
public:
    const T& operator*() const;

    ConstIterator& operator++();
   
    ConstIterator operator++(int);

    const bool operator!=(ConstIterator iterator) const;
    
    ConstIterator(const ConstIterator&) = default;
    ConstIterator& operator=(const ConstIterator&) = default;
  
    class InvalidOperation {};
    
private:
    QNode* m_currentNode;
    
    ConstIterator(const Queue* queue, QNode* node);
    
    friend class Queue;
};


template<class TransformFunction, class T>
void transform(Queue<T>& queue, TransformFunction transform);

template<class T>
Queue<T>::Queue():
    m_front(nullptr),
    m_back(nullptr),
    m_size(0)
{}

template<class T>
void Queue<T>::pushBack(const T& value) {
    Queue::QNode *newNode = new Queue::QNode(value);
    
    if(m_front == nullptr) {
        m_front = newNode;
    }
    
    if(m_back != nullptr) {
        m_back->m_next = newNode;
    }
    
    m_back = newNode;
    m_size++;
}

template<class T>
void Queue<T>::popFront() {
    if(this->isEmpty()) {
        throw EmptyQueue();
    }
    
    if(m_front == m_back) {
        m_back = nullptr;
    }
    
    Queue::QNode* temp = m_front;
    m_front = m_front->m_next;
    
    delete temp;
    m_size--;
}

template<class T>
T& Queue<T>::front() {
    if(this->isEmpty()) {
        throw EmptyQueue();
    }
    
    return m_front->m_data;
}

template<class T>
const T& Queue<T>::front() const {
    if(this->isEmpty()) {
        throw EmptyQueue();
    }

    return m_front->m_data;
}

template<class T>
typename Queue<T>::Iterator Queue<T>::begin() {
    return Queue::Iterator(this, m_front);
}

template<class T>
typename Queue<T>::Iterator Queue<T>::end() {
    if(m_back == nullptr) {
        return Queue::Iterator(this, m_back);
    }
    
    return Queue::Iterator(this, m_back->m_next);
}

template<class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const {
    return Queue::ConstIterator(this, m_front);
}

template<class T>
typename Queue<T>::ConstIterator Queue<T>::end() const {
    if(m_back == nullptr) {
        return Queue::ConstIterator(this, m_back);
    }
    
    return Queue::ConstIterator(this, m_back->m_next);
}

template<class T>
int Queue<T>::size() const {
    return m_size;
}

template<class T>
void Queue<T>::copyQueue(const Queue& queue, Queue& newQueue) {
    assert(newQueue.isEmpty());
    
    try {
        for(const int& queueElement : queue) {
            newQueue.pushBack(queueElement);
        }
    }
    catch(const std::bad_alloc& e) {
        newQueue.emptyQueue();
        throw e;
    }
}

template<class T>
Queue<T>::Queue(const Queue& queue):
    m_front(nullptr),
    m_back(nullptr),
    m_size(0)
{
    copyQueue(queue, *this);
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& queue) {
    if(this == &queue) {
        return *this;
    }
    
    this->emptyQueue();
    copyQueue(queue, *this);
    
    return *this;
}

template<class T>
Queue<T>::~Queue() {
    emptyQueue();
}

template<class T>
void Queue<T>::emptyQueue() {
    while(m_front != nullptr) {
        popFront();
    }
}

template<class T>
bool Queue<T>::isEmpty() const {
    return m_size == 0;
}

template<class T>
Queue<T>::QNode::QNode(const T& data):
    m_data(data),
    m_next(nullptr)
{}

template<class T>
T& Queue<T>::Iterator::operator*() const {
    // TODO: Is it the correct exception?
    if(m_currentNode == nullptr) {
        throw InvalidOperation();
    }
    
    return m_currentNode->m_data;
}

template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++() {
    if(m_currentNode == nullptr) {
        throw InvalidOperation();
    }
    
    m_currentNode = m_currentNode->m_next;
    return *this;
}

template<class T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator++(int) {
    Iterator oldIterator = *this;
    ++*this;
    return oldIterator;
}

template<class T>
const bool Queue<T>::Iterator::operator!=(Iterator iterator) const {
    return this->m_currentNode != iterator.m_currentNode;
}

template<class T>
Queue<T>::Iterator::Iterator(Queue* queue, QNode* node):
//    m_queue(queue),
    m_currentNode(node)
{}

template<class T>
const T& Queue<T>::ConstIterator::operator*() const {
    // TODO: Is it the correct exception?
    if(m_currentNode == nullptr) {
        throw InvalidOperation();
    }
    
    return m_currentNode->m_data;
}

template<class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++() {
    if(m_currentNode == nullptr) {
        throw InvalidOperation();
    }
    
    m_currentNode = m_currentNode->m_next;
    return *this;
}

template<class T>
typename Queue<T>::ConstIterator Queue<T>::ConstIterator::operator++(int) {
    if(m_currentNode == nullptr) {
        throw InvalidOperation();
    }
    
    ConstIterator oldIterator = *this;
    ++*this;
    return oldIterator;
}

template<class T>
const bool Queue<T>::ConstIterator::operator!=(ConstIterator iterator) const {
    return this->m_currentNode != iterator.m_currentNode;
}

template<class T>
Queue<T>::ConstIterator::ConstIterator(const Queue* queue, QNode* node):
    m_currentNode(node)
{}


template<class TransformFunction, class T>
void transform(Queue<T>& queue, TransformFunction transformFunction) {
    for(int& queueElement : queue) {
        transformFunction(queueElement);
    }
}

template<class FilterFunction, class T>
Queue<T> filter(const Queue<T>& queue, FilterFunction filterFunction) {
    Queue<T> newQueue;
    
    for(const int& queueElement : queue) {
        if(filterFunction(queueElement)) {
            newQueue.pushBack(queueElement);
        }
    }
    
    return newQueue;
}


#endif //MATAM_EX3_QUEUE_H
