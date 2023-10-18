#include "Hangman.h"

const char uparrow = 72;
const char darrow = 75;

Hangman game;

int isInMenuBounds(int value)
{
	return !(value == 3 || value == 0);
}

void startMainMenu()
{
	game.reset();
	char opt;
	int pos = 2;
	while (1)
	{
		system("cls");
		cout << "Menu" << endl;
		cout << "1. Play Game";
		if (pos == 2)
			cout << "  <-";
		cout << "\n2. Exit";
		if (pos == 1)
			cout << "       <-";

		opt = _getch();

		int flag = 0;
		if (opt == 'w')
		{
			++pos;
			flag = isInMenuBounds(pos);
			if (flag == false)
				--pos;
		}
		else if (opt == 's')
		{
			--pos;
			flag = isInMenuBounds(pos);
			if (flag == false)
				++pos;
		}
		else if (opt == '\r')
		{
			if (pos == 2)
				game.execute();
			else
				exit(0);
		}
	}
}

void finalScreen(bool win)
{
	system("cls");
	if (win) {
		cout << "You win!" << endl;
	}
	else {
		cout << "You lose!" << endl;
	}
	cout << "Press any key to return to the main menu";
	_getch();
	startMainMenu();
}

void Hangman::displayRules()
{
	system("cls");
	cout << "Rules" << endl;
	cout << "1. Game is designed for 2 players" << endl;
	cout << "2. One person enters a word / phrase. The other person attempts to guess it by either :" << endl;
	cout << "a) typing in a letter which could exist in the phrase to reveal all the places where the letter is used, or by" << endl;
	cout << "b) typing in the entire word." << endl;
	cout << "3. If 6 wrong guesses are made, person 2 loses the game." << endl;
	cout << "HAVE FUN!" << endl;;
	cout << "\nPress any key to proceed";
	_getch();
}

void Hangman::enterThePhrase()
{
	system("cls");
	cout << "Enter word/phrase to be guessed: ";
	getline(cin>>ws, phrase); //requires string header file / allows string input to terminate at newline character \n
}

void Hangman::displayAnimation()
{
	
	if (hangAnimation == 0)
	{
		retrieveTextFrom("zero.txt");
	}
	else if (hangAnimation == 1)
	{
		retrieveTextFrom("one.txt");
	}
	else if (hangAnimation == 2)
	{
		retrieveTextFrom("two.txt");
	}
	else if (hangAnimation == 3)
	{
		retrieveTextFrom("three.txt");
	}
	else if (hangAnimation == 4)
	{
		retrieveTextFrom("four.txt");
	}
	else if (hangAnimation == 5)
	{
		retrieveTextFrom("five.txt");
	}
	else if (hangAnimation == 6)
	{
		retrieveTextFrom("six.txt");
	}
	cout << endl;
}

void Hangman::retrieveTextFrom(string filename) {
	char c;
	ifstream obj;

	obj.open(filename, ios::in);
	obj.seekg(0);	
	while (obj)
	{
		obj.get(c);
		cout << c;
	}
	obj.close();
}

bool Hangman::hasBeenGuessed(char letter)
{
	bool flag = false;
	for (unsigned int j = 0; j < charactersToDisplay.size(); ++j)
	{
		if (letter == charactersToDisplay[j])
		{
			flag = true;
			break;
		}
	}
	return flag;
}

void Hangman::displayLetters()
{
	unsigned int length = 0;
	for (unsigned int i = 0; i < phrase.size(); ++i)
	{
		if (phrase[i] == ' ')
		{
			cout << "  ";
			++length;
			continue;
		}
		bool flag = hasBeenGuessed(phrase[i]);
		if (flag)
		{
			cout << phrase[i] << " ";
			++length;
		}
		else
			cout << "  ";
	}
	if (length == phrase.size())
		finalScreen(true);
	cout << endl;
}

void Hangman::displayPhraseLayout()
{
	for (unsigned int i = 0; i < phrase.size(); ++i)
	{
		if (phrase[i] != ' ')
			cout << "_ ";
		else
			cout << "  ";
	}
	cout << endl;
}

bool Hangman::isLetterInPhrase(char letter)
{
	int flag = false;
	for (unsigned int i = 0; i < phrase.size(); ++i)
	{
		if (phrase[i] == letter)
			flag = true;
	}
	return flag;
}

void Hangman::guessLetter()
{
	char letter;
	cout << "Enter the letter: ";
	cin >> letter;

	int flag = isLetterInPhrase(letter);
	if (flag == false)
		++hangAnimation;
	else
		charactersToDisplay.push_back(letter);
}

void Hangman::guessWord()
{
	string word;
	cout << "Enter word: ";
	getline(cin >> ws, word);
	if (word == phrase)
		finalScreen(true);
	else
		++hangAnimation;
}

void Hangman::playGame()
{
	while (1)
	{
		system("cls");
		cout << "HANGMAN\n" << endl;
		displayAnimation();

		if (isManHanging())
			finalScreen(false);

		displayLetters();
		displayPhraseLayout();

		char opt;
		cout << "\n1. Guess a letter" << endl;
		cout << "2. Guess the word/phrase" << endl;
		cout << "Enter here : " << endl;;
		cin >> opt;
		if (opt == '1')
			guessLetter();	
		else if(opt=='2')
			guessWord();
	}

}

void Hangman::execute()
{
	displayRules();
	enterThePhrase();
	playGame();
}

int main()
{
	startMainMenu();
}
