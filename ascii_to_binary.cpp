#include <iostream>
#include <vector>

// converts a string of ascii characters
// to a 2D vector of bitstrings
using namespace std;

// given an integer, returns its binary equivalent.
// this is an 8-bit representation of an ascii character
vector<int> integer_to_binary(int num, vector<int>& bitstring)
{
	int quotient = num / 2;
	int	bit = num % 2;
	bitstring.push_back(bit);
	
	if (num > 0)
		integer_to_binary(quotient, bitstring);

	return bitstring;
}

int main(int argc, char* argv[])
{
	string password = argv[1]; 		// string of ascii characters
	vector<int> integer_vect; 		// vector of their integer equivalents
	
	vector<int> char_bitstring_vect;				// vector to hold a char's binary equivalent
	vector< vector<int> > password_bitstring_vect;	// vector of char_bitstring_vect
	
	// create a vector of ascii integers
	string::iterator str_it;
	for (str_it = password.begin(); str_it != password.end(); ++str_it)
	{
		int integer = (int)(*str_it); // cast the ascii to its integer
		integer_vect.push_back(integer); // push to a vect of ints
	}

	// create a vector of character bitstrings
	for(int i = 0; i < integer_vect.size(); ++i)
	{
		// convert the i'th integer to a character bitstring
		vector<int> bitstring = integer_to_binary(integer_vect[i], char_bitstring_vect);
		
		// push the character bitstring to big password bitstring
		password_bitstring_vect.push_back(bitstring);
	}

	// print
	cout << endl << "Bitstring for " << password << " = ";

	cout << endl;

	return 0;
}
