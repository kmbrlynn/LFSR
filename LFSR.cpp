#include "LFSR.hpp"
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
int LFSR::stringToVector()
{
	for (int i = 0; i < _seedStr.size(); ++i)
	{
		try
		{
			if (_seedStr[i] == ASCII_ZERO)
				_seedVect.push_back(0);

			if (_seedStr[i] == ASCII_ONE)
				_seedVect.push_back(1);

			if (_seedStr[i] != ASCII_ZERO && _seedStr[i] != ASCII_ONE)
				throw notAOneOrZero();
		}
		catch (notAOneOrZero e)
		{
			std::cout << std::endl << "Encountered character: '" << _seedStr[i];
			std::cout << "' at _seedStr[" << i << "] " << std::endl;
			std::cout << "LFSR constructor may take a std::string containing only '";
			std::cout << ASCII_ZERO << "' or '" << ASCII_ONE << "' characters.";
			std::cout << std::endl << std::endl;
			return 1;
		}
	}
	return 0;
}
// =================================================================================
int LFSR::vectorToString()
{
	for(int i = 0; i < _seedVect.size(); ++i)
	{
		if (_seedVect[i] == 0)
			_seedStr[i] = ASCII_ZERO;

		if (_seedVect[i] == 1)
			_seedStr[i] = ASCII_ONE;
	}
	return 0;
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


