#include <string>
#include <vector>

class notAOneOrZero
{};

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


