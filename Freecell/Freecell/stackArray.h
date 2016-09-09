/**********************************************************************
* Author:			Molli Drivdahl
* Filename:			stackArray.h
* Date Created:		1/28/16
* Modifications:	1/30/16
*
* Class: StackArray
*
* Purpose:
*	This class simulates the stack, and uses an Array object as the
*	underlying data structure. The stack is a specified fixed size.
*
* Manager functions:
*	StackArray()
*		Creates a StackArray with the reference to the index of the
*		top of the stack set to -1 since the stack has no items (since
*		0 would indicate the stack has 1 item at element zero).
*
*	StackArray(int size)
*		Creates a StackArray with the length of the underlying array
*		set to the value of the parameter, and the reference to the
*		index of the top of the stack set to -1 since the stack has no
*		items (since 0 would indicate the stack has 1 item at element
*		zero).
*
*	StackArray(const StackArray<T> & copy)
*
*	~StackArray()
*
*	StackArray<T> & operator=(const StackArray<T> & rhs)
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
*
*	bool isFull()
*		Returns true if the stack is full.
**********************************************************************/
#ifndef STACK_ARRAY_H
#define STACK_ARRAY_H

#include "array.h"

template <typename T>
class StackArray
{
public:
	//Default Ctor
	StackArray();

	//1-Arg Overloaded Ctor
	StackArray(int size);

	//Copy Ctor
	StackArray(const StackArray<T> & copy);

	//Default Dtor
	~StackArray();

	//Assignment Operator
	StackArray<T> & operator=(const StackArray<T> & rhs);

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

	//Returns true if the stack is full
	bool isFull();

private:
	Array<T> m_stack;	//Underlying stack data structure
	int m_top;		//References the index of the top item of the stack in the Array
};

/**********************************************************************
* Purpose:
*	To construct an instance of a StackArray and initialize the data
*	member referencing the index of the top of the stack to the default
*	value of -1.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data members are initialized to default values.
**********************************************************************/
template<typename T>
StackArray<T>::StackArray() : m_top(-1)		//-1 indicates no items on stack since indicies cannot be < 0 
{}

/**********************************************************************
* Purpose:
*	To construct an instance of a StackArray, initialize one data
*	member to a default value of -1, and set the size of the
*	underlying Array to the length of the parameter if not negative.
*
* Precondition:
*	An integer representing the size of the stack.
*
* Postcondition:
*	Data members are initialized to default values.
**********************************************************************/
template<typename T>
StackArray<T>::StackArray(int size) : m_top(-1)		//-1 indicates no items on stack since indicies cannot be < 0 
{
	if (size < 0)
	{
		//Cannot have negative sized stack
		throw Exception("ERROR: Stack of negative size not allowed.");
	}

	//Give stack desired size
	m_stack.setLength(size);
}

/**********************************************************************
* Purpose:
*	To construct an instance of a StackArray with data members whose
*	initial values are copied from data members of an existing
*	StackArray object.
*
* Precondition:
*	An existing StackArray object passed by const ref.
*
* Postcondition:
*	The data members are initialized to the values of the data members
*	of the existing StackArray object.
**********************************************************************/
template<typename T>
StackArray<T>::StackArray(const StackArray<T> & copy) : m_top(-1)	//-1 indicates no items on stack since elements cannot be < 0 
{
	*this = copy;	//Use assignment operator
}

/**********************************************************************
* Purpose:
*	To reset the data members to default values, and destroy the
*	StackArray object.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data members are re-initialized to default values.
**********************************************************************/
template<typename T>
StackArray<T>::~StackArray()
{
	//Reset to default value
	m_top = -1;
}

/**********************************************************************
* Purpose:
*	To assign one existing StackArray object to another existing
*	StackArray object by copying values of data members from one to
*	another.
*
* Precondition:
*	An existing StackArray object passed by const ref.
*
* Postcondition:
*	One existing StackArray object is assigned to another existing
*	StackArray object.
**********************************************************************/
template<typename T>
StackArray<T>& StackArray<T>::operator=(const StackArray<T>& rhs)
{
	//Check for self assignment
	if (this != &rhs)
	{
		m_stack = rhs.m_stack;	//Use Array's assignment operator
		m_top = rhs.m_top;
	}

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
*	The item is placed on top of the stack, if the stack is not already
*	full.
**********************************************************************/
template<typename T>
void StackArray<T>::Push(const T & data)
{
	//Check if stack is already full
	if (isFull())
		throw Exception("ERROR: Stack overflow detected.");

	m_top++;	//Increment index of top of stack to next index in array
	m_stack[m_top] = data;		//Place item on top of stack
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
T StackArray<T>::Pop()
{
	//Check if stack is already empty
	if (isEmpty())
		throw Exception("ERROR: Stack underflow detected.");

	//Return value of top of stack & then decrement index of top of stack to previous index in array
	return m_stack[m_top--];
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
T StackArray<T>::Peek()
{
	//Check if stack is already empty
	if (isEmpty())
		throw Exception("ERROR: Cannot access top of empty stack.");

	//Return value of top of stack
	return m_stack[m_top];
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
int StackArray<T>::Size()
{
	//Return index value plus one to reference actual number of items on stack
	return (m_top + 1);
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
bool StackArray<T>::isEmpty()
{
	//Returns true if index of top element of stack is less than first index of array
	return (m_top == -1);
}

/**********************************************************************
* Purpose:
*	To return whether or not the stack if full.
*
* Precondition:
*	<None>
*
* Postcondition:
*	A bool is returned signaling whether or not the stack is full.
**********************************************************************/
template<typename T>
bool StackArray<T>::isFull()
{
	//Returns true if index of top element of stack is at the last index of array
	return (m_top == (m_stack.getLength() - 1));
}

#endif //STACK_ARRAY_H