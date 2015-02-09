#include "LFSR.hpp"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

// =================================================== Con/destructors =============
LFSR::LFSR(string seed, int tap)
{
	for (int i = 0; i < seed.length(); ++i)
	{
		if (seed[i] == '0')
			_seed.push_back(0);
		if (seed[i] == '1')
			_seed.push_back(1);
	}

	// back of vect corresponds to 0th bit
	_tap = _seed.size() - (tap + 1);
}

// =================================================================================
int LFSR::step()
{
	// XOR the first bit and the tap bit
	int xorBit = _seed[0] ^ _seed[_tap];

	// shift all the bits down
	for(int i = 1; i < _seed.size(); ++i)
	{
		_seed[i-1] = _seed[i];
	}

	_seed.back() = xorBit;
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
ostream& operator <<(ostream& outStream, const LFSR& lfsr)
{
	// print one step
	vector<int>::const_iterator iter;
	for (iter = lfsr._seed.begin(); iter != lfsr._seed.end(); ++iter)
		outStream << *iter;

	return outStream;
}

