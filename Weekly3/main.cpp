#include <iostream>
#include <random>
#include <Windows.h>
#include <vector>

void ClearCin();

void Menu();
void MainGameLoop(int);
void Leaderboard();
void Settings();

void AddTooHighScoreList(int, std::vector<int>&);
void SetDifficulty(int, int);
int GetRandomInterger();

int guessFrom = 1;
int guessTo = 5;
int currentDiff{ 0 };

std::vector<int> highscoreList{};

std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
std::uniform_int_distribution<> die{ guessFrom, guessTo };

int main() {
	// independent variables




	Menu();

	

	

	return 0;
}
void Menu() {

	
	while (true) // reset Menu
	{
		system("cls"); // clears the past info that was on screen

		// Generates number to geuss
		int numToGuess = GetRandomInterger();
		int guessCounter{};

		std::cout << "Hello! Welcome to this guessing game!" << std::endl;
		std::cout << "_____________________________________" << std::endl;

		std::cout << "Please select from the menu:" << std::endl;
		std::cout << "1. Start game" << std::endl;
		std::cout << "2. See leaderboards" << std::endl;
		std::cout << "3. Settings " << std::endl;
		std::cout << "q. Quit game :( " << std::endl;
		std::cout << "Input : ";
		std::string ans{};
		std::cin >> ans;
		ClearCin();
		system("cls");


		char ansChar{};
		if (ans.size() == 1)
		{
			ansChar = ans[0];
		}
		else
		{
			ansChar = {};
		}

		

		switch (tolower(ansChar))
		{
		case '1':
			MainGameLoop(numToGuess);
			break;


		case '2': 
			Leaderboard();
			break;

		case '3':
			Settings();
			break;

		case 'q':
			exit(0);
			break;

		default:
			break;
		}
	}
}



void MainGameLoop(int a_numToGuess) {
	int guessCounter{};
	while (true)	//main ingame loop
	{
		std::cout << "Please guess a number form " << guessFrom << " to " << guessTo << std::endl;
		int answer{};
		std::cin >> answer;
		system("cls");
		guessCounter++;
		if (answer > a_numToGuess)	// if the player guessed too high
		{
			std::cout << "Ouch! Too high, try again!" << std::endl;

		}
		else if (answer < a_numToGuess)	// if the player guessed to low
		{
			std::cout << "Auwwie! Too low, try again!" << std::endl;

		}
		else // if the player guessed correctly
		{
			std::cout << "Correct!" << std::endl;
			std::cout << "You guessed : " << guessCounter << " times until you got it right!" << std::endl;
			//displays in you beat the last score
			if (highscoreList.size() > 0)
			{
				if (guessCounter < highscoreList[0])
				{
					std::cout << "You beat the new highscore! The previous was " << highscoreList[0] << ", you your score was " << guessCounter << "!!!" << std::endl;
				}
			}


			AddTooHighScoreList(guessCounter, highscoreList);
			system("pause");
			break;

		}
	}
}

void Leaderboard() {
	std::cout << "Current highscore list : " << std::endl << std::endl;
	//std::cout << highscoreList.size() << std::endl;
	for (int i = 0; i < highscoreList.size(); i++)
	{
		std::cout << highscoreList[i] << std::endl;
	}

	system("pause");
}

void Settings() {
	bool exitSettings = false;
	while (exitSettings == false)
	{
		std::cout << "Please select a difficulty:" << std::endl;
		std::cout << "1. Easy     (1-5) " << std::endl;
		std::cout << "2. Medium   (1-10) " << std::endl;
		std::cout << "3. Hard     (1-30)" << std::endl;
		std::cout << "Input : ";
		int answer{};
		std::cin >> answer;
		ClearCin();
		system("cls");

		exitSettings = true;
		switch (answer)
		{
		case 1: 
			SetDifficulty(1);
			break;

		case 2:
			SetDifficulty(2);
			break;

		case 3:
			SetDifficulty(3);
			break;

		default:
			exitSettings = false;
			break;
		}



	}
}

void SetDifficulty(int diff) {
	switch (diff)
	{
	case 1:
		guessFrom = 1;
		guessTo = 5;
		currentDiff = 0;
		break;

	case 2:
		guessFrom = 1;
		guessTo = 10;
		currentDiff = 1;
		break;

	case 3:
		guessFrom = 1;
		guessTo = 30;
		currentDiff = 2;
		break;
	default:
		break;
	}
}

int GetRandomInterger() {
	std::uniform_int_distribution<> die{ guessFrom, guessTo };
	return die(mersenne);
}

void AddTooHighScoreList(int score, std::vector<int>& _highscoreList) {
	
	if (_highscoreList.size() == 0) { 
		_highscoreList.push_back(score); 
		return;
	}

	for (int i = 0; i < _highscoreList.size(); i++){
		if (score <_highscoreList[i])
		{
			_highscoreList.insert(_highscoreList.begin() + i, score);
			break;
		}
		else if (i == _highscoreList.size() - 1)
		{
			_highscoreList.push_back(score);
			break;
		}
		

	}
}


void ClearCin() {
	std::cin.clear();
	std::cin.ignore(32767, '\n');
}