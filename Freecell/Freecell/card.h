/**********************************************************************
* Author:			Molli Drivdahl
* Filename:			card.h
* Date Created:		2/2/16
* Modifications:	2/8/16
*
* Class: Card
*
* Purpose:
*	This class simulates a single playing card.
*
* Manager functions:
*	Card()
*		Creates a Card in which the rank defaults to Ace and the suit
*		defaults to Spade.
*
*	Card(Rank rank, Suit suit)
*		Creates a Card in which the rank and suit are both set to the
*		values of the parameters.
*
*	Card(const Card & copy)
*
*	~Card()
*
*	Card & operator=(const Card & rhs)
*
* Methods:
*	bool operator!=(const Card & rhs)
*		Overloads the != operator so two Cards' ranks and suits can be
*		compared.
*
*	void SetRank(Rank rank)
*		Sets the rank of the card to the value of the parameter.
*
*	void SetSuit(Suit suit)
*		Sets the suit of the card to the value of the parameter.
*
*	Rank GetRank() const
*		Returns the rank of the card.
*
*	Suit GetSuit() const
*		Returns the suit of the card.
**********************************************************************/
#ifndef CARD_H
#define CARD_H

//Cards can have any combination of rank and suit values
enum Rank { ACE = 1, DEUCE, TREY, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
enum Suit { SPADE, HEART, CLUB, DIAMOND };

const int NUM_RANKS = 13;	//Number of possible ranks for any given card
const int NUM_SUITS = 4;	//Number of possible suits for any given card

class Card
{
public:
	//Default Ctor
	Card();

	//2-Arg Overloaded Ctor
	Card(Rank rank, Suit suit);

	//Copy Ctor
	Card(const Card & copy);

	//Default Destructor
	~Card();

	//Assignment Operator
	Card & operator=(const Card & rhs);

	//Overloaded != Operator
	bool operator!=(const Card & rhs);

	//Setter for m_rank
	void SetRank(Rank rank);

	//Setter for m_suit
	void SetSuit(Suit suit);

	//Getter for m_rank
	Rank GetRank() const;

	//Getter for m_suit
	Suit GetSuit() const;

private:
	Rank m_rank;	//Stores Card rank
	Suit m_suit;	//Stores Card suit
};

#endif //CARD_H