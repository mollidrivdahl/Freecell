/**********************************************************************
* Author:			Molli Drivdahl
* Filename:			exception.h
* Date Created:		1/4/16
* Modifications:	1/5/16
*
* Class: Exception
*
* Purpose:
*	This class allows an Exception to be created that manages error
*	messages that can be thrown with the use of a try-catch block.
*
* Manager functions:
*	Exception()
*		Creates an Exception with a message initialized to nullptr.
*
*	Exception(char * msg)
*		Creates an Exception with a message initialized to the value of
*		the parameter.
*
*	Exception(const Exception & copy)
*
*	~Exception()
*
*	Exception & operator=(const Exception & rhs)
*
* Methods:
*	const char * getMessage() const
*		Returns value of the message about the Exception.
*
*	void setMessage(char * msg)
*		Sets value of the message about the Exception.
*
*	friend ostream & operator<<(ostream & stream,
*								const Exception & except)
*		Overloads the << operator to display the message of the
*		Exception object to the screen.
**********************************************************************/

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <fstream>
using std::ostream;

class Exception
{
public:
	//Default Ctor
	Exception();

	//Overloaded Ctor
	Exception(char * msg);

	//Copy Ctor
	Exception(const Exception & copy);

	//Default Dtor
	~Exception();

	//Assignment Operator
	Exception & operator=(const Exception & rhs);

	//Getter for m_msg
	const char * getMessage() const;

	//Setter for m_msg
	void setMessage(char * msg);

	//Friend overloaded << operator
	friend ostream & operator<<(ostream & stream, const Exception & except);

private:
	//Exception message
	char * m_msg;
};

#endif //EXCEPTION_H