/**********************************************************************
* Author:			Molli Drivdahl
* Filename:			freecell.cpp
* Date Created:		2/2/16
* Modifications:	2/8/16
**********************************************************************/

#include "freecell.h"

#include <iostream>
using std::cout;
using std::cin;

/**********************************************************************
* Purpose:
*	To construct an instance of an Freecell and initialize the bool
*	that flags whether the game has ended to false.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data members are initialized to default values.
**********************************************************************/
Freecell::Freecell() : m_endGame(false)
{}

/**********************************************************************
* Purpose:
*	To construct an instance of an Freecell game with data members
*	whose initial values are copied from data members of an existing
*	Freecell object.
*
* Precondition:
*	An existing Freecell object passed by const ref.
*
* Postcondition:
*	The data members are initialized to the values of the data members
*	of the existing Freecell object.
**********************************************************************/
Freecell::Freecell(const Freecell & copy) : m_endGame(false)
{
	*this = copy;	//Use assignment operator
}

/**********************************************************************
* Purpose:
*	To destroy the Freecell game object and reset the data members to
*	default values.
*
* Precondition:
*	<None>
*
* Postcondition:
*	Data members are reset to default values.
**********************************************************************/
Freecell::~Freecell()
{
	//Reset to default value
	m_endGame = false;
}

/**********************************************************************
* Purpose:
*	To assign one existing Freecell object to another existing Freecell
*	object by copying values of data members from one to another.
*
* Precondition:
*	An existing Freecell object passed by const ref.
*
* Postcondition:
*	One existing Freecell object is assigned to another existing
*	Freecell object.
**********************************************************************/
Freecell & Freecell::operator=(const Freecell & rhs)
{
	//Check for self-assignment
	if (this != &rhs)
	{
		m_gameBoard = rhs.m_gameBoard;	//Use Board's assignment operator
		m_endGame = rhs.m_endGame;
	}

	return *this;
}

/**********************************************************************
* Purpose:
*	To provide the entry into the game and exit out of the game.
*
* Precondition:
*	<None>
*
* Postcondition:
*	The user chooses whether or not to play again.
**********************************************************************/
void Freecell::RunGame()
{
	char playAgain = '\0';	//Contains user's choice whether to play again

	do
	{
		//Upon starting the game
		system("cls");

		cout << "\t\tWelcome to Freecell!\n\n";

		GameLoop();

		//Upon finishing the game
		cout << "\nDo you want to play again? (y/n): ";
		cin >> playAgain;

	}
	while (playAgain == 'y');

	cout << "\nThanks for playing!\n\n";
}

/**********************************************************************
* Purpose:
*	To run the main portion of the game until the user either wins or
*	quits.
*
* Precondition:
*	The cards have been distributed randomly to the board.
*
* Postcondition:
*	The game has been reset to a beginning state so that the user
*	can play again if he or she chooses. 
**********************************************************************/
void Freecell::GameLoop()
{
	//Display initial game board
	m_gameBoard.DisplayBoard();

	//Stay in loop until user wins or quits
	while (m_endGame != true)
	{
		ChooseAction();
	}

	//Reset state of game to be able to start over
	m_gameBoard.ResetNewBoard();
	m_endGame = false;
}

/**********************************************************************
* Purpose:
*	To allow the user to choose where to move the cards to and from on
*	the board.
*
* Precondition:
*	Called throughout the course of the game from the GameLoop()
*	method.
*
* Postcondition:
*	The user chooses an action to take, and the InterpretActionChoice()
*	method is called and passed the user's action choice.
**********************************************************************/
void Freecell::ChooseAction()
{
	int choice = 0;		//Contains user menu choice for board action

	cout << "\n\nPlease select an action for moving the cards:\n"
		<< "1) Move from play area to play area\n"
		<< "2) Move from play area to free cell area\n"
		<< "3) Move from play area to home cell area\n"
		<< "4) Move from free cell area to play area\n"
		<< "5) Move from free cell area to home area\n"
		<< "6) Quit this game\n";
	cout << "Your choice: ";
	cin >> choice;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int

	while (choice < 1 || choice > 6)
	{
		cout << "\nChoice must be a number between 1 and 6. Please try again: ";
		cin >> choice;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int
	}

	InterpretActionChoice(choice);
}

