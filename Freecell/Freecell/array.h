/**********************************************************************
* Author:			Molli Drivdahl
* Filename:			array.h
* Date Created:		1/4/16
* Modifications:	1/5/16
*
* Class: Array
*
* Purpose:
*	This class creates a dynamic one-dimensional array with a starting
*	index of any value.
*
* Manager functions:
*	Array()
* 		Creates an Array with the default length zero and the default
*		starting index zero.
*
*	Array(int length, int start_index = 0)
*		Creates an Array of a specified length with either a given
*		starting index value or a default starting index value of zero.
*
*	Array(const Array & copy)
*
*	~Array()
*
*	Array & operator=(const Array & rhs)
*
* Methods:
*	T & operator[](int index) const
*		Overloads the [] operator in order to work with Arrays of
*		varying starting indices.
*
*	int getStartIndex() const
*		Returns value of the starting index.
*
*	void setStartIndex(int start_index)
*		Sets value of the starting index.
*
*	int getLength() const
*		Returns value of the length.
*
*	void setLength(int length)
*		Sets value of the length.
**********************************************************************/

#ifndef ARRAY_H
#define ARRAY_H

#include "exception.h"

template <typename T>
class Array
{
public:
	//Default Ctor
	Array();

	//Overloaded 2-arg Ctor
	Array(int length, int start_index = 0);

	//Copy Ctor
	Array(const Array<T> & copy);

	//Default Dtor
	~Array();

	//Assignment Operator
	Array<T> & operator=(const Array<T> & rhs);

	//Overloaded [] Operator
	T & operator[](int index) const;

	//Getters for m_start_index and m_length
	int getStartIndex() const;
	int getLength() const;

	//Setters for m_start_index and m_length
	void setStartIndex(int start_index);
	void setLength(int length);

private:
	T * m_array;		//Pointer to the dynamic array of data
	int m_length;		//Number of elements
	int m_start_index;	//Starting index (base element)
};

/**********************************************************************
* Purpose:
*	To construct an instance of an Array and initialize the data
*	members to defaut values.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data members are initialized to default values.
**********************************************************************/
template <typename T>
Array<T>::Array() : m_array(nullptr), m_length(0),
m_start_index(0)
{}

/**********************************************************************
* Purpose:
*	To construct an instance of an Array and initialize the data
*	members to values of the parameters.
*
* Precondition:
*	An integer representing the desired length of the Array and an
*	integer representing the desired starting index of the Array.
*
* Postcondition:
*	The data members are initialized to the values of the parameters,
*	if desired length is not negative.
**********************************************************************/
template <typename T>
Array<T>::Array(int length, int start_index) : m_array(nullptr),
m_length(length), m_start_index(start_index)
{
	//If length is negative
	if (m_length < 0)
	{
		//Cannot have negative length
		m_length = 0;
		throw Exception("ERROR: Array of negative length not allowed.");
	}
	//Else if length is zero
	else if (m_length == 0)
	{
		m_array = nullptr;
	}
	//Else array is given desired length
	else
	{
		m_array = new T[m_length];
	}
}

/**********************************************************************
* Purpose:
*	To construct an instance of an Array with data members whose
*	initial values are copied from data members of an existing Array
*	object.
*
* Precondition:
*	An existing Array object passed by const ref.
*
* Postcondition:
*	The data members are initialized to the values of the data members
*	of the existing Array object.
**********************************************************************/
template <typename T>
Array<T>::Array(const Array<T> & copy) : m_array(nullptr),
m_length(copy.m_length), m_start_index(copy.m_start_index)
{
	*this = copy;	//Use assignment operator
}

/**********************************************************************
* Purpose:
*	To deallocate the pointer to the dynamic array of data,
*	reset the data members to default values, and destroy the Array.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data members are re-initialized to default values.
**********************************************************************/
template <typename T>
Array<T>::~Array()
{
	delete[] m_array;

	//Reset to default values
	m_array = nullptr;
	m_length = 0;
	m_start_index = 0;
}

