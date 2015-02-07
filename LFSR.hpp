#include <string>
#include <vector>

using namespace std;

class LFSR
{
public:
	LFSR(string, int);
	
	int step();
	int generate(int);

	friend ostream& operator <<(ostream&, const LFSR&);
	
private:
	vector<int> _seed;
	int _tap;

};


























