#include <iostream>
#include <random>
#include <Windows.h>
#include <vector>


int guessFrom = 0;
int guessTo = 1;
std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
std::uniform_int_distribution<> die{ guessFrom, guessTo };

int main() {
	// independent variables
	std::vector<int> highscoreList{};

	

	while (true) // reset gameloop
	{
		system("cls"); // clears the past info that was on screen

		// Generates number to geuss
		int numToGuess = die(mersenne);
		int guessCounter{};

		std::cout << "Hello! Welcome to this guessing game!" << std::endl;
		std::cout << " Current highscore list!" << std::endl;
		for (int i = 0; i < highscoreList.size(); i++)
		{
			std::cout << highscoreList[i] << std::endl;
		}


		while (true)	//main ingame loop
		{
			std::cout << "Please guess a number form " << guessFrom << " to " << guessTo << std::endl;
			int answer{};
			std::cin >> answer;
			system("cls");
			guessCounter++;
			if (answer > numToGuess)	// if the player guessed too high
			{
				std::cout << "Ouch! Too high, try again!" << std::endl;
				
			}
			else if (answer < numToGuess)	// if the player guessed to low
			{
				std::cout << "Auwwie! Too low, try again!" << std::endl;
				
			}
			else // if the player guessed correctly
			{
				highscoreList.push_back(guessCounter);
				std::cout << "Correct!" << std::endl;
				std::cout << "You guessed : " << guessCounter << " times until you got it right!" << std::endl;
				system("pause");
				break;
				
			}
		}
	}

	return 0;
}


