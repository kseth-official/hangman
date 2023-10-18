#pragma once

#include<iostream>
#include<conio.h>
#include<fstream>
#include<process.h>
#include<vector>
#include<string>

using namespace std;

class Hangman
{
private:
	string player, phrase;
	vector<char> characterstodisplay;
	int hanganimation;

public:
	Hangman()
	{
		player = "one";
		hanganimation = 0;
	}
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

} game;

