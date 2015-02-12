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

// ================================================== function to validate bitstring
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

// =================================================================================
// =================================================================================

int main(int argc, char* argv[])
{
	// args to main
	std::string inputFile;
	std::string outputFile;
	std::string password; 
	std::string bitstring;
	int tap; 

	// sfml-related vars
	sf::Image image;


	// ========================= did the user supply the correct number of arguments?
	try
	{	
		// arg-c... if they want to give it a password
		if (argc == ARGC_WITH_PASSWORD)
			password = argv[PASSWORD_ARG];
		
		// arg-c... if they want to give it a bitstring and tap
		if (argc == ARGC_WITH_BITSTRING)
		{
			bitstring = argv[BITSTRING_ARG];
			tap = std::atoi(argv[TAP_ARG]);
			
			if (!bitstringAndTapAreValid(bitstring, tap))
				return -1;
		}

		// arg-c...learly they are doing it wrong
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

	// ========================================================== now do sfml stuff!
	sf::Vector2u size = image.getSize();
	sf::RenderWindow window(sf::VideoMode(size.x, size.y), inputFile);

	sf::Texture texture;
	texture.loadFromImage(image);

	sf::Sprite sprite;
	sprite.setTexture(texture);

	while (window.isOpen())
	{
		sf::Event event;
		
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);
		window.draw(sprite);
		window.display();
	}

	if (!image.saveToFile(outputFile + ".png"))
		return -1;

	return 0;
}



