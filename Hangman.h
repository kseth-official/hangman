#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h> // Windows Specific

using namespace std;

class Hangman
{
private:
	int hangAnimation;
	string player;
	string phrase;
	vector<char> charactersToDisplay;

	void retrieveTextFrom(string filename);
public:
	Hangman() : hangAnimation(0), player("one") {}

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
		return (hangAnimation == 6);
	}
	void reset()
	{
		hangAnimation = 0;
		charactersToDisplay.clear();
	}

};

extern Hangman game;