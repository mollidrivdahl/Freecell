/**********************************************************************
* Author:			Molli Drivdahl
* Filename:			stackLL.h
* Date Created:		1/29/16
* Modifications:	1/30/16
*
* Class: StackLL
*
* Purpose:
*	This class simulates the stack, and uses a LinkedList object as
*	the underlying data structure to allow the stack to dynamically
*	grow as necessary.
*
* Manager functions:
*	StackLL()
*		Creates a StackLL with the number of items on the stack set
*		to 0.
*
*	StackLL(const StackLL<T> & copy)
*
*	~StackLL()
*
*	StackLL<T> & operator=(const StackLL<T> & rhs)
*
* Methods:
*	void Push(const T & data)
*		Pushes its parameter onto the top of the stack.
*
*	T & Pop()
*		Removes and returns the data from the top of the stack.
*
*	T & Peek()
*		Returns the element on the top of the stack but does not
*		remove it.
*
*	int Size()
*		Returns the number of items currently on the stack.
*
*	bool isEmpty()
*		Returns true if the stack is empty.
**********************************************************************/
#ifndef STACK_LL_H
#define STACK_LL_H

#include "linkedList.h"
#include "exception.h"

template <typename T>
class StackLL
{
public:
	//Default Ctor
	StackLL();

	//Copy Ctor
	StackLL(const StackLL<T> & copy);

	//Default Dtor
	~StackLL();

	//Assignment Operator
	StackLL<T> & operator=(const StackLL<T> & rhs);

	//Pushes its parameter onto the top of the stack
	void Push(const T & data);

	//Removes and returns the data from the top of the stack
	T Pop();

	//Returns the element on the top of the stack but does not remove it
	T Peek();

	//Returns the number of items currently on the stack
	int Size();

	//Returns true if the stack is empty
	bool isEmpty();

private:
	LinkedList<T> m_stack;	//Underlying stack data structure
	int m_size;		//Contains number of items on the stack
};

/**********************************************************************
* Purpose:
*	To construct an instance of a StackLL and initialize the data
*	member representing the number of items on the stack to zero.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data members are initialized to default values.
**********************************************************************/
template<typename T>
StackLL<T>::StackLL() : m_size(0)
{}

/**********************************************************************
* Purpose:
*	To construct an instance of a StackLL with data members whose
*	initial values are copied from data members of an existing StackLL
*	object.
*
* Precondition:
*	An existing StackLL object passed by const ref.
*
* Postcondition:
*	The data members are initialized to the values of the data members
*	of the existing StackLL object.
**********************************************************************/
template<typename T>
StackLL<T>::StackLL(const StackLL<T>& copy) : m_size(0)
{
	*this = copy;	//Use assignment operator
}

/**********************************************************************
* Purpose:
*	To reset the data members to default values, and destroy the
*	StackLL object.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data members are re-initialized to default values.
**********************************************************************/
template<typename T>
StackLL<T>::~StackLL()
{
	//Reset to default values
	m_size = 0;
}

/**********************************************************************
* Purpose:
*	To assign one existing StackLL object to another existing StackLL
*	object by copying values of data members from one to another.
*
* Precondition:
*	An existing StackLL object passed by const ref.
*
* Postcondition:
*	One existing StackLL object is assigned to another existing
*	StackLL object.
**********************************************************************/
template<typename T>
StackLL<T>& StackLL<T>::operator=(const StackLL<T>& rhs)
{
	if (this != &rhs)
		m_stack = rhs.m_stack;	//Use LinkedList's assignment operator

	return *this;
}

/**********************************************************************
* Purpose:
*	To add an item to the top of the stack.
*
* Precondition:
*	A template type that represents the data item to put on the stack.
*
* Postcondition:
*	The item is placed on top of the stack.
**********************************************************************/
template<typename T>
void StackLL<T>::Push(const T & data)
{
	m_stack.Prepend(data);	//Add node to front of linked list to put item at top of stack
	m_size++;	//Increment number of items on stack
}

/**********************************************************************
* Purpose:
*	To return and remove an item from the top of the stack.
*
* Precondition:
*	<None>
*
* Postcondition:
*	The item from the top of the stack is returned and then removed,
*	if the stack is not already empty.
**********************************************************************/
template<typename T>
T StackLL<T>::Pop()
{
	//Check if stack is already empty
	if (isEmpty())
		throw Exception("ERROR: Stack underflow detected.");

	T top = m_stack.First();	//Store value of item at top of stack
	m_stack.Extract(top);	//Remove first node of linked list to delete item at top of stack
	m_size--;	//Decrement number of items on stack

	return top;		//Return value of item previously at top of stack
}

/**********************************************************************
* Purpose:
*	To return an item from the top of the stack, but not remove it.
*
* Precondition:
*	<None>
*
* Postcondition:
*	The item from the top of the stack is returned, if the stack is
*	not already empty.
**********************************************************************/
template<typename T>
T StackLL<T>::Peek()
{
	//Check if stack is already empty
	if (isEmpty())
		throw Exception("ERROR: Cannot access top of an empty stack.");

	return (m_stack.First());		//Return value of item at top of stack
}

/**********************************************************************
* Purpose:
*	To return the number of items on the stack.
*
* Precondition:
*	<None>
*
* Postcondition:
*	The number of items on the stack is returned.
**********************************************************************/
template<typename T>
int StackLL<T>::Size()
{
	return m_size;	//Return number of items on stack
}

/**********************************************************************
* Purpose:
*	To return whether or not the stack is empty.
*
* Precondition:
*	<None>
*
* Postcondition:
*	A bool is returned signaling whether or not the stack is empty.
**********************************************************************/
template<typename T>
bool StackLL<T>::isEmpty()
{
	return (m_stack.isEmpty());		//Returns true if linked list is empty
}

#endif //STACK_LL_H