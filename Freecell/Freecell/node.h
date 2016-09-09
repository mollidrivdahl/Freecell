/**********************************************************************
* Author:			Molli Drivdahl
* Filename:			node.h
* Date Created:		1/6/16
* Modifications:	1/24/16
*
* Class: Node
*
* Purpose:
*	This class simulates a node of a linked list.
*
* Manager functions:
*	Node()
*		Creates a Node with the next and previous pointers set to
*		nullptr.
*
*	Node(T data)
*		Creates a Node with the next and previous pointers set to
*		nullptr, and the data set to the value of the parameter.
*
*	Node(const Node<T> & copy)
*
*	~Node()
*
*	Node<T> & operator=(const Node<T> & rhs)
**********************************************************************/
#ifndef NODE_H
#define NODE_H

//Node Class
template <typename T>
class Node
{
private:
	//LinkedList is a friend class to Node
	template <typename T>
	friend class LinkedList;

	//Default Ctor
	Node();

	//1-Arg Overloaded Ctor
	Node(T data);

	//Copy Ctor
	Node(const Node<T> & copy);

	//Default Dtor
	~Node();

	//Assignment Operator
	Node<T> & operator=(const Node<T> & rhs);

	//Data Members
	T m_data;				//Holds actual data stored in node
	Node<T> * m_next;		//Points to next node in list
	Node<T> * m_previous;	//Points to previous node in list
};

/**********************************************************************
* Purpose:
*	To construct an instance of a Node and initialize the data
*	members to default values.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data members are initialized to default values.
**********************************************************************/
template<typename T>
Node<T>::Node() : m_next(nullptr), m_previous(nullptr)
{}

/**********************************************************************
* Purpose:
*	To construct an instance of a Node and initialize the data
*	member representing the data to the value of the parameter, and the
*	pointer data members to nullptr.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data members are initialized to default values and the value of
*	the parameter.
**********************************************************************/
template<typename T>
Node<T>::Node(T data) : m_data(data), m_next(nullptr), m_previous(nullptr)
{}

/**********************************************************************
* Purpose:
*	To construct an instance of a Node with data members whose initial
*	values are copied from data members of an existing Node object.
*
* Precondition:
*	An existing Node object passed by const ref.
*
* Postcondition:
*	The data members are initialized to the values of the data members
*	of the existing Node object.
**********************************************************************/
template<typename T>
Node<T>::Node(const Node & copy) : m_data(copy.m_data), m_next(nullptr), m_previous(nullptr)
{
	*this = copy;	//Use assignment operator
}

/**********************************************************************
* Purpose:
*	To reset the data members to default values, and destroy the
*	Node object.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data members are re-initialized to default values.
**********************************************************************/
template<typename T>
Node<T>::~Node()
{
	//Reset to initial default values
	m_next = nullptr;
	m_previous = nullptr;
}

/**********************************************************************
* Purpose:
*	To assign one existing Node object to another existing Node object
*	by copying values of data members from one to another.
*
* Precondition:
*	An existing Node object passed by const ref.
*
* Postcondition:
*	One existing Node object is assigned to another existing Node
*	object.
**********************************************************************/
template<typename T>
Node<T> & Node<T>::operator=(const Node<T> & rhs)
{
	//Check for self-assignment
	if (this != &rhs)
	{
		m_data = rhs.m_data;
		m_next = rhs.m_next;
		m_previous = rhs.m_previous;
	}

	return *this;
}

#endif //NODE_H