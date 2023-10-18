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
	string player, phrase;
	vector<char> characterstodisplay;
	int hanganimation;

	void retrievetextfrom(string filename);
public:
	Hangman() : hanganimation(0), player("one") {}

	void execute();
	void displayRules();
	void enterthephrase();
	void playgame();
	void displayanimation();
	void displayphraselayout();
	void guessletter();
	bool isletterinphrase(char letter);
	void guessword();
	void displayletters();
	bool hasbeenguessed(char letter);
	bool manishanging()
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