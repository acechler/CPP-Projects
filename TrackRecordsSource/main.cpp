/* Name: Aaron Echler */
/* Date: 7/18/2019 */
/* Project: Go-Karts Records Project */

//NOTE: This code was updated 2/24/2020
/*
	I cleaned up some comments and updated some code with new tricks I have learned.
*/

/* Program Information */
/*
	The goal of this program

	1. Display the records in a text document or in the program
	2. Be able to order the records from least to greatest

*/



#include<iostream>
#include<ctime>
#include<vector>
#include<algorithm>
#include<string>
#include<iomanip>
#include<fstream>
#include<Windows.h>

void Clear() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}

//Check to see if the user has file on PC
void File_Check(std::string laptimesFile, std::vector<double> lapTimes)
{
	std::ifstream inputFile;
	std::ofstream outputFile;

	//--------Check if laptimes file exists----------
	inputFile.open(laptimesFile);
	{
		if (inputFile.fail())
		{
			outputFile.open(laptimesFile);

			for (int i = 0; i < lapTimes.size(); i++)
			{
				double placeHolder = 60.00;
				outputFile << placeHolder << std::endl;
			}

			outputFile.close();
		}
		else
			inputFile.close();
	}
}

//Displays the main options menu
void Display_Options()
{
	std::cout << std::setw(8) << "Go-Kart Records" << std::endl << std::endl;
	std::cout << "Please enter an option" << std::endl << std::endl
		<< "[1] Open Records" << std::endl
		<< "[2] Enter Records" << std::endl
		<< "[3] Create Legacy File" << std::endl
		<< "[4] Exit" << std::endl << std::endl
		<< "Enter: ";
}

//Displays the add records options menu
void Display_Add_Records_Options()
{
	std::cout << std::endl << std::endl;
	std::cout << "Do you want to enter a new laptime?" << std::endl << std::endl
		<< "[1] Yes" << std::endl
		<< "[2] No" << std::endl << std::endl
		<< "Enter:";

}

//This outputs data into the file
void Add_Data_To_File(std::string laptimesFile, std::vector<double> lapTimes)
{
	std::ofstream outputFile;

	//Add new laptime data into the file
	outputFile.open(laptimesFile);
	for (int i = 0; i < lapTimes.size(); i++)
	{
		outputFile << lapTimes[i] << std::endl;
	}
	outputFile.close();
}

//Asks for user to create a file name
std::string Get_Users_File_Names(std::string legacyFile)
{
	std::cout << "Legacy File Menu" << std::endl << std::endl;
	std::cout << "What would you like to call your legacy file?" << std::endl
		<< "Enter:";
	std::cin >> legacyFile;
	return legacyFile;
}

//Instructions for the legacy file menu
void Legacy_File_Menu_Display()
{
	std::cout << "Please enter what you want to do." << std::endl
		<< "[1] Create another file" << std::endl
		<< "[2] Erase Data in Current Go-Kart File" << std::endl
		<< "[3] Go back to main menu" << std::endl
		<< "Enter: ";
}

