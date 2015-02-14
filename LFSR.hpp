#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

// ======================================= validate arguments to main 
class translateAlphanumericToBinary
{}; // in case the user supplies a password

class invalidArgc
{}; // in case the user doesn't give the correct number of args

class invalidInputFile
{}; // in case the user-specified input file can't be found

class invalidOutputFormat
{}; // in case the user doesn't specify a .png or .bmp output format

bool bitstringAndTapAreValid(std::string, int);
// ensures that a bitstring is made of 0s and 1s
// and that the tap is an integer within the bitstring's bounds

// ============================================================ LFSR
class LFSR
{
public:
	LFSR(std::string, int);

	void stringToVector();
	void vectorToString();

	void integerToBinary(int);

	int step();
	int generate(int);

	friend std::ostream& operator <<(std::ostream&, const LFSR&);

private:
	std::string _seedStr;
	std::vector<int> _seedVect;
	int _subtractedTap; 
};


