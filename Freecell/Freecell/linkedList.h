/**********************************************************************
* Author:			Molli Drivdahl
* Filename:			linkedList.h
* Date Created:		1/6/16
* Modifications:	1/24/16
*
* Class: LinkedList
*
* Purpose:
*	This class simulates the actual list of a doubly linked list.
*
* Manager functions:
*	LinkedList()
*		Creates a LinkedList with the head and tail pointers set to
*		nullptr.
*
*	LinkedList(const LinkedList & copy)
*
*	~LinkedList()
*
*	LinkedList<T> & operator=(const LinkedList<T> & rhs)
*
* Methods:
*	bool isEmpty() const
*		Checks if list is empty.
*
*	const T & First() const
*		Returns a const reference to the data in the first element.
*
*	const T & Last() const
*		Returns a const reference to the data in the last element.
*
*	void Prepend(const T & data)
*		Adds an item to the front of the list.
*
*	void Append(const T & data)
*		Adds an item to the end of the list.
*
*	void InsertBefore(const T & newData, const T & existingData)
*		Insert an item/Node before an existing item/Node in the list.
*
*	void InsertAfter(const T & newData, const T & existingData)
*		Insert an item/Node after an existing item/Node in the list.
*
*	void Purge()
*		Removes all items/Nodes from the list.
*
*	void Extract(const T & data)
*		Removes a single item/Node from the list
*
*	void PrintForwards()
*		Displays the data of each item/Node in the list from front to
*		end.
*
*	void PrintBackwards()
*		Displays the data of each item/Node in the list from end to
*		front.
**********************************************************************/
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "node.h"

template <typename T>
class LinkedList
{
public:
	//Default Ctor
	LinkedList();

	//Copy Ctor
	LinkedList(const LinkedList & copy);

	//Default Dtor
	~LinkedList();

	//Assignment Operator
	LinkedList<T> & operator=(const LinkedList<T> & rhs);

	//Checks if list is empty
	bool isEmpty() const;

	//Returns a const reference to the data in the first element
	const T & First() const;

	//Returns a const reference to the data in the last element
	const T & Last() const;

	//Adds an item to the front of the list
	void Prepend(const T & data);

	//Adds an item to the end of the list
	void Append(const T & data);

	//Insert an item/Node before an existing item/Node in the list
	void InsertBefore(const T & newData, const T & existingData);

	//Insert an item/Node after an existing item/Node in the list
	void InsertAfter(const T & newData, const T & existingData);

	//Removes all items/Nodes from the list
	void Purge();

	//Removes a single item/Node from the list
	void Extract(const T & data);

	//Displays the data of each item/Node in the list from front to end
	void PrintForwards();

	//Displays the data of each item/Node in the list from end to front
	void PrintBackwards();

private:
	Node<T> * m_head;	//head pointer, points to first node in list
	Node<T> * m_tail;	//tail pointer, points to last node in list
};

/**********************************************************************
* Purpose:
*	To construct an instance of a LinkedList and initialize the data
members to default values.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data members are initialized to default values.
**********************************************************************/
template<typename T>
LinkedList<T>::LinkedList() : m_head(nullptr), m_tail(nullptr)
{}

/**********************************************************************
* Purpose:
*	To construct an instance of a LinkedList with data members whose
*	initial values are copied from data members of an existing
*	LinkedList object.
*
* Precondition:
*	An existing LinkedList object passed by const ref.
*
* Postcondition:
*	The data members are initialized to the values of the data members
*	of the existing LinkedList object.
**********************************************************************/
template<typename T>
LinkedList<T>::LinkedList(const LinkedList & copy) : m_head(nullptr), m_tail(nullptr)
{
	//Use assignment operator
	*this = copy;
}

/**********************************************************************
* Purpose:
*	To reset the data members to default values, and destroy the
*	LinkedList object.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data members are re-initialized to default values.
**********************************************************************/
template<typename T>
LinkedList<T>::~LinkedList()
{
	//Remove and delete all nodes
	Purge();

	//Reset to inital default values
	m_head = nullptr;
	m_tail = nullptr;
}

/**********************************************************************
* Purpose:
*	To assign one existing LinkedList object to another existing
*	LinkedList object by copying values of data members from one to
*	another.
*
* Precondition:
*	An existing LinkedList object object passed by const ref.
*
* Postcondition:
*	One existing LinkedList object object is assigned to another
*	existing LinkedList object.
**********************************************************************/
template<typename T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList<T> & rhs)
{
	//Traveling pointer to traverse parameter list
	Node<T> * rhsTravel = rhs.m_head;

	//If addresses of objects are not the same
	if (this != &rhs)
	{
		//Clear this list
		Purge();

		//While travel has not reached end of parameter list
		while (rhsTravel != nullptr)
		{
			//Add node from parameter list to this list
			Append(rhsTravel->m_data);
			//Increment traveling pointer to next node in parameter list
			rhsTravel = rhsTravel->m_next;
		}
	}

	return *this;
}

