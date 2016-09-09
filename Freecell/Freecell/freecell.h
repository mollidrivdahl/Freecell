/**********************************************************************
* Author:			Molli Drivdahl
* Filename:			freecell.h
* Date Created:		2/2/16
* Modifications:	2/8/16
*
* Class: Freecell
*
* Purpose:
*	This class controls the flow of the Freecell game. It also provides
*	the interface to the Freecell game from the user's perspective.
*
* Manager functions:
*	Freecell()
*		Creates a Freecell game with a board to hold the cards and
*		the bool to signal the end of the game, initialized to false.
*
*	Freecell(const Freecell & copy)
*
*	~Freecell()
*
*	Freecell & operator=(const Freecell & rhs)
*
* Methods:
*	void RunGame()
*		Provides the entrance into the game and exit out of the game.
*
*	void GameLoop()
*		Runs the game until the user wins or quits.
*
*	void ChooseAction()
*		Allows user to choose move to make on board.
*
*	void InterpretActionChoice(int choice)
*		Determines which action the user wanted to do.
*
*	void MovePlayToPlay()
*		Allows user to specify which card(s) to move from play area
*		column to play area column.
*
*	void MovePlayToFree()
*		Allows user to specify which card to move from play area to
*		free cell area.
*
*	void MovePlayToHome()
*		Allows user to specify which card to move from play area to
*		home cell area.
*
*	void MoveFreeToPlay()
*		Allows user to specify which card to move from free cell area
*		to play area column.
*
*	void MoveFreeToHome()
*		Allows user to specify which card to move from free cell area
*		to home cell area.
**********************************************************************/
#ifndef FREECELL_H
#define FREECELL_H

#include "board.h"

class Freecell
{
	public:
		//Default Ctor
		Freecell();
		
		//Copy Ctor
		Freecell(const Freecell & copy);

		//Default Dtor
		~Freecell();

		//Assignment Operator
		Freecell & operator=(const Freecell & rhs);

		//Provides entrance into game and exit out of game.
		void RunGame();

	private:
		//Runs the game until the user wins or quits
		void GameLoop();

		//Allows user to choose move to make on board
		void ChooseAction();

		//Determines which action the user wanted to do
		void InterpretActionChoice(int choice);

		//Allows user to specify which card(s) to move from play area column to play area column
		void MovePlayToPlay();

		//Allows user to specify which card to move from play area to free cell area
		void MovePlayToFree();

		//Allows user to specify which card to move from play area to home cell area
		void MovePlayToHome();

		//Allows user to specify which card to move from free cell area to play area column
		void MoveFreeToPlay();

		//Allows user to specify which card to move from free cell area to home cell area
		void MoveFreeToHome();

		Board m_gameBoard;	//Freecell game board
		bool m_endGame;		//Flag that the game has ended
};

#endif //FREECELL_H