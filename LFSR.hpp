#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

// check validity of seed string
class notAOneOrZero
{};

// check validity of command line args
class invalidArgc
{};

class invalidInputFile
{};

class invalidOutputFormat
{};

//class invalidTapPosition
//{};


class LFSR
{
public:
	LFSR(std::string, int);

	int stringToVector();
	int vectorToString();

	int step();
	int generate(int);

	friend std::ostream& operator <<(std::ostream&, const LFSR&);

private:
	std::string _seedStr;
	std::vector<int> _seedVect;
	int _subtractedTap; 
};