/**********************************************************************
* Purpose:
*	To check if the list is empty.
*
* Precondition:
*	<None>
*
* Postcondition:
*	A bool signaling if the list is empty is returned.
**********************************************************************/
template<typename T>
bool LinkedList<T>::isEmpty() const
{
	//Indicates list is empty if false
	bool emptyList = false;

	//If the head pointer points to nullptr
	if (m_head == nullptr)
		emptyList = true;	//List is not empty

	return emptyList;
}

/**********************************************************************
* Purpose:
*	To return a constant reference to the data in the first node of
*	the linked list.
*
* Precondition:
*	<None>
*
* Postcondition:
*	A constant reference to the data in the first node of the linked
*	list is returned.
**********************************************************************/
template<typename T>
const T & LinkedList<T>::First() const
{
	//If list is empty, can't access first node
	if (isEmpty())
		throw("ERROR: List is empty. Cannot return first node.");

	//Else return data of first node
	else
		return m_head->m_data;
}

/**********************************************************************
* Purpose:
*	To return a constant reference to the data in the last node of
*	the linked list.
*
* Precondition:
*	<None>
*
* Postcondition:
*	A constant reference to the data in the last node of the linked
*	list is returned.
**********************************************************************/
template<typename T>
const T & LinkedList<T>::Last() const
{
	//If list is empty, can't access last node
	if (isEmpty())
		throw("ERROR: List is empty. Cannot return last node.");

	//Else return data of last node
	else
		return m_tail->m_data;
}

/**********************************************************************
* Purpose:
*	To add an item to the front of the list.
*
* Precondition:
*	A template type of the data to add to the list.
*
* Postcondition:
*	An item is added to the front of the list.
**********************************************************************/
template<typename T>
void LinkedList<T>::Prepend(const T & data)
{
	//Create new node to add to list
	Node<T> * newNode = new Node<T>(data);

	//If list is empty
	if (isEmpty())
	{
		//Assign both head and tail pointers to new node
		m_head = newNode;
		m_tail = newNode;
	}
	//Else add new node to front of list
	else
	{
		newNode->m_next = m_head;
		m_head->m_previous = newNode;
		m_head = newNode;
	}
}

/**********************************************************************
* Purpose:
*	To add an item to the end of the list.
*
* Precondition:
*	A template type of the data to add to the list.
*
* Postcondition:
*	An item is added to the end of the list.
**********************************************************************/
template<typename T>
void LinkedList<T>::Append(const T & data)
{
	//Create new node to add to list
	Node<T> * newNode = new Node<T>(data);

	//If list is empty
	if (isEmpty())
	{
		//Assign both head and tail pointers to new node
		m_head = newNode;
		m_tail = newNode;
	}
	//Else add new node to end of list
	else
	{
		m_tail->m_next = newNode;
		newNode->m_previous = m_tail;
		m_tail = newNode;
	}
}

/**********************************************************************
* Purpose:
*	To insert and item before an existing item in the list.
*
* Precondition:
*	A template type of the data to add to the list, and a template type
*	of the data already existing in the list.
*
* Postcondition:
*	An item is inserted before an existing item in the list.
**********************************************************************/
template<typename T>
void LinkedList<T>::InsertBefore(const T & newData, const T & existingData)
{
	//If list is empty
	if (isEmpty())
	{
		//Can't insert node before another node
		throw ("ERROR: Cannot insert node if list is empty.");
	}
	//Else if first node's data matches target existing data
	else if (m_head->m_data == existingData)
	{
		//Add new node to front of list
		Prepend(newData);
	}
	//Else continue checking for target existing data
	else
	{
		//Traveling pointer to traverse list
		Node<T> * travel = m_head;

		//While travel's next pointer is not end of list
		//& data in node of travel's next pointer does not match target existing data
		while (travel->m_next != nullptr && travel->m_next->m_data != existingData)
			travel = travel->m_next;	//Increment travel to point to next node in list

										//If travel reaches end of list w/no match
		if (travel->m_next == nullptr)
		{
			//Can't insert node before non-existing target data
			throw ("ERROR: Cannot insert node when \"existing data\" does not exist in any existing nodes.");
		}
		//Else travel's next pointer points to node w/target existing data
		else
		{
			//Create new node to add to list
			Node<T> * newNode = new Node<T>(newData);

			//Insert new node before node travel's next pointer points to
			newNode->m_next = travel->m_next;
			newNode->m_previous = travel;
			travel->m_next->m_previous = newNode;
			travel->m_next = newNode;
		}
	}
}

