#include <iostream>
#include <vector>

// converts an integer to a bitstring
// bitstring is represented as a vector of integers
// where least significant bit corresponds to vector[0]

using namespace std;

void integer_to_binary(int num, vector<int>& bitstring)
{
	int	bit = num % 2;
	bitstring.push_back(bit);
	
	if (num > 0)
		integer_to_binary(num/2, bitstring);
}

int main(int argc, char* argv[])
{
	char ascii = *argv[1];
//	char ascii = 'a';
	int integer = (int)ascii;
	vector<int> bitstringVect;

	integer_to_binary(ascii, bitstringVect);

	cout << ascii << " = " << integer << " = ";

	// print with reverse mapping because
	// bitstringVect[0] corresponds to least significant bit
	vector<int>::iterator iter;
	for (iter = bitstringVect.end(); iter != bitstringVect.begin(); --iter)
		cout << *iter;

	cout << endl;

	return 0;
}
