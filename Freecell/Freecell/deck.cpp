/**********************************************************************
* Author:			Molli Drivdahl
* Filename:			deck.cpp
* Date Created:		2/2/16
* Modifications:	2/8/16
**********************************************************************/

#include "deck.h"

#include <cstdlib>
#include <ctime>
using std::srand;
using std::time;

/**********************************************************************
* Purpose:
*	To construct an instance of an Deck and initialize the data
*	member representing the current card to be dealt to a 0, and
*	initialize all 52 cards to different rank and suit combination in
*	sequential order.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data members are initialized to default values.
**********************************************************************/
Deck::Deck() : m_current_card(0)
{
	int count = 0;	//Counter for loop that initializes cards in deck

	//Initialize each Card to different rank/suit combination
	for (int row = 1; row <= NUM_RANKS; row++)
	{
		for (int column = 0; column < NUM_SUITS; column++)
		{
			m_deck[count].SetRank(static_cast<Rank>(row));
			m_deck[count].SetSuit(static_cast<Suit>(column));
			count++;
		}
	}

	//Placed here instead of in Shuffle() b/c needs only run once
	srand((unsigned int)time(NULL));
}

/**********************************************************************
* Purpose:
*	To construct an instance of an Deck with data members whose
*	initial values are copied from data members of an existing Deck
*	object.
*
* Precondition:
*	An existing Deck object passed by const ref.
*
* Postcondition:
*	The data members are initialized to the values of the data members
*	of the existing Deck object.
**********************************************************************/
Deck::Deck(const Deck & copy) : m_current_card(0)
{
	*this = copy;	//Use assignment operator
}

/**********************************************************************
* Purpose:
*	To destroy the Deck and reset the data members to default values.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data members are reset to default values.
**********************************************************************/
Deck::~Deck()
{
	//Reset to default value
	m_current_card = 0;
}

/**********************************************************************
* Purpose:
*	To assign one existing Deck object to another existing Deck object
*	by copying values of data members from one to another.
*
* Precondition:
*	An existing Deck object passed by const ref.
*
* Postcondition:
*	One existing Deck object is assigned to another existing Deck
*	object.
**********************************************************************/
Deck & Deck::operator=(const Deck & rhs)
{
	//Check for self-assignment
	if (this != &rhs)
	{
		m_current_card = rhs.m_current_card;
		
		for (int i = 0; i < NUM_CARDS_DECK; i++)
		{
			m_deck[i] = rhs.m_deck[i];	//Use Card's assignment operator
		}
	}

	return *this;
}

/**********************************************************************
* Purpose:
*	To randomly assign different combinations of ranks and suits to all
*	52 cards in the deck. Also resets the current card back to the top
*	of the deck.
*
* Precondition:
*	<None>
*
* Postcondition:
*	The cards in the deck are randomly shuffled and the current card
*	is reset to the first card in the deck.
**********************************************************************/
void Deck::Shuffle()
{
	Rank rank = ACE;		//To hold value of random rank
	Suit suit = SPADE;		//To hold value of random suit
	int numCards = 0;		//To count number of randomized cards
	bool sameCard = false;	//Flags whether rank and suit combo already exists

	//While not all cards have been assigned a rank and suit combo
	while (numCards < NUM_CARDS_DECK)
	{
		sameCard = false;	

		int rankInt = (rand() % NUM_RANKS) + 1;	//Add one, since Rank skips zero and starts at 1
		rank = static_cast<Rank>(rankInt);		//Randomly generate a rank
		suit = static_cast<Suit>(rand() % NUM_SUITS);	//Randomly generate a suit

		//For all cards that have been assigned a rank and suit combo
		for (int i = 0; i < numCards && sameCard == false; i++)
		{
			//Check if the random rank and suit combo already exists
			if (m_deck[i].GetRank() == rank && m_deck[i].GetSuit() == suit)
			{
				sameCard = true;
			}
		}

		//If new rank and suit combo
		if (sameCard == false)
		{
			//Assign next card in deck that rank and suit combo
			m_deck[numCards].SetRank(rank);
			m_deck[numCards].SetSuit(suit);
			numCards++;
		}
	}

	//Reset current card to first card in deck
	m_current_card = 0;
}

/**********************************************************************
* Purpose:
*	To deal one of the 52 cards in the deck, and then increment the
*	current card to the next card in the deck.
*
* Precondition:
*	<None>
*
* Postcondition:
*	The current card is returned from the deck.
**********************************************************************/
Card Deck::Deal()
{
	//Retrun current card in deck, then increment current card to next card in deck
	return m_deck[m_current_card++];
}