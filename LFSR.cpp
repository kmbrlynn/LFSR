#include "LFSR.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>

// =================================================== Con/destructors =============
LFSR::LFSR(std::string seed, int tap) : _seedString(seed)
{
	stringToVector();
/*	for (int i = 0; i < seed.size(); ++i)
	{
		try
		{
			if (seed[i] == '0')
				_seed.push_back(0);
			if (seed[i] == '1')
				_seed.push_back(1);
			if (seed[i] != '0' && seed[i] != '1')
				throw notAOneOrZero();
		}
		catch (notAOneOrZero charException)
		{
			std::cout << "LFSR constructor must take a std::string " << std::endl;
			std::cout << "of 0 and 1 characters. Aborting program." << std::endl;
			std::exit(1);
		}
	}
*/
	// back of vect corresponds to 0th bit
	// that is why this is called a 'subtracted' tap bit
	_subtractedTap = _seed.size() - (tap + 1);
}

// =================================================================================
int LFSR::stringToVector()
{
	for (int i = 0; i < _seedString.size(); ++i)
	{
		try
		{
			if (_seedString[i] == '0')
				_seed.push_back(0);
			if (_seedString[i] == '1')
				_seed.push_back(1);
			if (_seedString[i] != '0' && _seedString[i] != '1')
				throw notAOneOrZero();
		}
		catch (notAOneOrZero charException)
		{
			std::cout << "LFSR constructor must take a std::string ";
			std::cout << "of 0 and 1 chars" << std::endl;
			return 1;
		}
	}
	
	return 0;
}
// =================================================================================
int LFSR::vectorToString()
{
	//std::vector<int>::const_iterator iter;
	//for (iter = lfsr._seed.begin(); iter != lfsr._seed.end(); ++iter)
	
	for(int i = 0; i < _seed.size(); ++i)
	{
		if (_seed[i] == 0)
			_seedString[i] = '0';
		if (_seed[i] == 1)
			_seedString[i] = '1';
	}

	return 0;
}

// =================================================================================
int LFSR::step()
{
	// XOR the first bit and the subtracted tap bit
	int xorBit = _seed[0] ^ _seed[_subtractedTap];

	// shift all the bits down
	for(int i = 1; i < _seed.size(); ++i)
		_seed[i-1] = _seed[i];

	_seed.back() = xorBit;

	// match the string representation to the vector representation
	vectorToString();

	return xorBit;
}

// =================================================================================
int LFSR::generate(int k)
{
	// a 'bit sequence' is the sequence of bits returned by step() 
	// After k calls to step, the bit sequence is k bits long
	int integerValueOfBitSequence = 0;

	for(int i = 0; i < k; ++i)
		integerValueOfBitSequence  = (integerValueOfBitSequence * 2) + step();

	return integerValueOfBitSequence;
}

// =================================================================================
std::ostream& operator <<(std::ostream& outStream, const LFSR& lfsr)
{
	// print one step
//	std::vector<int>::const_iterator iter;
//	for (iter = lfsr._seed.begin(); iter != lfsr._seed.end(); ++iter)
//		outStream << *iter;
//	lfsr.vectorToString();
	outStream << lfsr._seedString;

	return outStream;
}
























