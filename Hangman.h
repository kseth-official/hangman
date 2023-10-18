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
	int hanganimation;
	string player;
	string phrase;
	vector<char> characterstodisplay;

	void retrieveTextFrom(string filename);
public:
	Hangman() : hanganimation(0), player("one") {}

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
		return (hanganimation == 6);
	}
	void reset()
	{
		hanganimation = 0;
		characterstodisplay.clear();
	}

};

extern Hangman game;