/**********************************************************************
* Author:			Molli Drivdahl
* Filename:			deck.h
* Date Created:		2/2/16
* Modifications:	2/8/16
*
* Class: Deck
*
* Purpose:
*	This class simulates a deck of 52 playing cards.
*
* Manager functions:
*	Deck()
*		Creates a Deck with the 52 cards initialized to a different
*		rank and suit combination in sequential order.
*
*	Deck(const Deck & copy)
*
*	~Deck()
*
*	Deck & operator=(const Deck & rhs)
*
* Methods:
*	void Shuffle()
*		Randomly assigns different combinations of ranks and suits to
*		all 52 cards in the deck.
*
*	Card Deal()
*		Deals one of the 52 cards in the deck.
**********************************************************************/
#ifndef DECK_H
#define DECK_H

#include "card.h"

const int NUM_CARDS_DECK = 52;	//Number of cards in a deck

class Deck
{
public:
	//Default Ctor
	Deck();

	//Copy Ctor
	Deck(const Deck & copy);

	//Default Dtor
	~Deck();

	//Assignment Operator
	Deck & operator=(const Deck & rhs);

	//Randomly shuffles deck
	void Shuffle();

	//Deals card from deck
	Card Deal();

private:
	Card m_deck[NUM_CARDS_DECK];	//Array of 52 Cards
	int m_current_card;				//Counter for current card to be dealt from the deck
};

#endif //DECK_H