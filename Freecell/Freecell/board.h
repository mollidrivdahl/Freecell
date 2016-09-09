/**********************************************************************
* Author:			Molli Drivdahl
* Filename:			board.h
* Date Created:		2/2/16
* Modifications:	2/8/16
*
* Class: Board
*
* Purpose:
*	This class symbolizes the board of the Freecell game. It manages
*	all the changes to the areas that contain the cards.
*
* Manager functions:
*	Board()
*		Creates a board with a free cell area, a home cell area, and
*		a play area with 52 cards, each initialized through the call to
*		the CreateBoard() method. A bool array to flag each free cell as
*		empty is initialized to true for each element.
*
*	Board(const Board & copy)
*
*	~Board()
*
*	Board & operator=(const Board & rhs)
*
* Methods:
*	void CreateBoard()
*		Distributes shuffled cards to the play area on board, and
*		gives the free cell area empty card cells and the home cell
*		area empty stacks for future cards.
*
*	void MovePlayToPlay(int column1, int column2, int numCards)
*		Moves card(s) from a play area column to a different play area
*		column.
*
*	void MovePlayToFree(int column, int freeCellIndex)
*		Moves card from a play area column to a free cell.
*
*	void MovePlayToHome(int column, int homeCellIndex)
*		Moves card from a play area column to a home cell stack.
*
*	void MoveFreeToPlay(int freeCellIndex, int column)
*		Moves card from a free cell to a play area column.
*
*	void MoveFreeToHome(int freeCellIndex, int homeCellIndex)
*		Moves card from a free cell to a home cell stack.
*
*	int CalculateMaxMovableCards(int destColumn)
*		Determines maximum number of cards that can be moved at the
*		same time from column to column in the play area.
*
*	void DisplayBoard()
*		Displays the current location of the cards on the board.
*
*	void DisplayEmptyCell()
*		Displays an empty cell location for a card.
*
*	void DisplaySingleCard(const Card & card)
*		Displays an individual card on the board.
*
*	string ConvertRank(const Card & card)
*		Converts a rank value to a character/string that will be
*		displayed to represent that rank of the given card.
*
*	char ConvertSuit(const Card & card)
*		Converts a suit value to a character that will be displayed to
*		represent that suit of the given card.
*
*	bool WonGame()
*		Checks if the user won the game.
*
*	void ResetNewBoard()
*		Clears the original data from the free cells, home cells, and
*		and play area, and then calls the CreateBoard() method to re-
*		shuffle the deck and re-distribute the cards to the play area.
**********************************************************************/
#ifndef BOARD_H
#define BOARD_H

#include "stackArray.h"
#include "stackLL.h"
#include "deck.h"

#include <string>
using std::string;

const int NUM_FREE_CELLS = 4;
const int NUM_HOME_CELLS = 4;
const int NUM_PLAY_CELLS = 8;

class Board
{
	public:
		//Default Ctor
		Board();

		//Copy Ctor
		Board(const Board & copy);

		//Default Dtor
		~Board();

		//Assignment Operator
		Board & operator=(const Board & rhs);

		//Move from Play Area to Play Area
		void MovePlayToPlay(int column1, int column2, int numCards);

		//Move from Play Area to Free Cell Area
		void MovePlayToFree(int column, int freeCellIndex);

		//Move from Play Area to Home Cell Area
		void MovePlayToHome(int column, int homeCellIndex);

		//Move from Free Cell Area to Play Area
		void MoveFreeToPlay(int freeCellIndex, int column);

		//Move from Free Cell Area to Home Cell Area
		void MoveFreeToHome(int freeCellIndex, int homeCellIndex);

		//Display the current location of cards on the board
		void DisplayBoard();

		//Check if user won the game
		bool WonGame();

		//Reset game to start over
		void ResetNewBoard();

	private:
		//Distribute cards on board
		void CreateBoard();

		//Determine max number of cards to move
		int CalculateMaxMovableCards(int destColumn);

		//Display an empty cell location for a card
		void DisplayEmptyCell();

		//Display an individual card on the board
		void DisplaySingleCard(const Card & card);

		//Convert rank value to a character to be displayed
		string ConvertRank(const Card & card);

		//Convert suit value to a character to be displayed
		char ConvertSuit(const Card & card);

		Array<Card> m_freeCells;				//Cards in Free Cell Area
		Array<StackArray<Card>> m_homeCells;	//Stack of Cards in Home Cell Area
		Array<StackLL<Card>> m_playArea;		//Stack of Cards in Play Area
		bool m_emptyFreeCell[NUM_FREE_CELLS];	//Flags whether each Free Cell is empty
};

#endif //BOARD_H