/**********************************************************************
* Author:			Molli Drivdahl
* Filename:			card.cpp
* Date Created:		2/2/16
* Modifications:	2/8/16
**********************************************************************/

#include "card.h"

#include <iostream>
using std::cout;

/**********************************************************************
* Purpose:
*	To construct an instance of an Card and initialize the rank and
*	suit of the card to Ace of Spaces by default.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data members are initialized to default values.
**********************************************************************/
Card::Card() : m_rank(ACE), m_suit(SPADE)
{}

/**********************************************************************
* Purpose:
*	To construct an instance of an Card and initialize the rank and
*	suit of the card to the values of the parameters.
*
* Precondition:
*	A Rank and a Suit enum type.
*
* Postcondition:
*	Data members are initialized to default values.
**********************************************************************/
Card::Card(Rank rank, Suit suit) : m_rank(rank), m_suit(suit)
{}

/**********************************************************************
* Purpose:
*	To construct an instance of an Card with data members whose
*	initial values are copied from data members of an existing Card
*	object.
*
* Precondition:
*	An existing Card object passed by const ref.
*
* Postcondition:
*	The data members are initialized to the values of the data members
*	of the existing Card object.
**********************************************************************/
Card::Card(const Card & copy) : m_rank(ACE), m_suit(SPADE)
{
	*this = copy;	//Use assignment operator
}

/**********************************************************************
* Purpose:
*	To destroy the Card and reset the data members to default values.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data members are reset to default values.
**********************************************************************/
Card::~Card()
{
	//Reset to default values
	m_rank = ACE;
	m_suit = SPADE;
}

/**********************************************************************
* Purpose:
*	To assign one existing Card object to another existing Card object
*	by copying values of data members from one to another.
*
* Precondition:
*	An existing Card object passed by const ref.
*
* Postcondition:
*	One existing Card object is assigned to another existing Card
*	object.
**********************************************************************/
Card & Card::operator=(const Card & rhs)
{
	//Check for self-assignment
	if (this != &rhs)
	{
		m_rank = rhs.m_rank;
		m_suit = rhs.m_suit;
	}

	return *this;
}

/**********************************************************************
* Purpose:
*	To overload the != operator in order to compare the ranks and suits
*	of two Cards.
*
* Precondition:
*	An existing Card object passed by const ref.
*
* Postcondition:
*	The rhs Card object is compared with the lhs Card object.
**********************************************************************/
bool Card::operator!=(const Card & rhs)
{
	bool notEqual = false;	//Flags whether the Cards are the same

	//Cards are not the same if either rank or suit is not equal
	if (m_rank != rhs.m_rank || m_suit != rhs.m_suit)
		notEqual = true;

	return notEqual;
}

/**********************************************************************
* Purpose:
*	To set the rank to the value of the parameter.
*
* Precondition:
*	A Rank enum type.
*
* Postcondition:
*	The rank is set to the value of the parameter.
**********************************************************************/
void Card::SetRank(Rank rank)
{
	m_rank = rank;
}

/**********************************************************************
* Purpose:
*	To set the suit to the value of the parameter.
*
* Precondition:
*	A Suit enum type.
*
* Postcondition:
*	The suit is set to the value of the parameter.
**********************************************************************/
void Card::SetSuit(Suit suit)
{
	m_suit = suit;
}

/**********************************************************************
* Purpose:
*	To return the value of the rank.
*
* Precondition:
*	<None>
*
* Postcondition:
*	The rank is returned.
**********************************************************************/
Rank Card::GetRank() const
{
	return m_rank;
}

/**********************************************************************
* Purpose:
*	To return the value of the suit.
*
* Precondition:
*	<None>
*
* Postcondition:
*	The suit is returned.
**********************************************************************/
Suit Card::GetSuit() const
{
	return m_suit;
}
