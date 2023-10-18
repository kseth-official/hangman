#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h> // Windows Specific

#include "AnimationState.h"

class Hangman
{
private:
	int hangAnimation;
	std::string player;
	std::string phrase;
	std::vector<char> charactersToDisplay;

	void retrieveTextFrom(std::string filename);
public:
	Hangman() : hangAnimation(AnimationState::INITIAL), player("one") {}

	void execute();
	void displayRules();
	void enterThePhrase();
	void playGame();
	void displayAnimation();
	void displayPhraseLayout();
	void guessLetter();
	bool isLetterInPhrase(char letter);
	void guessWord();
	void displayLetters();
	bool hasBeenGuessed(char letter);
	bool isManHanging()
	{
		return (hangAnimation == AnimationState::FINAL);
	}
	void reset()
	{
		hangAnimation = AnimationState::INITIAL;
		charactersToDisplay.clear();
	}
};

extern Hangman game;