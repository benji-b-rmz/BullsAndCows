//Benjamin Ramirez
/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"


using FText = std::string;
using int32 = int;

// fucntion prototypes as outside a class
void PrintIntro();
FText GetValidGuess();
void PlayGame();
bool  AskToPlayAgain();

FBullCowGame BCGame; //instantiate a new game

int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0; 
}

//introduce the game
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game\n" << std::endl;
	std::cout << "Can you guess the" << BCGame.GetHiddenWordLength() << " letter isogram that I'm thinking of?\n";
	std::cout << "You have: " << BCGame.GetMaxTries() << " Tries, Good Luck :)!\n";
	std::cout << std::endl;
}

//loop continually until the user puts a valid guess
FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do 
	{
		//get a guess from the user
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try: " << CurrentTry << ". Enter your guess: ";
		FText Guess = " ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n";
		default:
			// assume the guess is valid
			return Guess;
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors

	return Guess;
}

void PrintGameSummary() 
{

	if (BCGame.IsGameWon()) {
		std::cout << "WELL DONE !!!\n\n";
	}
	else {
		std::cout << "BETTER LUCK NEXT TIME LMAO\n\n";
	}

}

// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses
	// is NOT won and there are still tries remaining
	while( !BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) 
	{
		FText Guess = GetValidGuess(); // TODO make loop checking validity

									   // submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << "Cows = " << BullCowCount.Cows << std::endl;
	}
	
	// TODO summarise game
	PrintGameSummary();
}


bool AskToPlayAgain() 
{
	std::cout << "\nWant to play again?\n" << "y for yes, n for no: ";
	FText Response = "";
	std::getline(std::cin, Response);
	return ((Response[0] == 'y') || (Response[0] == 'Y'));
}