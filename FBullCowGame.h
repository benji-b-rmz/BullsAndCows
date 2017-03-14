#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// all values initialized to 0
struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

enum class EResetStatus {
	No_Hidden_Word,
	OK
};

class FBullCowGame 
{
public:
	FBullCowGame(); // constructor
	void Reset();
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	
	//  counts bulls & cows, and increasing try # assuming valid guess
	FBullCowCount SubmitValidGuess(FString);

private:
	// see constructor for initialization
	int32 MyMaxTries = 5;
	int32 MyCurrentTry = 1;
	FString MyHiddenWord;
	bool bGameIsWon = false;
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};