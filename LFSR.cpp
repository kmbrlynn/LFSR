#include "LFSR.hpp"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

// =================================================== Con/destructors =============
LFSR::LFSR(string seed, int tap)
{
	// may want to do some exception handling... 
	//		in case (seed[i] != '0' || seed[i] != '1') 
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

}

// =================================================================================
ostream& operator <<(ostream& os, const LFSR& lfsr)
{
	// print one step
	vector<int>::const_iterator iter;
	for (iter = lfsr._seed.begin(); iter != lfsr._seed.end(); ++iter)
		os << *iter;

	// as well as its last bit
//	os << " " << lfsr._seed.back();

	return os;
}








//	for (int i = 0; i < lfsr._register.size(); ++i)
//		os << lfsr._seed[i];



