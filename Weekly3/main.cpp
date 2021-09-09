#include <iostream>
#include <random>
#include <Windows.h>
#include <vector>

void ClearCin();

void Menu();
void MainGameLoop();
void Leaderboard();
void Settings();

void AddTooHighScoreList(int, std::vector<int>&);
void SetDifficulty(int);
void SetCustomDifficulty();
int GetRandomInterger();

int guessFrom = 1;
int guessTo = 5;
int currentDiff{ 0 };

std::vector<std::vector<int>> highscoreList{ {} };

std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
std::uniform_int_distribution<> die{ guessFrom, guessTo };

int main() {
	//give the highscore vector 3 inner vectros for different highscore settings
	highscoreList.push_back(std::vector<int>{});
	highscoreList.push_back(std::vector<int>{});
	highscoreList.push_back(std::vector<int>{});
	highscoreList.push_back(std::vector<int>{});


	Menu();

	return 0;
}

void Menu() {

	
	while (true) // reset Menu
	{
		system("cls"); // clears the past info that was on screen


		std::cout << "Hello! Welcome to this guessing game!" << std::endl;
		std::cout << "_____________________________________" << std::endl << std::endl;

		std::cout << "Please select from the menu:" << std::endl;
		std::cout << "1. Start game" << std::endl;
		std::cout << "2. See leaderboards" << std::endl;
		std::cout << "3. Settings " << std::endl;
		std::cout << "q. Quit game :( " << std::endl << std::endl;
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
			MainGameLoop();
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



void MainGameLoop() {

	int a_numToGuess = GetRandomInterger();
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
			if (highscoreList[currentDiff].size() > 0)
			{
				if (guessCounter < highscoreList[currentDiff][0])
				{
					std::cout << "You beat the new highscore! The previous was " << highscoreList[currentDiff][0] << ", you your score was " << guessCounter << "!!!" << std::endl;
				}
			}


			AddTooHighScoreList(guessCounter, highscoreList[currentDiff]);
			system("pause");
			break;

		}
	}
}

void Leaderboard() {
	std::cout << "Current highscore for ";
	//prints the current difficulty mode
	std::string currentDiffString{};
	switch (currentDiff)
	{
	case 0:
		currentDiffString = "Easy";
		break;
	case 1:
		currentDiffString = "Medium";
		break;
	case 2:
		currentDiffString = "Hard";
		break;
	case 3:
		currentDiffString = "Custom";
		break;

	default:
		currentDiffString = "NOT DEFINED";
		break;
	}

	std::cout << currentDiffString << " difficulty mode : " << std::endl;
	std::cout << "_______________________" << std::endl;

	
	for (int i = 0; i < highscoreList[currentDiff].size(); i++)
	{
		std::cout << highscoreList[currentDiff][i] << std::endl;
	}

	std::cout << "_______________________" << std::endl << std::endl;

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
		std::cout << "4. Custom " << std::endl;
		std::cout << "q. Return to Menu" << std::endl << std::endl;
		std::cout << "Input : ";
		char answer{};
		std::cin >> answer;
		ClearCin();
		system("cls");

		exitSettings = true;
		switch (answer)
		{
		case '1':
			SetDifficulty(1);
			break;

		case '2':
			SetDifficulty(2);
			break;

		case '3':
			SetDifficulty(3);
			break;

		case '4':
			SetCustomDifficulty();
			break;

		case 'q':
			break;

		default:
			exitSettings = false;
			break;
		}



	}
}

void SetCustomDifficulty() {
	while (true)
	{

		std::cout << "Please select from what interger to guess from, then too" << std::endl;

		int from{};
		int too{};
		std::cout << " From : ";
		std::cin >> from;
		std::cout << " Too : ";
		std::cin >> too;

		if (from < too)
		{
			currentDiff = 3;
			guessFrom = from;
			guessTo = too;
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