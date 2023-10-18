/*A TEXT BASED IMPLEMENTATION OF HANGMAN
Menu:
1. Play Game
2. Exit

Play Game =>
Rules:
Game is designed for 2 players
 One person enters a word/phrase (which can include spaces and special characters) as the word/phrase to be guessed.
//A screen appears with dashes indicating letters of the word/phrase (dash does not occur for spaces)
The other person must either: a) type in a letter which he/she thinks exists b) choose to enter the entire word 
If 6 wrong guesses are made for which letters could exist, the person loses the game.

	*****
	*	*
	0	*
   \|/  *
	|	*
   / \  *
		*
		*
*********

*/

#include "Hangman.h"

const char uparrow = 72;
const char darrow = 75;

int checkposinmenu(int value)
{
	if (value == 3 || value == 0)
		return false;
	else
		return true;
}

void MAINMENU()
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
			flag = checkposinmenu(pos);
			if (flag == false)
				--pos;
		}
		else if (opt == 's')
		{
			--pos;
			flag = checkposinmenu(pos);
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

void finalscreen(bool win)
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
	MAINMENU();
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

void Hangman::enterthephrase()
{
	system("cls");
	cout << "Enter word/phrase to be guessed: ";
	getline(cin>>ws, phrase); //requires string header file / allows string input to terminate at newline character \n
}

void Hangman::displayanimation()
{
	char c;
	ifstream obj;
	if (hanganimation == 0)
	{
		obj.open("zero.txt", ios::in);
		obj.seekg(0);	
		while (obj)
		{
			obj.get(c);
			cout << c;
		}
		obj.close();
	}
	else if (hanganimation == 1)
	{
		obj.open("one.txt",ios::in);
		obj.seekg(0);
		while (obj)
		{
			obj.get(c);
			cout << c;
		}
		obj.close();
	}
	else if (hanganimation == 2)
	{
		obj.open("two.txt",ios::in);
		obj.seekg(0);
		while (obj)
		{
			obj.get(c);
			cout << c;
		}
		obj.close();
	}
	else if (hanganimation == 3)
	{
		obj.open("three.txt",ios::in);
		obj.seekg(0);
		while (obj)
		{
			obj.get(c);
			cout << c;
		}
		obj.close();
	}
	else if (hanganimation == 4)
	{
		obj.open("four.txt",ios::in);
		obj.seekg(0);
		while (obj)
		{
			obj.get(c);
			cout << c;
		}
		obj.close();
	}
	else if (hanganimation == 5)
	{
		obj.open("five.txt",ios::in);
		obj.seekg(0);
		while (obj)
		{
			obj.get(c);
			cout << c;
		}
		obj.close();
	}
	else if (hanganimation == 6)
	{
		obj.open("six.txt",ios::in);
		obj.seekg(0);
		while (obj)
		{
			obj.get(c);
			cout << c;
		}
		obj.close();
	}
	cout << endl;
}

bool Hangman::hasbeenguessed(char letter)
{
	bool flag = false;
	for (int j = 0; j < characterstodisplay.size(); ++j)
	{
		if (letter == characterstodisplay[j])
		{
			flag = true;
			break;
		}
	}
	return flag;
}

void Hangman::displayletters()
{
	int length = 0;
	for (int i = 0; i < phrase.size(); ++i)
	{
		if (phrase[i] == ' ')
		{
			cout << "  ";
			++length;
			continue;
		}
		bool flag = hasbeenguessed(phrase[i]);
		if (flag)
		{
			cout << phrase[i] << " ";
			++length;
		}
		else
			cout << "  ";
	}
	if (length == phrase.size())
		finalscreen(true);
	cout << endl;
}

void Hangman::displayphraselayout()
{
	for (int i = 0; i < phrase.size(); ++i)
	{
		if (phrase[i] != ' ')
			cout << "_ ";
		else
			cout << "  ";
	}
	cout << endl;
}

bool Hangman::isletterinphrase(char letter)
{
	int flag = false;
	for (int i = 0; i < phrase.size(); ++i)
	{
		if (phrase[i] == letter)
			flag = true;
	}
	return flag;
}

void Hangman::guessletter()
{
	char letter;
	cout << "Enter the letter: ";
	cin >> letter;

	int flag = isletterinphrase(letter);
	if (flag == false)
		++hanganimation;
	else
		characterstodisplay.push_back(letter);
}

void Hangman::guessword()
{
	string word;
	cout << "Enter word: ";
	getline(cin >> ws, word);
	if (word == phrase)
		finalscreen(true);
	else
		++hanganimation;
}

void Hangman::playgame()
{
	while (1)
	{
		system("cls");
		cout << "HANGMAN\n" << endl;
		displayanimation();

		if (manishanging())
			finalscreen(false);

		displayletters();
		displayphraselayout();

		char opt;
		cout << "\n1. Guess a letter" << endl;
		cout << "2. Guess the word/phrase" << endl;
		cout << "Enter here : " << endl;;
		cin >> opt;
		if (opt == '1')
			guessletter();	
		else if(opt=='2')
			guessword();
	}

}

void Hangman::execute()
{
	displayRules();
	enterthephrase();
	playgame();
}

int main()
{
	MAINMENU();
}
