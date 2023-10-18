#include "Hangman.h"

const char uparrow = 72;
const char darrow = 75;

Hangman game;

const int START_OF_FILE = 0;

const char UP = 'w';
const char DOWN = 's';
const char ENTER = '\r';

const std::string ANIMATION_INITIAL_FILE_NAME = "zero.txt";
const std::string ANIMATION_ONE_FILE_NAME = "one.txt";
const std::string ANIMATION_TWO_FILE_NAME = "two.txt";
const std::string ANIMATION_THREE_FILE_NAME = "three.txt";
const std::string ANIMATION_FOUR_FILE_NAME = "four.txt";
const std::string ANIMATION_FIVE_FILE_NAME = "five.txt";
const std::string ANIMATION_FINAL_FILE_NAME = "six.txt";

int isInMenuBounds(int value)
{
	return !(value == 3 || value == 0);
}

void startMainMenu()
{
	game.reset();
	char option;
	int position = 2;
	while (1)
	{
		system("cls");
		std::cout << "Menu" << std::endl << std::endl;
		std::cout << "1. Play Game";
		if (position == 2)
			std::cout << "  <-";
		std::cout << "\n2. Exit";
		if (position == 1)
			std::cout << "       <-";

 		std::cout << std::endl;
 		std::cout << std::endl;
		
		std::cout << "Use W and S to navigate and enter to select";

		option = _getch();

		int flag = 0;
		if (option == UP)
		{
			++position;
			flag = isInMenuBounds(position);
			if (flag == false)
				--position;
		}
		else if (option == DOWN)
		{
			--position;
			flag = isInMenuBounds(position);
			if (flag == false)
				++position;
		}
		else if (option == ENTER)
		{
			if (position == 2)
				game.execute();
			else
				exit(0);
		}
	}
}

void finalScreen(bool hasWon)
{
	system("cls");
	if (hasWon) {
		std::cout << "You win!" << std::endl;
	}
	else {
		std::cout << "You lose!" << std::endl;
	}
	std::cout << "Press any key to return to the main menu";
	_getch();
	startMainMenu();
}

void Hangman::displayRules()
{
	system("cls");
	std::cout << "Rules" << std::endl;
	std::cout << "1. Game is designed for 2 players" << std::endl;
	std::cout << "2. One person enters a word / phrase. The other person attempts to guess it by either :" << std::endl;
	std::cout << "  a) typing in a letter which could exist in the phrase to reveal all the places where the letter is used, or by" << std::endl;
	std::cout << "  b) typing in the entire word/phrase in one go" << std::endl;
	std::cout << "3. If 6 wrong guesses are made, person 2 loses the game." << std::endl << std::endl;
	std::cout << "HAVE FUN!" << std::endl;
	std::cout << "\nPress any key to proceed";
	_getch();
}

void Hangman::enterThePhrase()
{
	system("cls");
	std::cout << "Enter word/phrase to be guessed: ";
	getline(std::cin >> std::ws, phrase);
	transform(phrase.begin(), phrase.end(), phrase.begin(), ::tolower); 
}

void Hangman::displayAnimation()
{
	switch(hangAnimation) {
		case AnimationState::INITIAL: 
			retrieveTextFrom(ANIMATION_INITIAL_FILE_NAME); break;
		case AnimationState::ONE: 
			retrieveTextFrom(ANIMATION_ONE_FILE_NAME); break;
		case AnimationState::TWO: 
			retrieveTextFrom(ANIMATION_TWO_FILE_NAME); break;
		case AnimationState::THREE: 
			retrieveTextFrom(ANIMATION_THREE_FILE_NAME); break;
		case AnimationState::FOUR: 
			retrieveTextFrom(ANIMATION_FOUR_FILE_NAME); break;
		case AnimationState::FIVE: 
			retrieveTextFrom(ANIMATION_FIVE_FILE_NAME); break;
		case AnimationState::FINAL: 
			retrieveTextFrom(ANIMATION_FINAL_FILE_NAME); break;
	}
	std::cout << std::endl;
}

void Hangman::retrieveTextFrom(std::string filename) {
	char character;
	std::ifstream inputStream;

	inputStream.open(filename, std::ios::in);
	inputStream.seekg(START_OF_FILE);	
	while (inputStream)
	{
		inputStream.get(character);
		std::cout << character;
	}
	inputStream.close();
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
			std::cout << "  ";
			++length;
			continue;
		}
		bool flag = hasBeenGuessed(phrase[i]);
		if (flag)
		{
			std::cout << phrase[i] << " ";
			++length;
		}
		else
			std::cout << "  ";
	}
	if (length == phrase.size())
		finalScreen(true);
	std::cout << std::endl;
}

void Hangman::displayPhraseLayout()
{
	for (unsigned int i = 0; i < phrase.size(); ++i)
	{
		if (phrase[i] != ' ')
			std::cout << "_ ";
		else
			std::cout << "  ";
	}
	std::cout << std::endl;
}

bool Hangman::isLetterInPhrase(char letter)
{
	int isLetterInPhrase = false;
	for (unsigned int i = 0; i < phrase.size(); ++i)
	{
		if (phrase[i] == letter)
			isLetterInPhrase = true;
	}
	return isLetterInPhrase;
}

void Hangman::guessLetter()
{
	char letter;
	std::cout << "Enter the letter: ";
	std::cin >> letter;

	int flag = isLetterInPhrase(letter);
	if (flag == false)
		++hangAnimation;
	else
		charactersToDisplay.push_back(letter);
}

void Hangman::guessWord()
{
	std::string word;
	std::cout << "Enter word: ";
	getline(std::cin >> std::ws, word);
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
		std::cout << "HANGMAN\n" << std::endl;
		displayAnimation();

		if (isManHanging())
			finalScreen(false);

		displayLetters();
		displayPhraseLayout();

		char option;
		std::cout << "\n1. Guess a letter" << std::endl;
		std::cout << "2. Guess the entire word/phrase" << std::endl;
		std::cout << "Enter here : " << std::endl;;
		std::cin >> option;
		if (option == '1')
			guessLetter();	
		else if(option=='2')
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
