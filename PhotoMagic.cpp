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

const int PRIME_TAP = 2;

int main(int argc, char* argv[])
{
	// args to main
	std::string inputFile;
	std::string outputFile;
	std::string password; 
	std::string bitstring;
	std::string tap;

	// for the LFSR
	std::string lfsr_seed; // either a password or a bitstring
	int lfsr_tap;		   // converted from a std::string

	// sfml vars
	sf::Vector2u size;
	sf::Color pixel;

	sf::Image inputImage;
	sf::Texture inputTexture;
	sf::Sprite inputSprite;

	sf::Image outputImage;
	sf::Texture outputTexture;
	sf::Sprite outputSprite;

	// =============================== did the user supply the right number of args?
	try
	{	
		// arg-c... if they want to give it a password
		if (argc == ARGC_WITH_PASSWORD)
		{
			// their password will get converted to a binary seed,
			// to be tapped at a relatively prime position
			password = argv[PASSWORD_ARG];
			lfsr_seed = password;
			tap = PRIME_TAP;
		
			// cast their now-validated tap from std::string to an int
			// via cstring (stoi only available in c++1)
		//	char* tap_cstring = new char[tap.length()+1];
		//	std::strcpy(tap_cstring, tap.c_str());
			lfsr_tap = stringToInt(tap); //= atoi(tap_cstring);
		}

		// arg-c... if they want to give it a bitstring and tap
		if (argc == ARGC_WITH_BITSTRING)
		{
			bitstring = argv[BITSTRING_ARG];
			lfsr_seed = bitstring;
			tap = argv[TAP_ARG];

			// tell them to provide better arguments, and exit
			if (!bitstringAndTapAreValid(bitstring, tap))
				return -1;

			// cast their now-validated tap from std::string to an int
			// via cstring (stoi only available in c++1)
			char* tap_cstring = new char[tap.length()+1];
			std::strcpy(tap_cstring, tap.c_str());
			lfsr_tap = stringToInt(tap);// = atoi(tap_cstring);
		}

		// arg-c...learly they are doing it wrong
		if (argc != ARGC_WITH_PASSWORD && argc != ARGC_WITH_BITSTRING)
			throw invalidArgc();
	}
	catch (invalidArgc e)
	{ 
		std::cout << std::endl << "Usage:" << std::endl; 
		std::cout << "\t./PhotoMagic input-file output-file bitstring tap-position";
		std::cout << std::endl;
		std::cout << "\t./PhotoMagic input-file output-file alphanumeric-password";
		std::cout << std::endl << std::endl;
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
		std::cout << std::endl << "You provided input-file: '" << inputFile << "' ";
		std::cout << "as an argument to PhotoMagic." << std::endl;
		std::cout << "Please check that it exists in the current directory ";
		std::cout << "and try again." << std::endl << std::endl;
		return -1;
	}

	// ===================================== is the user outputting to a png format?
	try
	{
		outputFile = argv[OUTPUT_ARG];
		char* fileExt = new char[outputFile.size()+1]; // +1 for null terminator
		std::strcpy(fileExt, outputFile.c_str());
		int size = outputFile.size();

		if (  ( size < 5 ) || // if filename isn't at least one char long, or it's
			  
			  (	fileExt[size-1] != 'g' && fileExt[size-1]	!= 'G'	||	// neither
				fileExt[size-2] != 'n' && fileExt[size-2]	!= 'N'	||	// a .png
				fileExt[size-3] != 'p' && fileExt[size-4]	!= 'P'	||
				fileExt[size-4] != '.' 
			  ) && 
	       
		   	  (	fileExt[size-1] != 'p' && fileExt[size-1]	!= 'P'	||	// nor
				fileExt[size-2] != 'm' && fileExt[size-2]	!= 'M'	||	// a .bmp
				fileExt[size-3] != 'b' && fileExt[size-4]	!= 'B'	||
				fileExt[size-4] != '.' 
			  )

		   ) { throw invalidOutputFormat(); }

	}
	catch (invalidOutputFormat e)
	{
		std::cout << std::endl << "You provided output-file: '" << outputFile;
		std::cout << "' as an argument to PhotoMagic." << std::endl;
		std::cout << "Please provide file extension '.png' or '.bmp' and try again.";
		std::cout << std::endl << std::endl;
		return -1;
	}

	// ========================================================================= sfml
	size = inputImage.getSize();
	sf::RenderWindow window(sf::VideoMode(size.x*2, size.y), "Image encryption");
	window.setPosition(sf::Vector2i(200, 50));
	outputImage.create(size.x, size.y, sf::Color::White);

	// input image - on the left
	inputTexture.loadFromImage(inputImage);
	inputSprite.setTexture(inputTexture);
	inputSprite.setPosition(0, 0);

	// ======================================================== CREATE YOUR LFSR! :)
	// =============================================================================
	LFSR lfsr(lfsr_seed, lfsr_tap);
	// =============================================================================
	// =============================================================================

	// encrypt the output image
	for (int x = 0; x < size.x; ++x)
	{
		for (int y = 0; y < size.y; ++y)
		{
			pixel = inputImage.getPixel(x, y);
			pixel.r = pixel.r ^ lfsr.generate(8);
			pixel.g = pixel.g ^ lfsr.generate(8);
			pixel.b = pixel.b ^ lfsr.generate(8);
			outputImage.setPixel(x, y, pixel);
		}
	}

	// output image - on the right
	outputTexture.loadFromImage(outputImage);
	outputSprite.setTexture(outputTexture);
	outputSprite.setPosition(size.x, 0);

	// draw them
	while (window.isOpen())
	{
		sf::Event event;
		
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		window.clear(sf::Color::White);
		window.draw(inputSprite);
		window.draw(outputSprite);
		window.display();
	}

	if (!outputImage.saveToFile(outputFile))
		return -1;

	return 0;
}


