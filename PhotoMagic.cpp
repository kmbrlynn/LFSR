#include <SFML/Graphics.hpp>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "LFSR.hpp"

const int ARGC_WITH_PASSWORD = 4;
const int ARGC_WITH_BITSTRING = 5;

const int INPUT_ARG = 1;
const int OUTPUT_ARG = 2;
const int PASSWORD_ARG = 3;
const int BITSTRING_ARG = 3;
const int TAP_ARG = 4;

int main(int argc, char* argv[])
{
	// args to main
	std::string inputFile;
	std::string outputFile;
	std::string password; 
	std::string bitstring;
	int tap; 

	// sfml-related vars
	sf::Image inputImage;
	sf::Image outputImage;

	sf::Vector2u size;

	sf::RenderWindow inputWindow;
	sf::Texture inputTexture;
	sf::Sprite inputSprite;

	sf::RenderWindow outputWindow;
	sf::Texture outputTexture;
	sf::Sprite outputSprite;

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

		if (!inputImage.loadFromFile(inputFile))
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

	// ===================================== is the user outputting to a png format?
	try
	{
		outputFile = argv[OUTPUT_ARG];

		char* fileExt = new char[outputFile.size()+1]; // +1 for null terminator
		std::strcpy(fileExt, outputFile.c_str());
		int size = outputFile.size();

		if (	size < 5 || // filename before extension must be at least 1 char
				fileExt[size-1] != 'g' && fileExt[size-1]	!= 'G'	||
				fileExt[size-2] != 'n' && fileExt[size-2]	!= 'N'	||
				fileExt[size-3] != 'p' && fileExt[size-4]	!= 'P'	||
				fileExt[size-4] != '.'
	       ) { throw invalidOutputFormat(); }

	}
	catch (invalidOutputFormat e)
	{
		std::cout << std::endl << "You ran PhotoMagic with '" << outputFile;
		std::cout << "' as an output file. Please provide a filename ending ";
		std::cout << std::endl << "with a '.png' extension, and try again.";
		std::cout << std::endl << std::endl;
		return -1;
	}

	// ========================================================== now do sfml stuff!
	size = inputImage.getSize();

	// input window
	inputWindow.setSize(size);
	inputWindow.setPosition(sf::Vector2i(100, 50));

	inputTexture.loadFromImage(inputImage);
	inputSprite.setTexture(inputTexture);

	// === RUN LFSR ==== ? to generate output file

	for (int x = 0; x < size.x; ++x)
	{
		for (int y = 0; y < size.y; ++y)
		{
			


		}


	}

	// output window
	outputWindow.setSize(size);
	outputWindow.setPosition(sf::Vector2i(300, 50));
	
	outputTexture.loadFromImage(outputImage); // create this with LFSR
	outputSprite.setTexture(outputTexture);

	while (inputWindow.isOpen() && outputWindow.isOpen())
	{
		sf::Event event;
		
		while (inputWindow.pollEvent(event))
			if (event.type == sf::Event::Closed)
				inputWindow.close();

		while (outputWindow.pollEvent(event))
			if (event.type == sf::Event::Closed)
				outputWindow.close();
		

		inputWindow.clear(sf::Color::White);
		inputWindow.draw(inputSprite);
		inputWindow.display();

		outputWindow.clear(sf::Color::White);
		outputWindow.draw(outputSprite);
		outputWindow.display();
	}

	if (!outputImage.saveToFile(outputFile))
		return -1;

	return 0;
}



