#include <iostream>
#include <random>
#include <Windows.h>
#include <vector>

//initializing all the methods so we can use them independent of what order they are defiined in
// the definitions of the mehods are further down the page
void ClearCin();

//menus/scenes that the player sees
void Menu();
void MainGameLoop();
void Leaderboard();
void Settings();
void SetCustomDifficulty();

//functions that are non visual
void AddTooHighScoreList(int, std::vector<int>&);
void SetDifficulty(int);
int GetRandomInterger();

//numbers to guess from and to, they are in global scope becouse its a small project
int guessFrom = 1;
int guessTo = 5;
int currentDiff{ 0 };

// stores highscores, one vector per difficulty
std::vector<std::vector<int>> highscoreList{ {} };

//setting the random number seed to the time -> get a diffrent seed for each run of the program
std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };


int main() {
	//give the highscore vector 4 inner vectors for the different highscore settings
	highscoreList.push_back(std::vector<int>{});
	highscoreList.push_back(std::vector<int>{});
	highscoreList.push_back(std::vector<int>{});
	highscoreList.push_back(std::vector<int>{});

	Menu();

	return 0;
}

void Menu() {

	
	while (true) // Menu loop
	{
		system("cls"); // clears the past info that was on screen

		//menu scene/text
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


		char ansChar{};	 //writes to string, so that if the player types more than one letter, it wont work
		if (ans.size() == 1)
		{
			ansChar = ans[0];
		}
		else
		{
			ansChar = {};
		}

		
		//diffrent scenes to travel to, or quit
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
		else if (answer < a_numToGuess)	// if the player guessed too low
		{
			std::cout << "Auwwie! Too low, try again!" << std::endl;

		}
		else // if the player guessed correctly
		{
			std::cout << "Correct!" << std::endl;
			std::cout << "You guessed : " << guessCounter << " times until you got it right!" << std::endl;

			//displays if you beat the last score
			if (highscoreList[currentDiff].size() > 0)	//checks if the you have a highscore to compare too
			{
				if (guessCounter < highscoreList[currentDiff][0])
				{
					std::cout << "You beat the new highscore! The previous was " << highscoreList[currentDiff][0] << ", you your score was " << guessCounter << "!!!" << std::endl;
				}
			}

			//adds the score you got to the appropiate place in the vector in acending order
			AddTooHighScoreList(guessCounter, highscoreList[currentDiff]);
			system("pause");
			
			break; // exits the main game loop

		}
	}
}

void Leaderboard() { // menu for viewing the leaderboards
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

	//prints the acutal scores
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

void SetDifficulty(int diff) { //sets the difficulty
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

int GetRandomInterger() { // gets a random int using the method we got from learncpp
	std::uniform_int_distribution<> die{ guessFrom, guessTo };
	return die(mersenne);
}

void AddTooHighScoreList(int score, std::vector<int>& _highscoreList) { // adds the score you got to the vector in ascening order
	
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


void ClearCin() { // clears the cin buffer for:
	std::cin.clear(); // errors
	std::cin.ignore(32767, '\n'); // leftover text
}