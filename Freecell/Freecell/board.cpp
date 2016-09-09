/**********************************************************************
* Author:			Molli Drivdahl
* Filename:			board.cpp
* Date Created:		2/2/16
* Modifications:	2/8/16
**********************************************************************/

#include "board.h"

#include <windows.h>
#include <cmath>
#include <iostream>
using std::cout;
#include <iomanip>
using std::setw;

// Grab the console Handle
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

/**********************************************************************
* Purpose:
*	To construct an instance of a Board, initialize the bools that flag
*	whether a free cell is empty to true, and call the CreateBoard()
*	method to initialize the values of the different areas on the
*	board.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data members are initialized to default values.
**********************************************************************/
Board::Board()
{
	CreateBoard();

	//All free cells start as empty
	for (int i = 0; i < NUM_FREE_CELLS; i++)
		m_emptyFreeCell[i] = true;
}

/**********************************************************************
* Purpose:
*	To construct an instance of an Board with data members whose
*	initial values are copied from data members of an existing Board
*	object.
*
* Precondition:
*	An existing Board object passed by const ref.
*
* Postcondition:
*	The data members are initialized to the values of the data members
*	of the existing Board object.
**********************************************************************/
Board::Board(const Board & copy) : m_freeCells(copy.m_freeCells), m_homeCells(copy.m_homeCells), m_playArea(copy.m_playArea)
{
	*this = copy;	//Use assignment operator
}

/**********************************************************************
* Purpose:
*	To destroy the Board object and reset the data members to default
*	values.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data members are reset to default values.
**********************************************************************/
Board::~Board()
{
	m_freeCells.setLength(0);	//clear original data from free cells
	m_homeCells.setLength(0);	//clear original data from home cells
	m_playArea.setLength(0);	//clear original data from play area cells

	//Reset to default values
	for (int i = 0; i < NUM_FREE_CELLS; i++)
		m_emptyFreeCell[i] = true;
}

/**********************************************************************
* Purpose:
*	To assign one existing Board object to another existing Board
*	object by copying values of data members from one to another.
*
* Precondition:
*	An existing Board object passed by const ref.
*
* Postcondition:
*	One existing Board object is assigned to another existing Board
*	object.
**********************************************************************/
Board & Board::operator=(const Board & rhs)
{
	//Check for self-assignment
	if (this != &rhs)
	{
		//Use Array's assignment operator
		m_freeCells = rhs.m_freeCells;
		m_homeCells = rhs.m_homeCells;
		m_playArea = rhs.m_playArea;

		for (int i = 0; i < NUM_FREE_CELLS; i++)
			m_emptyFreeCell[i] = rhs.m_emptyFreeCell[i];
	}

	return *this;
}

/**********************************************************************
* Purpose:
*	To distribute shuffled cards to the play area on board, and give
*	the free cell area empty card cells and the home cell area empty
*	stacks for future cards.
*
* Precondition:
*	The areas on the board have no cards and no size to hold cards.
*
* Postcondition:
*	All cards are distributed on the play area, and the free cell and
*	home cell areas have no cards.
**********************************************************************/
void Board::CreateBoard()
{
	m_freeCells.setLength(NUM_FREE_CELLS);	//4 free cells
	m_homeCells.setLength(NUM_HOME_CELLS);	//4 home cells
	m_playArea.setLength(NUM_PLAY_CELLS);	//8 play cells

	//Assign each home cell a stack of 13 cards
	for (int i = 0; i < NUM_HOME_CELLS; i++)
	{
		m_homeCells[i] = StackArray<Card>(NUM_RANKS);
	}

	//Create deck and shuffle the cards
	Deck tempDeck;
	tempDeck.Shuffle();

	//Distribute cards to play area
	for (int i = 0; i < NUM_CARDS_DECK;)
	{
		for (int j = 0; j < NUM_PLAY_CELLS && i < NUM_CARDS_DECK; j++)
		{
			m_playArea[j].Push(tempDeck.Deal());	//Deal card to play area
			i++;	//Increment number of cards dealt to play area
		}
	}
}

