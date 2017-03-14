#include "FBullCowGame.h"
#include <map>
#define TMap std::map


using FString = std::string;
using int32 = int;


FBullCowGame::FBullCowGame() //default constructor
{
	this->Reset();
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const {return this->bGameIsWon;}


int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,5}, {4,7}, {5,9}, {6,11} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}


void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 3;
	const FString HIDDEN_WORD = "lmao"; //this must be an isogram

	this->MyMaxTries = MAX_TRIES;
	this->MyHiddenWord = HIDDEN_WORD;
	this->bGameIsWon = false;
	this->MyCurrentTry = 1;
	return;
}



EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))//if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram; 
	}
	else  if (!IsLowerCase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != this->GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	} 
	else 
	{
		return EGuessStatus::OK;
	}
	return EGuessStatus::OK; // TODO make actual error
}

// reveives a VALID guess, increments turn,
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	this->MyCurrentTry++;
	FBullCowCount BullCowCount; //auto inits to 0
	int32 WordLength = MyHiddenWord.length(); //assuming the same length as guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the hidden word
		for(int32 GChar = 0; GChar < WordLength; GChar++) {
			//if they match then
			if ( Guess[GChar] == this->MyHiddenWord[MHWChar]) {
				// if they're in the same place
				if (MHWChar == GChar) {
					BullCowCount.Bulls++; //increment bulls
				}
				else {
					BullCowCount.Cows++; // increment cows if not
				}
			}
		}
	}
	if (BullCowCount.Bulls == this->GetHiddenWordLength()) {
		this->bGameIsWon = true;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter words as isogramsinit a map, 
	if (Word.length() <= 1) { return true; }
	TMap<char, bool> LetterSeen;

	for (auto Letter : Word) {	//loop through the FString 

		Letter = tolower(Letter);
		if (LetterSeen[Letter]) { 		//if letter is in the map
										//we do not have an isogram
			return false;
		}
		LetterSeen[Letter] = true;//otherwise
			//we add the letter to the map as seen
	}	
		
	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word)
	{
		// if not a lower case letter
		if (!islower(Letter)) {
			return false;
		}
	}
	//otherwise
	return true;
}
