#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

// ======================================= validate arguments to main 
class neitherZeroNorOne
{};

class invalidArgc
{};

class invalidInputFile
{};

class invalidOutputFormat
{};

bool bitstringAndTapAreValid(std::string, int);

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


