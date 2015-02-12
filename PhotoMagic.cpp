#include <SFML/Graphics.hpp>
#include <string>
#include <cstdlib>
#include <iostream>
#include "LFSR.hpp"

const int ASCII_ZERO = '0';
const int ASCII_ONE = '1';

const int ARGC_WITH_PASSWORD = 4;
const int ARGC_WITH_BITSTRING = 5;

const int INPUT_ARG = 1;
const int OUTPUT_ARG = 2;
const int PASSWORD_ARG = 3;
const int BITSTRING_ARG = 3;
const int TAP_ARG = 4;

// ============================================================== validate bitstring
// a bitstring may only contain ascii 1s and 0s
// tap must exist within the bounds of the bitstring 

bool bitstringAndTapAreValid(std::string bitstring, int tap)
{
	for(int i = 0; i < bitstring.size(); ++i)
	{
		if (bitstring[i] != ASCII_ONE && bitstring[i] != ASCII_ZERO)
		{
			std::cout << std::endl;
			std::cout << "Your bitstring may only contain 1s and 0s. If you wish ";
			std::cout << "to supply a password containing any type of character, ";
			std::cout << "then do not supply a tap position. Please try again!";
			std::cout << std::endl << std::endl;
			return false;
		}
	}

	if (tap < 0 || tap+1 > bitstring.size())
	{
		std::cout << "You supplied a tap position outside the bounds of your ";
		std::cout << "bitstring. Please try again!" << std::endl << std::endl;
		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	std::string inputFile;// = argv[INPUT_ARG];
	std::string outputFile;// = argv[OUTPUT_ARG];
	std::string password; // = argv[PASSWORD_ARG];
	std::string bitstring; // = argv[BITSTRING_ARG]
	int tap; 



	// ========================= did the user supply the correct number of arguments?
	try
	{	
		// args to main are: input, output, and password
		if (argc == ARGC_WITH_PASSWORD)
			password = argv[PASSWORD_ARG];
		
		// args to main are: input, output, bitstring, and tap
		if (argc == ARGC_WITH_BITSTRING)
		{
			bitstring = argv[BITSTRING_ARG];
			tap = std::atoi(argv[TAP_ARG]);
			
			if (!bitstringAndTapAreValid(bitstring, tap))
				return -1;
		}

		// arg-c...learly you are doing it wrong
		if (argc != ARGC_WITH_PASSWORD && argc != ARGC_WITH_BITSTRING)
			throw invalidArgc();
	}
	catch (invalidArgc e)
	{
		std::cout << std::endl << "You must supply PhotoMagic with: " << std::endl;
		std::cout << "\t<input-file> <output-file> <32-bit-string> <tap-position>";
		std::cout << std::endl << "\t\t-- or --" << std::endl;
		std::cout << "\t<input-file> <output-file> <password>" << std::endl;
		std::cout << "Please try again." << std::endl << std::endl;
		return -1;
	}

	// ==================================== does the user-supplied input file exist?
	sf::Image image;
	try
	{
		inputFile = argv[INPUT_ARG];
		outputFile = argv[OUTPUT_ARG];

		if (!image.loadFromFile(inputFile))
			throw invalidInputFile();
	}
	catch (invalidInputFile e)
	{
		std::cout << std::endl << "You ran PhotoMagic with '" << inputFile;
		std::cout << "' as an input file. Please chack that this file" << std::endl; 
		std::cout << "exists in the current directory, and try again.";
		std::cout << std::endl << std::endl;
		return -1;
	}






	










//std::cout << inputFile << std::endl;


	return 0;
}



