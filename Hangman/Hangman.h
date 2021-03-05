#pragma once
class Hangman
{
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
		if (hanganimation == 6)
			return true;
		else
			return false;
	}
	void reset()
	{
		hanganimation = 0;
		characterstodisplay.clear();
	}

} game;