/**********************************************************************
* Purpose:
*	To call the appropriate method, or set the flag to end the game,
*	based on the user's choice of action.
*
* Precondition:
*	An integer specifying the user's action choice.
*
* Postcondition:
*	The appropriate method is called or the flag to end the game is
*	set based on the user's choice of actions.
**********************************************************************/
void Freecell::InterpretActionChoice(int choice)
{
	//Choose appropriate choice of action
	switch (choice)
	{
	case 1:
		MovePlayToPlay();
		break;
	case 2:
		MovePlayToFree();
		break;
	case 3:
		MovePlayToHome();
		break;
	case 4:
		MoveFreeToPlay();
		break;
	case 5:
		MoveFreeToHome();
		break;
	case 6:
		m_endGame = true;
		break;
	}
}

/**********************************************************************
* Purpose:
*	To allow the user to specify which card(s) to move from one play
*	area column to another play area column.
*
* Precondition:
*	User choose to move card from play area to play area.
*
* Postcondition:
*	Card(s) moved from one play area column to another play area
*	column, if acceptable.
**********************************************************************/
void Freecell::MovePlayToPlay()
{
	//-1 protects from specifying a cell if a char gets stored into int
	int column1 = -1;	//User specified column to move card(s) from
	int column2 = -1;	//User specified column to move card(s) to
	int numCards = 0;	//User specified number of cards to move

	//Display current game board and key symbols on board
	m_gameBoard.DisplayBoard();

	//Prompt for which column to move from
	cout << "\nPlease enter which column (0-7) to move the card(s) FROM: ";
	cin >> column1;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int

	while (column1 < 0 || column1 > 7)
	{
		cout << "\nChoice must be a number between 0 and 7. Please try again: ";
		cin >> column1;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int
	}

	//Prompt for which column to move to
	cout << "\nPlease enter which column (0-7) to move the card(s) TO: ";
	cin >> column2;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int

	while (column2 < 0 || column2 > 7 || column2 == column1)
	{
		cout << "\nChoice must be a number between 0 and 7, different from the first column value. Please try again: ";
		cin >> column2;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int
	}

	//Prompt for number of cards to move
	cout << "\nPlease enter the number of cards to move: ";
	cin >> numCards;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int

	//If trying to move zero or less cards
	if (numCards <= 0)
	{
		m_gameBoard.DisplayBoard();
		cout << "\nERROR: Cannot move zero cards.";
	}
	else
	{
		try
		{
			//Move cards from one column to another in play area, and re-display board
			m_gameBoard.MovePlayToPlay(column1, column2, numCards);
			m_gameBoard.DisplayBoard();
		}
		catch (Exception & ex)
		{
			//Re-display board and display exception
			m_gameBoard.DisplayBoard();
			cout << "\n" << ex;
		}
	}
}

/**********************************************************************
* Purpose:
*	To allow the user to specify which card to move from one play area
*	column to a free cell.
*
* Precondition:
*	User choose to move card from play area to free cell.
*
* Postcondition:
*	Card moved from one play area column to a chosen free cell, if
*	acceptable.
**********************************************************************/
void Freecell::MovePlayToFree()
{
	//-1 protects from specifying a cell if a char gets stored into int
	int column = -1;	//User specified column to move card from
	int index = -1;		//User specified free cell index to move card to

	//Display current game board and key symbols on board
	m_gameBoard.DisplayBoard();

	//Prompt for which column to move from
	cout << "\nPlease enter which column (0-7) to move the card FROM: ";
	cin >> column;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int

	while (column < 0 || column > 7)
	{
		cout << "\nChoice must be a number between 0 and 7. Please try again: ";
		cin >> column;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int
	}

	//Prompt for which free cell to move card to
	cout << "\nPlease enter which free cell (0-3) to move the card TO: ";
	cin >> index;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int

	while (index < 0 || index > 3)
	{
		cout << "\nChoice must be a number between 0 and 3. Please try again: ";
		cin >> index;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int
	}

	try
	{
		//Move cards from a column to a free cell, and re-display board
		m_gameBoard.MovePlayToFree(column, index);
		m_gameBoard.DisplayBoard();
	}
	catch (Exception & ex)
	{
		//Re-display board and display exception
		m_gameBoard.DisplayBoard();
		cout << "\n" << ex;
	}
}

