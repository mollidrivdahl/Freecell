/**********************************************************************
* Author:			Molli Drivdahl
* Filename:			exception.cpp
* Date Created:		1/4/16
* Modifications:	1/5/16
**********************************************************************/

#include "exception.h"

#include <cstring>
using std::strlen;
using std::strcpy;

/**********************************************************************
* Purpose:
*	To construct an instance of an Excecption and initialize the data
*	member to a default value.
*
* Precondition:
*	<None>
*
* Postcondition:
*	The data member is initialized to default values.
**********************************************************************/
Exception::Exception() : m_msg(nullptr)
{}

/**********************************************************************
* Purpose:
*	To construct an instance of an Exception and initialize the data
*	member to value of the parameter.
*
* Precondition:
*	An character pointer representing the desired message of the
*	Exception.
*
* Postcondition:
*	The data member is initialized to the value of the parameter.
**********************************************************************/
Exception::Exception(char * msg) : m_msg(nullptr)
{
	//If exception message is not set to nullptr
	if (msg != nullptr)
	{
		//Assign desired message to data member
		m_msg = new char[strlen(msg) + 1];
		strcpy(m_msg, msg);
	}
}

/**********************************************************************
* Purpose:
*	To construct an instance of an Exception with the data member whose
*	initial value is copied from data member of an existing Exception
*	object.
*
* Precondition:
*	An existing Exception object passed by const ref.
*
* Postcondition:
*	Data member is initialized to the value of the data member of
*	the existing Exception object.
**********************************************************************/
Exception::Exception(const Exception & copy) : m_msg(nullptr)
{
	//If exception message of existing Exception object is not set to nullptr
	if (copy.m_msg != nullptr)
	{
		//Assign message from existing Exception object to data member
		m_msg = new char[strlen(copy.m_msg) + 1];
		strcpy(m_msg, copy.m_msg);
	}
}

/**********************************************************************
* Purpose:
*	To deallocate the character pointer with the Exception message,
*	reset the data member to a default value, and destroy the
*	Exception.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data member is re-initialized to a default value.
**********************************************************************/
Exception::~Exception()
{
	delete[] m_msg;
	//Reset to default value
	m_msg = nullptr;
}

/**********************************************************************
* Purpose:
*	To assign one existing Exception object to another existing Array
*	object by copying values of data members from one to another.
*
* Precondition:
*	An existing Exception object passed by const ref.
*
* Postcondition:
*	One existing Exception object is assigned to another existing
*	Exception object.
**********************************************************************/
Exception & Exception::operator=(const Exception & rhs)
{
	//If object addresses are not the same
	if (this != &rhs)
	{
		delete[] m_msg;

		//If rhs exception message is not set to nullptr
		if (rhs.m_msg != nullptr)
		{
			//Assign message from rhs object to data member
			m_msg = new char[strlen(rhs.m_msg) + 1];
			strcpy(m_msg, rhs.m_msg);
		}
		else
			m_msg = nullptr;
	}
	return *this;
}

/**********************************************************************
* Purpose:
*	To retrieve the value of the message.
*
* Precondition:
*	<None>
*
* Postcondition:
*	The value of the message is returned.
**********************************************************************/
const char * Exception::getMessage() const
{
	return m_msg;
}

/**********************************************************************
* Purpose:
*	To set the value of the message to the parameter value.
*
* Precondition:
*	An character pointer representing the desired message of the
*	Exception.
*
* Postcondition:
*	The value of the message is set to the parameter value.
**********************************************************************/
void Exception::setMessage(char * msg)
{
	delete[] m_msg;

	//If desired excepion message is not set to nullptr
	if (msg != nullptr)
	{
		//Assign desired message to data member
		m_msg = new char[strlen(msg) + 1];
		strcpy(m_msg, msg);
	}
	//Else assign data member to nullptr
	else
		m_msg = nullptr;
}

/**********************************************************************
* Purpose:
*	To overload the << operator in order to allow the message of the
*	Exception object to be displayed to the screen.
*
* Precondition:
*	An output stream object and an Exception object.
*
* Postcondition:
*	The message of the Exception is displayed to the screen and the
*	output stream is returned.
**********************************************************************/
ostream & operator<<(ostream & stream, const Exception & except)
{
	return stream << except.m_msg;
}