int main()
{

	bool mainProgram = true;		//The main loop of the program that traverses through the program
	//
	bool initializerMenu = true;	//This is the main menu of the program that allows the user to select different options
	//
	bool openRecords = false;		//Allows user to open a previously created file and modify it
	//
	bool enterRecords = false;		//Menu that allows the user to enter track records
	//
	bool legacyFileMenu = true;		//Allows user to move records into new files
	//

	
	int userInput = 0;				//Variable to allow user to input numbers to interact with the program
	//
	double newLapTimes = 0;			//Variable to hold the users laptime so it can be added to the laptime vector
	//


	std::ofstream mainOutputFile;
	std::ifstream mainInputFile;

	
	std::string laptimesFile = "laptimesFile.txt";		//The main track records file that the user will store current track records in
	//	
	std::string legacyFile;								//A legacy file that saves the track records from laptime file without records being erased
	//


	std::vector <double> lapTimes(8);						//Vector of doubles that hold the current go kart laptimes
	//
	

	std::cout << std::fixed << std::setprecision(2);
	File_Check(laptimesFile,lapTimes);

	while (mainProgram == true)
	{

		while (initializerMenu == true)
		{
			Display_Options();
			std::cin >> userInput;

			while (userInput < 1 || userInput > 4)
			{
				std::cout << std::endl;
				std::cout << "Invalid input... please try again" << std::endl << std::endl;

				Display_Options();
				std::cin >> userInput;
			}

			switch (userInput)
			{

			case 1:
				Clear();
				mainProgram		= true;
				initializerMenu = false;
				openRecords		= true;
				legacyFileMenu  = false;
				break;

			case 2:
				Clear();
				mainProgram		= true;
				initializerMenu = false;
				enterRecords	= true;
				legacyFileMenu	= false;
				break;

			case 3:
				Clear();
				mainProgram		= true;
				initializerMenu = false;
				enterRecords    = false;
				legacyFileMenu  = true;
				break;

			case 4:
				initializerMenu = false;
				openRecords		= false;
				legacyFileMenu  = false;
				mainProgram		= false;
				break;

			default:
				break;
			}

		}
		//Display Records
		while (openRecords == true)
		{
			int recordPlace = 1;
			std::cout << std::endl;
			std::cout << "Current Track Records" << std::endl << std::endl;
			mainInputFile.open(laptimesFile);
			for (int i = 0; i < lapTimes.size(); i++,recordPlace++)
			{
				mainInputFile >> lapTimes[i];
				std::cout << recordPlace << ".  ";
				std::cout << lapTimes[i] << std::endl;
			}
			std::cout << std::endl;
			mainInputFile.close();

			initializerMenu = true;
			openRecords = false;
			
		}

		//Allows user to enter new records
		while (enterRecords == true)
		{
			//Inputing from laptimes file
			mainInputFile.open(laptimesFile);
			for (int lapTimesIndex = 0; lapTimesIndex < lapTimes.size(); lapTimesIndex++)
				mainInputFile >> lapTimes[lapTimesIndex];
			mainInputFile.close();

			std::cout << "Enter New Laptime. Format as 00.00" << std::endl << std::endl
				<< "Enter: ";
			std::cin >> newLapTimes;
			std::cout << std::endl;
			std::cout << "TRACK RECORDS" << std::endl << std::endl;
			//Enter new laptime and sort it
			lapTimes.push_back(newLapTimes);
			for (int i = 0; i < lapTimes.size(); i++)
			{
				sort(lapTimes.begin(), lapTimes.end(), std::greater<double>());
				reverse(lapTimes.begin(), lapTimes.end());
				std::cout << lapTimes[i] << std::endl;
			}
			lapTimes.pop_back();

			//Add new laptime data into the file
			Add_Data_To_File(laptimesFile,lapTimes);

			//Check if user wants to enter another record
			Display_Add_Records_Options();
			std::cin >> userInput;

			while (userInput < 1 || userInput > 2)
			{
				std::cout << std::endl;
				std::cout << "Invalid input... please try again" << std::endl << std::endl;
				Display_Add_Records_Options();
				std::cin >> userInput;
			}

			switch (userInput)
			{
			case 1:
				Clear();
				enterRecords = true;
				break;

			case 2:
				Clear();
				initializerMenu = true;
				enterRecords = false;
				break;

			default:
				break;
			}

		}

		//Allows user to create a new file and clear out main laptime file
		while (legacyFileMenu == true)
		{
			
			std::string txtExtention = ".txt";		//Variable to allow user to add txt at the end of the file name automatically
			//			
			std::string combineFileName;			//Variable to combine the users text file name with a txt extention
			//

			//Inputing from laptimes file
			mainInputFile.open(laptimesFile);
			for (int lapTimesIndex = 0; lapTimesIndex < lapTimes.size(); lapTimesIndex++)
				mainInputFile >> lapTimes[lapTimesIndex];
			mainInputFile.close();

			//Get users filename
			legacyFile = Get_Users_File_Names(legacyFile);

			combineFileName = legacyFile + txtExtention;
			Add_Data_To_File(combineFileName, lapTimes);

			Legacy_File_Menu_Display();
			std::cin >> userInput;

			while (userInput < 1 || userInput > 3)
			{
				std::cout << std::endl;
				std::cout << "Invalid input... please try again" << std::endl << std::endl;
				Legacy_File_Menu_Display();
				std::cin >> userInput;
			}

			switch (userInput)
			{
			case 1:
				legacyFileMenu = true;
				break;

			case 2:
				mainOutputFile.open(laptimesFile);
				for (int i = 0; i < lapTimes.size(); i++)
				{
					double placeHolder = 60.00;	
					mainOutputFile << placeHolder << std::endl;
				}
				mainOutputFile.close();
				initializerMenu = true;
				legacyFileMenu = false;
				break;

			case 3:
				initializerMenu = true;
				legacyFileMenu  = false;
				break;

			default:
				break;
			}



		}

	}



	std::cin.get();
	return 0;
}