/**********************************************************************
* Purpose:
*	To move the card(s) from a play area column to another play area
*	column, if allowed.
*
* Precondition:
*	Three integers specifying the index of the column to move from,
*	the index of the column to move to, and the number of cards to move.
*
* Postcondition:
*	The card(s) moved from one column to another, if allowed.
**********************************************************************/
void Board::MovePlayToPlay(int column1, int column2, int numCards)
{
	StackArray<Card> tempStack(numCards);	//Holds cards being moved
	Card tempCard;		//Holds one card to compare with another
	int numMovedCards = 0;		//Counts number of cards being moved

	//Check number of cards allowed to be moved
	if (numCards > CalculateMaxMovableCards(column2))
		throw Exception("ERROR: Not enough open cells to move that many cards.");

	//If not moving from an empty play area column
	if (!m_playArea[column1].isEmpty())
	{
		//***Move card(s) from column

		//Remove and save the first card from play area column & increment count of moved cards
		tempCard = m_playArea[column1].Pop();
		tempStack.Push(tempCard);
		numMovedCards++;

		//Attempt to move more cards
		for (int i = 0; i < numCards - 1; i++)
		{
			//If moving from an empty play area column
			if (m_playArea[column1].isEmpty())
			{
				//Restore original column
				for (int i = 0; i < numMovedCards; i++)
				{
					m_playArea[column1].Push(tempStack.Pop());
				}
				throw Exception("ERROR: Cannot move more cards than are available.");
			}

			//If ranks are in order (previously removed card is one less than next card to be removed) 
			if (m_playArea[column1].Peek().GetRank() - tempCard.GetRank() == 1)	
			{
				//If suit colors are opposite (+-1 & +-3 specify the opposite colored suits by enum value)
				if (tempCard.GetSuit() + 1 == m_playArea[column1].Peek().GetSuit() ||
					tempCard.GetSuit() + 3 == m_playArea[column1].Peek().GetSuit() ||
					tempCard.GetSuit() - 1 == m_playArea[column1].Peek().GetSuit() ||
					tempCard.GetSuit() - 3 == m_playArea[column1].Peek().GetSuit())
				{
					//Remove and save the next card from play area column & increment count of moved cards
					tempCard = m_playArea[column1].Pop();
					tempStack.Push(tempCard);
					numMovedCards++;
				}
				else
				{
					//Restore original column
					for (int i = 0; i < numMovedCards; i++)
					{
						m_playArea[column1].Push(tempStack.Pop());
					}
					throw Exception("ERROR: Not all cards to be moved are in the correct order.");
				}
			}
			else
			{
				//Restore original column
				for (int i = 0; i < numMovedCards; i++)
				{
					m_playArea[column1].Push(tempStack.Pop());
				}
				throw Exception("ERROR: Not all cards to be moved are in the correct order.");
			}
		}
	}
	else
		throw Exception("ERROR: Cannot move from an empty play area column.");

	//***Move card(s) to column

	//If column to move card(s) to is empty
	if (m_playArea[column2].isEmpty())
	{
		//Add each moved card to the play area column
		for (int i = 0; i < numMovedCards; i++)
		{
			m_playArea[column2].Push(tempStack.Pop());
		}
	}
	//Else if ranks are in order (first card to be added is one less than current top card of column) 
	else if (m_playArea[column2].Peek().GetRank() - tempStack.Peek().GetRank() == 1)			
	{
		//If suit colors are opposite (+-1 & +-3 specify the opposite colored suits by enum value)
		if (tempStack.Peek().GetSuit() + 1 == m_playArea[column2].Peek().GetSuit() ||
			tempStack.Peek().GetSuit() + 3 == m_playArea[column2].Peek().GetSuit() ||
			tempStack.Peek().GetSuit() - 1 == m_playArea[column2].Peek().GetSuit() ||
			tempStack.Peek().GetSuit() - 3 == m_playArea[column2].Peek().GetSuit())
		{
			//Add each moved card to the play area column
			for (int i = 0; i < numMovedCards; i++)
			{
				m_playArea[column2].Push(tempStack.Pop());
			}
		}
		else
		{
			//Restore original column
			for (int i = 0; i < numMovedCards; i++)
			{
				m_playArea[column1].Push(tempStack.Pop());
			}
			throw Exception("ERROR: Cannot move card(s) to that location. Invalid combination of cards.");
		}
	}
	else
	{
		//Restore original column
		for (int i = 0; i < numMovedCards; i++)
		{
			m_playArea[column1].Push(tempStack.Pop());
		}
		throw Exception("ERROR: Cannot move card(s) to that location. Invalid combination of cards.");
	}	
}

