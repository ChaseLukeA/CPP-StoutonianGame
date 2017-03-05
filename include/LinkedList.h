// ---------------------------------------------------------------------------
//
//                   University of Wisconsin-Stout
//            Mathematics, Statistics & Computer Science
//                 CS-244 Data Structures - Fall 2016
//
// This software is student work for CSS-244 Data Structures and may not
// be copied except by the original author and instructor.
// Copyright 2016
//
// <filename>
//
// <class description>
//
// Instructor: Jocelyn Richardt
// Assignment: StoutonianGame
// Author: Luke A Chase
// Date: 03/01/2017
//
// ---------------------------------------------------------------------------

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#ifndef null
#define null 0
#endif

#include <iostream>

using namespace std;

// LinkedList Declarations
//------------------------------------------------------------------------------------------------//
template <class T>
class LinkedList
{
    private:
        class Node
        {
            public:
                Node(T element = 0, Node *next = null) : m_Element(element), m_Next(next) {}

                T m_Element;
                Node* m_Next;
        };

        Node* m_Head;
        Node* m_Tail;

        const LinkedList& operator =(const LinkedList& nodes);

    public:
        class Iterator
        {
            public:
                Iterator(Node* node) : m_CurrentNode(node) {}

                T operator *() { return m_CurrentNode->m_Element; }

                Iterator& operator ++()
                {
                    m_CurrentNode = m_CurrentNode->m_Next;
                    return *this;
                }

                Iterator operator ++(int)
                {
                    Iterator iter = *this;
                    m_CurrentNode = m_CurrentNode->m_Next;
                    return iter;
                }

                bool operator ==(const Iterator& rightSide) const { return (m_CurrentNode == rightSide.m_CurrentNode); }

                bool operator !=(const Iterator& rightSide) const { return (m_CurrentNode != rightSide.m_CurrentNode); }

            private:
                Iterator() {}

                Node* m_CurrentNode;
        };

        LinkedList() : m_Head(null), m_Tail(null) {}
        LinkedList(LinkedList& nodes);
        virtual ~LinkedList();

        bool addFirst(const T &element);
        bool addLast(const T &element);
        bool addBefore(const T &element, int position);
        bool addAfter(const T &element, int position);
        bool removeFirst();
        bool removeLast();
        bool removeAt(int position);

        Iterator begin() { return Iterator(m_Head); }
        Iterator end() { return Iterator(null); }

        int getSize();
        bool isEmpty() const { return m_Head == null; }
        void print();
};

// LinkedList Definitions
//------------------------------------------------------------------------------------------------//
// Constructor that makes a deep copy of the specified LinkedList
template<class T>
inline LinkedList<T>::LinkedList(LinkedList& nodes) : m_Head(null), m_Tail(null)
{
    if (nodes.isEmpty()) return;

    Node* original = nodes.m_Head;
    Node* copyOfOriginal = new Node(original->m_Element, null);

    m_Head = copyOfOriginal;
    m_Tail = copyOfOriginal;

    while (original->m_Next)
    {
        original = original->m_Next;

        Node* newcopyOfOriginal;
        newcopyOfOriginal = new Node(original->m_Element, null);

        copyOfOriginal->m_Next = newcopyOfOriginal;
        m_Tail = newcopyOfOriginal;
        copyOfOriginal = copyOfOriginal->m_Next;
    }
}

// Destructor removes all nodes
template<class T>
inline LinkedList<T>::~LinkedList()
{
    while (!isEmpty()) removeFirst();
}

// Add a node to the beginning of the list
template<class T>
inline bool LinkedList<T>::addFirst(const T &element)
{
    Node *newHead = new Node(element, null);

    if (!m_Head)
    {
        m_Tail = newHead;
        newHead->m_Next = null;
    }
    else
    {
        newHead->m_Next = m_Head;
    }
    m_Head = newHead;

    return true;
}

// Add a node to the end of the list
template<class T>
inline bool LinkedList<T>::addLast(const T &element)
{
    Node *newTail = new Node(element, null);

    if (m_Tail) m_Tail->m_Next = newTail;

    if (!m_Head) m_Head = newTail;

    m_Tail = newTail;

    return true;
}

// Add a node before the specified position
template<class T>
inline bool LinkedList<T>::addBefore(const T &element, int position)
{
    if (position < 0) return false;
    if (position == 0) this->addFirst(element);
    if (position >= getSize()) return false;

    Node *newElement = new Node(element, null);

    Node* current = m_Head;
    Node* previous = current;
    int currentPosition = 1;

    while (current->m_Next && currentPosition < position)
    {
        previous = current;
        current = current->m_Next;
        currentPosition++;
    }

    newElement->m_Next = current->m_Next;

    current->m_Next = newElement;

    return true;
}

// Add a node after the specified position
template<class T>
inline bool LinkedList<T>::addAfter(const T &element, int position)
{
    if (position < 0) return false;

    if (position >= getSize()) { this->addLast(element); return true; }

    Node *newElement = new Node(element, null);

    Node* current = m_Head;
    Node* previous = current;
    int currentPosition = 0;

    while (current->m_Next && currentPosition < position) {
        previous = current;
        current = current->m_Next;
        currentPosition++;
    }

    newElement->m_Next = current->m_Next;

    current->m_Next = newElement;

    return true;
}

// Remove first node from the list
template<class T>
inline bool LinkedList<T>::removeFirst()
{
    if (isEmpty()) return false;

    Node* newFirst = m_Head->m_Next;
    delete m_Head;
    m_Head = newFirst;

    return true;
}

// Remove last node from the list
template<class T>
inline bool LinkedList<T>::removeLast()
{
    if (isEmpty()) return false;

    Node* current = m_Head;
    Node* previous = current;

    while (current->m_Next)
    {
        previous = current;
        current = current->m_Next;
    }

    if (current == previous) m_Head = null;

    delete current;

    m_Tail = previous;

    previous->m_Next = null;

    return true;
}

// Remove node at specified position
template<class T>
inline bool LinkedList<T>::removeAt(int position)
{
    if (position < 0 || isEmpty()) return false;

    if (position == 0) { this->removeFirst(); return true; }

    if (position >= getSize()) return false;

    Node* current = m_Head;
    Node* previous = current;
    int currentPosition = 0;

    while (current->m_Next && currentPosition < position)
    {
        previous = current;
        current = current->m_Next;
        currentPosition++;
    }

    if (current == m_Tail) { this->removeLast(); return true; }

    previous->m_Next = current->m_Next;

    delete current;

    return true;
}

// Get the number of elements in the LinkedList
template<class T>
inline int LinkedList<T>::getSize()
{
    int numberOfElements = 0;

    Node* element = m_Head;

    while (element)
    {
        ++numberOfElements;
        element = element->m_Next;
    }

    return numberOfElements;
}

// Print the entire list of nodes
template<class T>
inline void LinkedList<T>::print()
{
    if (isEmpty()) { cout << "The list is empty." << endl; return; }

    Node* current = m_Head;

    while (current->m_Next)
    {
        cout << current->m_Element << endl;
        current = current->m_Next;
    }
    cout << current->m_Element << endl;
}

#endif // LINKEDLIST_H
