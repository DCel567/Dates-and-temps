//17.05.2019 version 1.0

//program reads data from input file (ifile.txt as example)
//which consists of year, month, day, hour and temperature
//in { year @year@ { month @month@ (@day@ @month@ @temperature@) } }
//format. Then prints all read data to output file (ofile.txt as example)
//No defense against false input

#include "pch.h"
#include "data.h"
#include <fstream>
using namespace std;

int main() {
	cout << "Input ifile name.\n";
	string iname;
	cin >> iname;
	ifstream ifs{iname + ".txt"};
	if (!ifs) cout << "Can't open ifile " << iname << endl;

	ifs.exceptions(ifs.exceptions() | ios_base::badbit);

	cout << "Input ofile name.\n";
	string oname;
	cin >> oname;
	ofstream ofs{ oname + ".txt" };
	if (!ofs) cout << "Can't open ofile " << oname << endl;

	vector<Year> ys;
	while (1) {
		Year y;
		if (!(ifs >> y)) break;
		ys.push_back(y);
		//reading and remembering data from input file
	}
	cout << "Read " << ys.size() << " year notes.\n";

	for (Year& y : ys) print_year(ofs, y);
	//printing all read data to output file
}