/**********************************************************************
* Purpose:
*	To allow the user to specify which card to move from one play area
*	column to a home cell.
*
* Precondition:
*	User choose to move card from play area to home cell.
*
* Postcondition:
*	Card moved from one play area column to a chosen home cell, if
*	acceptable.
**********************************************************************/
void Freecell::MovePlayToHome()
{
	//-1 protects from specifying a cell if a char gets stored into int
	int column = -1;	//User specified column to move card from
	int index = -1;		//User specified home cell index to move card to

	//Display current game board and key symbols on board
	m_gameBoard.DisplayBoard();

	//Prompt for which column to move from
	cout << "\nPlease enter which column (0-7) to move the card FROM: ";
	cin >> column;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int

	while (column < 0 || column > 7)
	{
		cout << "\nChoice must be a number between 0 and 7. Please try again: ";
		cin >> column;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int
	}

	//Prompt for which home cell to move card to
	cout << "\nPlease enter which home cell (0-3) to move the card TO: ";
	cin >> index;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int

	while (index < 0 || index > 3)
	{
		cout << "\nChoice must be a number between 0 and 3. Please try again: ";
		cin >> index;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int
	}

	try
	{
		//Move cards from a column to a free cell, and re-display board
		m_gameBoard.MovePlayToHome(column, index);
		m_gameBoard.DisplayBoard();
	}
	catch (Exception & ex)
	{
		//Re-display board and display exception
		m_gameBoard.DisplayBoard();
		cout << "\n" << ex;
	}

	//Check if user won game
	if (m_gameBoard.WonGame() == true)
	{
		m_endGame = true;
		cout << "\n\nYou won!\n\n";
	}
}

/**********************************************************************
* Purpose:
*	To allow the user to specify which card to move from a free cell to
*	a play area column.
*
* Precondition:
*	User choose to move card from free cell to play area column.
*
* Postcondition:
*	Card moved from a free cell to a play area column, if acceptable.
**********************************************************************/
void Freecell::MoveFreeToPlay()
{
	//-1 protects from specifying a cell if a char gets stored into int
	int column = -1;	//User specified column to move card to
	int index = -1;		//User specified free cell index to move card from

	//Display current game board and key symbols on board
	m_gameBoard.DisplayBoard();

	//Prompt for which free cell to move card from
	cout << "\nPlease enter which free cell (0-3) to move the card FROM: ";
	cin >> index;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int

	while (index < 0 || index > 3)
	{
		cout << "\nChoice must be a number between 0 and 3. Please try again: ";
		cin >> index;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int
	}

	//Prompt for which column to move card to
	cout << "\nPlease enter which column (0-7) to move the card TO: ";
	cin >> column;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int

	while (column < 0 || column > 7)
	{
		cout << "\nChoice must be a number between 0 and 7. Please try again: ";
		cin >> column;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int
	}

	try
	{
		//Move cards from a free cell to a play area column, and re-display board
		m_gameBoard.MoveFreeToPlay(index, column);
		m_gameBoard.DisplayBoard();
	}
	catch (Exception & ex)
	{
		//Re-display board and display exception
		m_gameBoard.DisplayBoard();
		cout << "\n" << ex;
	}
}

/**********************************************************************
* Purpose:
*	To allow the user to specify which card to move from a free cell to
*	a home cell.
*
* Precondition:
*	User choose to move card from free cell to home cell.
*
* Postcondition:
*	Card moved from a free cell to a home cell, if acceptable.
**********************************************************************/
void Freecell::MoveFreeToHome()
{
	//-1 protects from specifying a cell if a char gets stored into int
	int freeCellIndex = -1;		//User specified free cell index to move card from
	int homeCellIndex = -1;		//User specified home cell index to move card to

	//Display current game board and key symbols on board
	m_gameBoard.DisplayBoard();

	//Prompt for which free cell to move card from
	cout << "\nPlease enter which free cell (0-3) to move the card FROM: ";
	cin >> freeCellIndex;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int

	while (freeCellIndex < 0 || freeCellIndex > 3)
	{
		cout << "\nChoice must be a number between 0 and 3. Please try again: ";
		cin >> freeCellIndex;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int
	}

	//Prompt for which home cell to move card to
	cout << "\nPlease enter which home cell (0-3) to move the card TO: ";
	cin >> homeCellIndex;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int

	while (homeCellIndex < 0 || homeCellIndex > 3)
	{
		cout << "\nChoice must be a number between 0 and 3. Please try again: ";
		cin >> homeCellIndex;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());	//In case char goes into an int
	}

	try
	{
		//Move cards from a free cell to a home cell, and re-display board
		m_gameBoard.MoveFreeToHome(freeCellIndex, homeCellIndex);
		m_gameBoard.DisplayBoard();
	}
	catch (Exception & ex)
	{
		//Re-display board and display exception
		m_gameBoard.DisplayBoard();
		cout << "\n" << ex;
	}

	//Check if user won game
	if (m_gameBoard.WonGame() == true)
	{
		m_endGame = true;
		cout << "\n\nYou won!\n\n";
	}
}