/**********************************************************************
* Purpose:
*	To assign one existing Array object to another existing Array
*	object by copying values of data members from one to another.
*
* Precondition:
*	An existing Array object passed by const ref.
*
* Postcondition:
*	One existing Array object is assigned to another existing Array
*	object.
**********************************************************************/
template <typename T>
Array<T> & Array<T>::operator=(const Array<T> & rhs)
{
	//If object addresses are not the same
	if (this != &rhs)
	{
		delete[] m_array;
		m_length = rhs.m_length;
		m_start_index = rhs.m_start_index;

		//If lenth is zero
		if (rhs.m_length == 0)
		{
			m_array = nullptr;
		}
		//Else lhs array is given length of rhs array
		else
		{
			m_array = new T[rhs.m_length];

			for (int i = 0; i < m_length; i++)
				m_array[i] = rhs.m_array[i];
		}
	}

	return *this;
}

/**********************************************************************
* Purpose:
*	To overload the [] operator in order to behave correctly with
*	Arrays with non-zero starting indices.
*
* Precondition:
*	An integer representing the desired index.
*
* Postcondition:
*	The element of the Array the the desired index location is
*	returned.
**********************************************************************/
template <typename T>
T & Array<T>::operator[](int index) const
{
	//If accessing element smaller than first element
	if (index < m_start_index)
	{
		//Out of bounds of array
		throw Exception("ERROR: Index smaller than lower bound.");
	}
	//Else if accessing element larger than last element
	else if (index >= m_length + m_start_index)
	{
		//Out of bound of array
		throw Exception("ERROR: Index larger than upper bound.");
	}
	//Else return the real index of array
	else
		return m_array[index - m_start_index];
}

/**********************************************************************
* Purpose:
*	To retrieve the value of the starting index.
*
* Precondition:
*	<None>
*
* Postcondition:
*	The value of the starting index is returned.
**********************************************************************/
template <typename T>
int Array<T>::getStartIndex() const
{
	return m_start_index;
}

/**********************************************************************
* Purpose:
*	To set the value of the starting index to the parameter value.
*
* Precondition:
*	An integer representing the desired starting index.
*
* Postcondition:
*	The value of the starting index is set to the parameter value.
**********************************************************************/
template <typename T>
void Array<T>::setStartIndex(int start_index)
{
	m_start_index = start_index;
}

/**********************************************************************
* Purpose:
*	To retrieve the value of the length.
*
* Precondition:
*	<None>
*
* Postcondition:
*	The value of the length is returned.
**********************************************************************/
template <typename T>
int Array<T>::getLength() const
{
	return m_length;
}

/**********************************************************************
* Purpose:
*	To set the value of the length to the parameter value only if the
*	parameter is non-negative.
*
* Precondition:
*	An integer representing the desired length.
*
* Postcondition:
*	The value of the starting index is set to the parameter value and
*	the pointer to the dynamic array of data is adjusted based on the
*	new parameter length, only if the parameter is non-negative; else,
*	an error is displayed.
**********************************************************************/
template <typename T>
void Array<T>::setLength(int length)
{
	//If length is greater than zero
	if (length > 0)
	{
		T * newArray = new T[length];	//Give new array the new length
		int smallestLength = 0;			//Will store length of shortest array

										//If original array has shorter length
		if (m_length < length)
			smallestLength = m_length;

		//Else new array will have shorter length
		else
			smallestLength = length;

		//Assign contents of original array to new array
		for (int i = 0; i < smallestLength; i++)
			newArray[i] = m_array[i];

		delete[] m_array;
		m_array = newArray;
		m_length = length;
	}
	//Else length is zero
	else if (length == 0)
	{
		delete[] m_array;
		m_array = nullptr;
		m_length = length;
	}
	//Else length cannot be negative
	else
		throw Exception("ERROR: Array of negative length not allowed.");
}

#endif //ARRAY_H