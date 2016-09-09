/**********************************************************************
* Author:			Molli Drivdahl
* Filename:			stub.cpp
* Date Created:		2/2/16
* Modifications:	2/8/16
*
* Lab/Assignment: Lab 3 - Freecell
*
* Overview:
*	This program simulates the classic Freecell game. There are 3 areas
*	on the board: Free cells, home cells, and the play area. Cards can
*	be moved from play area to play area, from play area to free a free
*	cell, from play area to a home cell, from a free cell to play area,
*	or from a free cell to a home cell. The goal is to place all cards
*	in the home cells, with each of the four stacks accending from Ace
*	to King of the same suit per stack. Only one card can be placed in
*	each free cell. Cards can only be placed on other cards in the play
*	area if the new card is one rank lower and the opposite color of the
*	card it's placed on. Multiple cards can be moved from play area to
*	play area only if all cards to be moved are in decending order and
*	alternating colors.
*
* Input:
*	The input comes from the user from keyboard. The user will type
*	numbers to specify menu options and columns or cells to move the
*	cards to or from.
*
* Output:
*	The output will be displayed to the screen. Instructions for the
*	user, error messages to the user, and a the game board will be
*	displayed to the screen. 
**********************************************************************/
#include "freecell.h"

#include <crtdbg.h> 
#define _CRTDBG_MAP_ALLOC

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Freecell freecellGame;	//Create a game
	freecellGame.RunGame();	//Start the game

	system("pause");

	return 0;
}