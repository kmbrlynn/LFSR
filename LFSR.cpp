#include <SFML/Graphics.hpp>
#include "LFSR.hpp"
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>

const char ASCII_ZERO = '0';
const char ASCII_ONE = '1';

// =================================================== Con/destructors =============
LFSR::LFSR(std::string seed, int tap) : _seedStr(seed)
{
	// create a vector representation of the seed, given the string representation.
	// we won't deal with the string representation until we are ready to print
	stringToVector();

	// the back of the vector corresponds to the 0th bit
	_subtractedTap = _seedVect.size() - (tap + 1);
}

// =================================================================================
void LFSR::stringToVector()
{
	try
	{
		for (int i = 0; i < _seedStr.size(); ++i)
		{
			if (_seedStr[i] == ASCII_ZERO)
				_seedVect.push_back(0);

			if (_seedStr[i] == ASCII_ONE)
				_seedVect.push_back(1);

			if (_seedStr[i] != ASCII_ZERO && _seedStr[i] != ASCII_ONE)
			{
				_seedVect.clear();
				throw translateAlphanumericToBinary();
			}
		}
	}
	catch (translateAlphanumericToBinary e)
	{
		std::vector<int> integerVect;
		int integerVectTotal = 0;

		for (int i = 0; i < _seedStr.size(); ++i)
		{
			// cast the ascii character to its integer value, 
			// and push it to the temporary vector of integers
			integerVect.push_back((int)_seedStr.at(i));	
			integerVectTotal = integerVectTotal + integerVect[i];
		}
		
		// add up the integer values for each character in the string, 
		// convert them into binary, and put them in the _seedVect
		integerToBinary(integerVectTotal);
		
		// keep the string representation up to date with the vector representation
		vectorToString();
	}
}
	
// =================================================================================
void LFSR::vectorToString()
{
	for(int i = 0; i < _seedVect.size(); ++i)
	{
		if (_seedVect[i] == 0)
			_seedStr[i] = ASCII_ZERO;

		if (_seedVect[i] == 1)
			_seedStr[i] = ASCII_ONE;
	}
}

// =================================================================================
void LFSR::integerToBinary(int num)
{
	int quotient = num / 2;
	int bit = num % 2;
	_seedVect.push_back(bit);

	if (num > 0)
		integerToBinary(quotient);
}

// =================================================================================
int LFSR::step()
{
	// XOR the first bit and the subtracted tap bit
	int xorBit = _seedVect[0] ^ _seedVect[_subtractedTap];

	// shift all the bits down
	for(int i = 1; i < _seedVect.size(); ++i)
		_seedVect[i-1] = _seedVect[i];

	_seedVect.back() = xorBit;

	// keep the string representation up to date with the vector representation
	vectorToString();

	return xorBit;
}

// =================================================================================
int LFSR::generate(int k)
{
	// 'bit sequence' refers to the sequence of bits returned by a sequence of steps 
	// After k calls to step(), the bit sequence is k bits long
	int integerValueOfBitSequence = 0;

	for(int i = 0; i < k; ++i)
		integerValueOfBitSequence  = (integerValueOfBitSequence * 2) + step();

	return integerValueOfBitSequence;
}

// =================================================================================
std::ostream& operator <<(std::ostream& outStream, const LFSR& lfsr)
{
	// print the current string representation of the register
	outStream << lfsr._seedStr;
	return outStream;
}

// ===============================================================================bool bitstringAndTapAreValid(std::string bitstring, int tap)
bool bitstringAndTapAreValid(std::string bitstring, std::string tap)
{		
	for (int i = 0; i < bitstring.size(); ++i)
	{
		if (bitstring[i] != ASCII_ONE && bitstring[i] != ASCII_ZERO)
		{
			std::cout << std::endl << "You provided '" << std::cout << bitstring;
			std::cout << "' as a bitstring, which may only contain 1s and 0s.";
			std::cout << std::endl << std::endl << "If you would rather provide ";
			std::cout << "an alphanumeric password," << std::endl;
			std::cout << "do not provide a tap position. Please try again.";
			std::cout << std::endl << std::endl;
			return false;
		}
	}

	// somewhat lame and hackish validation, but it works, assuming the
	// bitstring is not larger than 99 characters.	
	std::string::iterator iter;
	for (iter = tap.begin(); iter != tap.end(); ++iter)
	{
		if (*iter != '0' && *iter != '1' && *iter != '2' && 
			*iter != '3' && *iter != '4' && *iter != '5' &&
			*iter != '6' && *iter != '7' && *iter != '8' && *iter != '9')
		{		
			std::cout << std::endl;
			std::cout << "You provided '" << tap << "' as a tap position for your ";
			std::cout << "bitstring." << std::endl << "Your tap position must be ";
			std::cout << "an integer. Please try again." << std::endl << std::endl;	
			return false;
		}
	}

	// convert string to int via cstring (stoi not available in c++11)
	char* tap_cstring = new char[tap.length()+1]; // remember null terminator
	std::strcpy(tap_cstring, tap.c_str());
	int tap_integer = atoi(tap_cstring);
	if (tap_integer < 0 || tap_integer+1 > bitstring.size())
	{
		std::cout << std::endl;
		std::cout << "You provided " << tap_integer << " as tap position, which ";
		std::cout << "is not an integer " << std::endl << "within the bounds ";
		std::cout << "of your bitstring. Please try again.";
		std::cout << std::endl << std::endl;
		return false;
	}

	return true;
}


