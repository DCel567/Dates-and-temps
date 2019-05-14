#include "pch.h"
#include "data.h"
#include <fstream>
using namespace std;

int main() {
	cout << "Input ifile name.\n";
	string iname;
	cin >> iname;
	ifstream ifs{ iname };
	if (!ifs) cout << "Can't open ifile " << iname << endl;

	ifs.exceptions(ifs.exceptions() | ios_base::badbit);

	cout << "Input ofile name.\n";
	string oname;
	cin >> oname;
	ofstream ofs{ oname };
	if (!ofs) cout << "Can't open ofile " << oname << endl;

	vector<Year> ys;
	while (true) {
		Year y;
		if (!(ifs >> y)) break;
		ys.push_back(y);
	}
	cout << "Read " << ys.size() << " year notes.\n";

	//for (Year& y : ys) print_year(ofs, y);
}