/**********************************************************************
* Purpose:
*	To move the card(s) from a play area column to a free cell.
*
* Precondition:
*	Two integers specifying the index of the column to move from and
*	the index of the free cell to move to.
*
* Postcondition:
*	The card(s) moved from one column to a free cell, if allowed.
**********************************************************************/
void Board::MovePlayToFree(int column, int freeCellIndex)
{
	//If not moving from an empty play area column
	if (!m_playArea[column].isEmpty())
	{
		//If desired free cell index is empty
		if (m_emptyFreeCell[freeCellIndex] == true)
		{
			//Remove card from play area and place in free cell
			m_freeCells[freeCellIndex] = m_playArea[column].Pop();
			//Set free cell to non-empty
			m_emptyFreeCell[freeCellIndex] = false;
		}
		else
			throw Exception("ERROR: Cannot put card in a filled free cell.");
	}
	else
		throw Exception("ERROR: Cannot move from an empty play area column.");
}

/**********************************************************************
* Purpose:
*	To move the card(s) from a play area column to a home cell.
*
* Precondition:
*	Two integers specifying the index of the column to move from and
*	the index of the home cell to move to.
*
* Postcondition:
*	The card(s) moved from one column to a home cell, if allowed.
**********************************************************************/
void Board::MovePlayToHome(int column, int homeCellIndex)
{
	//If not moving from an empty play area column
	if (!m_playArea[column].isEmpty())
	{
		//If desired home cell is empty
		if (m_homeCells[homeCellIndex].isEmpty())
		{
			//If card to be moved is an ACE, remove from play area and put as first card in desired home cell
			if (m_playArea[column].Peek().GetRank() == ACE)
				m_homeCells[homeCellIndex].Push(m_playArea[column].Pop());
			else
				throw Exception("ERROR: Cannot place that card as the first one in a home cell.");
		}
		else
		{
			//If ranks are in order (card to be added is one more than current top card of home cell) 
			if (m_playArea[column].Peek().GetRank() - m_homeCells[homeCellIndex].Peek().GetRank() == 1)
			{
				//If suits are same, remove card from play area and put as next card in desired home cell
				if (m_playArea[column].Peek().GetSuit() == m_homeCells[homeCellIndex].Peek().GetSuit())
					m_homeCells[homeCellIndex].Push(m_playArea[column].Pop());
				else
					throw Exception("ERROR: Cannot move card to that location. Invalid combination of cards.");
			}
			else
				throw Exception("ERROR: Cannot move card to that location. Invalid combination of cards.");
		}
	}
	else
		throw Exception("ERROR: Cannot move from an empty play area column.");
}

/**********************************************************************
* Purpose:
*	To move the card(s) from a free cell to a play area column.
*
* Precondition:
*	Two integers specifying the index of the free cell to move from,
*	and the index of the play area column to move to.
*
* Postcondition:
*	The card(s) moved from a free cell to a play area column, if
*	allowed.
**********************************************************************/
void Board::MoveFreeToPlay(int freeCellIndex, int column)
{
	//If not moving from an empty free cell
	if (m_emptyFreeCell[freeCellIndex] == false)
	{
		//If moving to an empty play area column
		if (m_playArea[column].isEmpty())
		{
			//Remove card from free cell and add to column of play area
			m_playArea[column].Push(m_freeCells[freeCellIndex]);
			//Set free cell to empty
			m_emptyFreeCell[freeCellIndex] = true;
		}
		else
		{
			//If ranks are in order (card to be added is one less than current top card of column)
			if (m_playArea[column].Peek().GetRank() - m_freeCells[freeCellIndex].GetRank() == 1)
			{
				//If suit colors are opposite (+-1 & +-3 specify the opposite colored suits by enum value)
				if (m_freeCells[freeCellIndex].GetSuit() + 1 == m_playArea[column].Peek().GetSuit() ||
					m_freeCells[freeCellIndex].GetSuit() + 3 == m_playArea[column].Peek().GetSuit() ||
					m_freeCells[freeCellIndex].GetSuit() - 1 == m_playArea[column].Peek().GetSuit() ||
					m_freeCells[freeCellIndex].GetSuit() - 3 == m_playArea[column].Peek().GetSuit())
				{
					//Remove card from free cell and add as next card in play area column
					m_playArea[column].Push(m_freeCells[freeCellIndex]);
					//Set free cell to empty
					m_emptyFreeCell[freeCellIndex] = true;
				}
				else
					throw Exception("ERROR: Cannot move card to that location. Invalid combination of cards.");
			}
			else
				throw Exception("ERROR: Cannot move card to that location. Invalid combination of cards.");
		}
	}
	else
		throw Exception("ERROR: Cannot move from an empty free cell.");
}