/**********************************************************************
* Purpose:
*	To insert and item after an existing item in the list.
*
* Precondition:
*	A template type of the data to add to the list, and a template type
*	of the data already existing in the list.
*
* Postcondition:
*	An item is inserted after an existing item in the list.
**********************************************************************/
template<typename T>
void LinkedList<T>::InsertAfter(const T & newData, const T & existingData)
{
	//If list is empty
	if (isEmpty())
	{
		//Can't insert node after another node
		throw ("ERROR: Cannot insert node if list is empty.");
	}
	//Else check list for target existing data
	else
	{
		//Traveling pointer to traverse list
		Node<T> * travel = m_head;

		//While travel is not at end of list
		//& data in node of travel does not match target existing data
		while (travel != nullptr && travel->m_data != existingData)
			travel = travel->m_next;	//Increment travel to point to next node

										//If travel reaches end of list with no match
		if (travel == nullptr)
		{
			//Can't insert node after non-existing target data
			throw ("ERROR: Cannot insert node when \"existing data\" does not exist in any existing nodes.");
		}
		//Else travel points to node w/target existing data
		else
		{
			//If travel is at last node in list
			if (travel == m_tail)
			{
				//Insert new node after last node in list
				Append(newData);
			}
			//Else travel is in middle of list
			else
			{
				//Create new node to add to list
				Node<T> * newNode = new Node<T>(newData);

				//Insert new node after node travel points to
				newNode->m_next = travel->m_next;
				newNode->m_previous = travel;
				travel->m_next->m_previous = newNode;
				travel->m_next = newNode;
			}
		}
	}
}

/**********************************************************************
* Purpose:
*	To remove all items from the list.
*
* Precondition:
*	<None>
*
* Postcondition:
*	All items are removed from the list.
**********************************************************************/
template<typename T>
void LinkedList<T>::Purge()
{
	//If list is not empty, remove all nodes
	if (!isEmpty())
	{
		//Trailing poiter to traverse list behind head pointer
		Node<T> * trail = m_head;

		//While trail is not at end of list
		while (trail != nullptr)
		{
			//Point head to next node in list
			m_head = m_head->m_next;
			//Delete node trailing head pointer
			delete trail;
			//Point trail to new first node in list
			trail = m_head;
		}

		//Reset tail to nullptr since list is empty
		m_tail = nullptr;
	}
}

/**********************************************************************
* Purpose:
*	To remove a single item from the list.
*
* Precondition:
*	A template type of the data to remove from the list.
*
* Postcondition:
*	An item is removed from the list.
**********************************************************************/
template<typename T>
void LinkedList<T>::Extract(const T & data)
{
	//If list is empty
	if (isEmpty())
	{
		//Can't remove node from empty list
		throw("ERROR: Cannot remove a node when list is empty.");
	}
	//Else check list for node w/target data to remove
	else
	{
		//Traveling pointer to traverse list
		Node<T> * travel = m_head;

		//While travel is not at end of list
		//& data in node of travel does not match target data
		while (travel != nullptr && travel->m_data != data)
			travel = travel->m_next;	//Increment travel to point to next node

										//If travel reaches end of list with no match
		if (travel == nullptr)
		{
			//Can't remove node that does not exist
			throw("ERROR: Cannot remove a node that does not exist.");
		}
		//Else travel points to node w/target data to be removed
		else
		{
			//If node w/target data (travel) is only node in list
			if (travel->m_previous == nullptr && travel->m_next == nullptr)
			{
				//Assign both head and tail to nullptr
				m_head = nullptr;
				m_tail = nullptr;
				//Delete node w/target data
				delete travel;
			}
			//Else if node w/target data (travel) is first node in list
			else if (travel->m_previous == nullptr)
			{
				//Assign head pointer to travel's next node
				m_head = travel->m_next;
				//Make node prior to travel the first node in list
				travel->m_next->m_previous = nullptr;
				//Delete node w/target data
				delete travel;
			}
			//Else if node w/target data (travel) is last node in list
			else if (travel->m_next == nullptr)
			{
				//Assign tail pointer to travel's previous node
				m_tail = travel->m_previous;
				//Make node previous to travel the last node in list
				travel->m_previous->m_next = nullptr;
				//Delete node w/target data
				delete travel;
			}
			//Else node w/target data (travel) is in middle of list
			else
			{
				//Connect node previous to travel to node prior to travel
				travel->m_previous->m_next = travel->m_next;
				travel->m_next->m_previous = travel->m_previous;
				//Delete node w/target data
				delete travel;
			}
		}
	}
}

/**********************************************************************
* Purpose:
*	To display the data of each item in the list from the beginning of
*	the list to the end of the list.
*
* Precondition:
*	<None>
*
* Postcondition:
*	The data of each item in the list is displayed.
**********************************************************************/
template<typename T>
void LinkedList<T>::PrintForwards()
{
	//Traveling pointer to traverse list
	Node<T> * travel = m_head;

	//While travel is not at end of list
	while (travel != nullptr)
	{
		//Display data in nodes
		cout << travel->m_data << "\n";
		//Increment travel to point to next node
		travel = travel->m_next;
	}
}

/**********************************************************************
* Purpose:
*	To display the data of each item in the list from the end of the
*	list to the beginning of the list.
*
* Precondition:
*	<None>
*
* Postcondition:
*	The data of each item in the list is displayed.
**********************************************************************/
template<typename T>
void LinkedList<T>::PrintBackwards()
{
	//Traveling pointer to traverse list from back to front
	Node<T> * travelReverse = m_tail;

	//While travelReverse is not at beginning of list
	while (travelReverse != nullptr)
	{
		//Display data in nodes
		cout << travelReverse->m_data << "\n";
		//Increment travelReverse to point to previous node
		travelReverse = travelReverse->m_previous;
	}
}

#endif //LINKED_LIST_H