/**********************************************************************
* Purpose:
*	To move the card(s) from a free cell to a home cell.
*
* Precondition:
*	Two integers specifying the index of the free cell to move from,
*	and the index of the home cell to move to.
*
* Postcondition:
*	The card(s) moved from a free cell to a home cell, if allowed.
**********************************************************************/
void Board::MoveFreeToHome(int freeCellIndex, int homeCellIndex)
{
	//If not moving from an empty free cell
	if (m_emptyFreeCell[freeCellIndex] == false)
	{
		//If desired home cell is empty
		if (m_homeCells[homeCellIndex].isEmpty())
		{
			//If card to be moved is an ACE
			if (m_freeCells[freeCellIndex].GetRank() == ACE)
			{
				//Remove card from free cell and put as first card in desired home cell
				m_homeCells[homeCellIndex].Push(m_freeCells[freeCellIndex]);
				//Set free cell to empty
				m_emptyFreeCell[freeCellIndex] = true;
			}
			else
				throw Exception("ERROR: Cannot place that card as the first one in a home cell.");
		}
		else
		{
			//If ranks are in order (card to be added is one more than current top card in home cell)
			if (m_freeCells[freeCellIndex].GetRank() - m_homeCells[homeCellIndex].Peek().GetRank() == 1)
			{
				//If suits are the same
				if (m_freeCells[freeCellIndex].GetSuit() == m_homeCells[homeCellIndex].Peek().GetSuit())
				{
					//Remove card from free cell and put as next card in desired home cell
					m_homeCells[homeCellIndex].Push(m_freeCells[freeCellIndex]);
					//Set free cell to empty
					m_emptyFreeCell[freeCellIndex] = true;
				}
				else
					throw Exception("ERROR: Cannot move card to that location. Invalid combination of cards.");
			}
			else
				throw Exception("ERROR: Cannot move card to that location. Invalid combination of cards.");
		}
	}
	else
		throw Exception("ERROR: Cannot move from an empty free cell.");
}

/**********************************************************************
* Purpose:
*	To calculate maximum number of cards that can be moved from play
*	area to play area at one time.
*
* Precondition:
*	Called from the MovePlayToPlay() board method.
*
* Postcondition:
*	The maximum number of cards allowed to be moved is returned.
**********************************************************************/
int Board::CalculateMaxMovableCards(int destColumn)
{
	int numEmptyFreeCells = 0;	//Counts number of free cells that are empty
	int numEmptyPlayCells = 0;	//Counts number of play area columns that are empty

	//Check each free cell
	for (int i = 0; i < NUM_FREE_CELLS; i++)
	{
		//If empty, increment count of number of empty free cells
		if (m_emptyFreeCell[i] == true)
			numEmptyFreeCells++;
	}

	//Check each play area column
	for (int i = 0; i < NUM_PLAY_CELLS; i++)
	{
		//If empty, increment count of number of empty play area columns
		if (m_playArea[i].isEmpty())
			numEmptyPlayCells++;
	}

	//If play area column to move card(s) to is empty, decrement count of number of empty play area columns
	if (m_playArea[destColumn].isEmpty())
		numEmptyPlayCells--;

	//Return calculated max number of cards to be moved
	return ((1 + numEmptyFreeCells) * pow(2, numEmptyPlayCells));
}

/**********************************************************************
* Purpose:
*	To display the cards in the free cell area, home cell area, and
*	play area.
*
* Precondition:
*	<None>
*
* Postcondition:
*	The cards are displayed on the board in their current locations.
**********************************************************************/
void Board::DisplayBoard()
{
	system("cls");	//Clear screen

	bool emptyPlayCell[NUM_PLAY_CELLS] = { false };		//Flags whether each play area column is empty
	bool noMorePlayCells = false;		//Flags whether all play area columns are empty

	//***Display Free Cell Area

	//For each free cell
	for (int i = 0; i < NUM_FREE_CELLS; i++)
	{
		//Display card if not empty
		if (m_emptyFreeCell[i] == false)
		{
			cout << " ";
			DisplaySingleCard(m_freeCells[i]);
		}
		//Display empty space if empty
		else
		{
			cout << " ";
			DisplayEmptyCell();
		}
	}

	cout << "          ";		//Add space between free cell and home cell areas

	//***Display Home Cell Area

	//For each home cell
	for (int i = 0; i < NUM_HOME_CELLS; i++)
	{
		//Display top card of home cell if not empty
		if (!m_homeCells[i].isEmpty())
		{
			cout << " ";
			DisplaySingleCard(m_homeCells[i].Peek());
		}
		//Display empty space if empty
		else
		{
			cout << " ";
			DisplayEmptyCell();
		}
	}

	//Display index values for free cell area
	cout << "\n";
	for (int i = 0; i < NUM_FREE_CELLS; i++)
		cout << "   " << i << " ";
	
	//Display index values for home cell area
	cout << "          ";
	for (int i = 0; i < NUM_HOME_CELLS; i++)
		cout << "   " << i << " ";

	//Display index values for play area
	cout << "\n\n     ";
	for (int i = 0; i < NUM_PLAY_CELLS; i++)
		cout << "   " << i << " ";

	//***Display Play Area

	Array<StackLL<Card>> playAreaCopy(m_playArea);	//Copy of current play area that can be changed
	Array<StackLL<Card>> tempPlayArea;		//To hold cards in opposite order
	tempPlayArea.setLength(NUM_PLAY_CELLS);		//8 play cells

	//Reverse order of cards in each stack of the play area
	while (noMorePlayCells == false)		//Loop through each row of play cells
	{
		noMorePlayCells = true;

		for (int i = 0; i < NUM_PLAY_CELLS; i++)	//Loop through each column of play cells
		{
			//Remove and store top card if given column is not empty
			if (!playAreaCopy[i].isEmpty())
				tempPlayArea[i].Push(playAreaCopy[i].Pop());
			else
				emptyPlayCell[i] = true;	//Mark given column as empty
		}

		//Check if all columns are empty
		for (int i = 0; i < NUM_PLAY_CELLS; i++)
		{
			//If any not empty, keep looping and reversing order of cards
			if (emptyPlayCell[i] == false)
				noMorePlayCells = false;
		}
	}
	
	//Reset all flags to false
	for (int i = 0; i < NUM_PLAY_CELLS; i++)
		emptyPlayCell[i] = false;

	noMorePlayCells = false;

	//Display each card of the play area
	while (noMorePlayCells == false)		//Loop through each row of play cells
	{
		noMorePlayCells = true;
		cout << "\n     ";		//Move down a line and indent 5 spaces from edge

		for (int i = 0; i < NUM_PLAY_CELLS; i++)	//Loop through each column of play cells
		{
			//Remove and display top card if given column not empty
			if (!tempPlayArea[i].isEmpty())
			{
				cout << " ";
				DisplaySingleCard(tempPlayArea[i].Pop());
			}
			else
			{
				cout << "     ";		//Display empty space
				emptyPlayCell[i] = true;	//Mark given column as empty
			}
		}

		//Check if all columns are empty
		for (int i = 0; i < NUM_PLAY_CELLS; i++)
		{
			//If not empty, keep looping and displaying
			if (emptyPlayCell[i] == false)
				noMorePlayCells = false;
		}
	}

	cout << "\n";
}

/**********************************************************************
* Purpose:
*	To display a single spot where a card could be placed.
*
* Precondition:
*	Called from the DisplayBoard() method.
*
* Postcondition:
*	A single empty card spot is dispayed.
**********************************************************************/
void Board::DisplayEmptyCell()
{
	SetConsoleTextAttribute(handle, 136);	//Gray text on gray background
	cout << "    ";							//Display blank area for a card
	SetConsoleTextAttribute(handle, 7);		//Reset screen to default colors
}

/**********************************************************************
* Purpose:
*	To display a single card.
*
* Precondition:
*	A Card object passed by const ref. This method is called from the
*	DisplayBoard() method.
*
* Postcondition:
*	The rank and suit of a card is displayed as a card on the board.
**********************************************************************/
void Board::DisplaySingleCard(const Card & card)
{
	string rank = ConvertRank(card);	//Rank string/character to be displayed
	char suit = ConvertSuit(card);		//Suit character to be displayed

	//If card is a red suit
	if (card.GetSuit() == HEART || card.GetSuit() == DIAMOND)
	{
		SetConsoleTextAttribute(handle, 124);	//Red text on gray background
		cout << setw(2) << rank << " " << suit;	//Display rank and suit
		SetConsoleTextAttribute(handle, 7);		//Reset screen to default colors
	}
	//Else card is a black suit
	else
	{
		SetConsoleTextAttribute(handle, 112);	//Black text on gray background
		cout << setw(2) << rank << " " << suit;	//Display rank and a spade
		SetConsoleTextAttribute(handle, 7);		//Reset screen to default colors
	}
}

/**********************************************************************
* Purpose:
*	To convert the Rank enum value of a card to an actual symbol
*	(number or letter) that can be displayed to represent that rank.
*
* Precondition:
*	A Card object passed by const ref. This method is called from the
*	DisplaySingleCard() method.
*
* Postcondition:
*	The rank of a card is converted to a symbol that will be used to 
*	display the rank.
**********************************************************************/
string Board::ConvertRank(const Card & card)
{
	string rank;	//Assigned a rank string/character to display

	if (card.GetRank() == ACE)
		rank = "A";
	else if (card.GetRank() == TEN)
		rank = "10";
	else if (card.GetRank() == JACK)
		rank = "J";
	else if (card.GetRank() == QUEEN)
		rank = "Q";
	else if (card.GetRank() == KING)
		rank = "K";
	else
		rank = card.GetRank() + 48;	//+48 coverts rank value to an ascii number

	return rank;
}

/**********************************************************************
* Purpose:
*	To convert the Suit enum value of a card to an actual symbol
*	(number or letter) that can be displayed to represent that suit.
*
* Precondition:
*	A Card object passed by const ref. This method is called from the
*	DisplaySingleCard() method.
*
* Postcondition:
*	The suit of a card is converted to a symbol that will be used to 
*	display the suit.
**********************************************************************/
char Board::ConvertSuit(const Card & card)
{
	char suit;		//Assigned a suit character to display

	if (card.GetSuit() == HEART)
		suit = 3;	//ascii 3 is a heart character
	else if (card.GetSuit() == DIAMOND)
		suit = 4;	//ascii 4 is a diamond character
	else if (card.GetSuit() == CLUB)
		suit = 5;	//ascii 5 is a club character
	else if (card.GetSuit() == SPADE)
		suit = 6;	//ascii 6 is a spade character

	return suit;
}

/**********************************************************************
* Purpose:
*	To check if the user has won the game by placing all cards in order
*	in all of the home cells.
*
* Precondition:
*	<None>
*
* Postcondition:
*	A bool specifying whether the user won the game is returned.
**********************************************************************/
bool Board::WonGame()
{
	bool wonGame = false;		//Flags whether user won game
	int numFullHomeCells = 0;	//Counts number of home cells that are full

	//Check if each home cell is full
	for (int i = 0; i < NUM_HOME_CELLS; i++)
	{
		//If home cell is full, increment count of home cells that are full
		if (m_homeCells[i].isFull())
			numFullHomeCells++;		
	}

	//If all home cells are full, user won game
	if (numFullHomeCells == NUM_HOME_CELLS)
		wonGame = true;

	return wonGame;
}

/**********************************************************************
* Purpose:
*	To clear the original data from the free cells, home cells, and
*	the play area, and then call the CreateBoard() method to re-shuffle
*	the deck and re-distribute the cards to the play area.
*
* Precondition:
*	The board has cards in any location.
*
* Postcondition:
*	The board areas are cleared of all cards, and then the board is
*	recreated with a random distribution of all cards to the play area.
**********************************************************************/
void Board::ResetNewBoard()
{
	m_freeCells.setLength(0);	//clear original data from free cells
	m_homeCells.setLength(0);	//clear original data from home cells
	m_playArea.setLength(0);	//clear original data from play area cells

	//Reset all free cells to empty
	for (int i = 0; i < NUM_FREE_CELLS; i++)
		m_emptyFreeCell[i] = true;

	CreateBoard();		//Re-create the board
}