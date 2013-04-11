#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char ** argv) {
	bool dry = false;
	bool present = false;
	bool valid_options = false;
	
	if (argc == 4) valid_options = true;
	if (argc == 5) {
		if (argv[4][0] == 's') present = true, valid_options = true;
		if (argv[4][0] == 'd') dry = true, valid_options = true;
	}
	
	if (!valid_options) {
		cerr << "Comment Toggler" << endl;
		cerr << endl;
		cerr << "For each line containg pattern, toggles #-comment for next n-1 of them." << endl;
		cerr << "Toggled lines are printed on output (changed)." << endl;
		cerr << "Provided excessive argument, performs a dry run," << endl;
		cerr << "or shows present state instead of changed." << endl;
		cerr << endl;
		cerr << "	Usage: " << argv[0] << " <file> <pattern> <n> [dry|show]" << endl;
		cerr << endl;
		return 1;
	}
	int tyle = atoi(argv[3]);
	
	vector<string> v;
	
	{
		ifstream fin(argv[1]);
		if (!fin.is_open()) {
			cerr << "Can't read from " << argv[1] << endl;
			return 1;
		}
		string s;
		int jeszcze = 0;
		while (getline(fin, s)) {
			if (jeszcze == 0 && s.find(argv[2]) != string::npos) jeszcze = tyle;
			if (jeszcze) {
				jeszcze--;
				if (present) cerr << s << endl;
				if (s[0] == '#') s.erase(s.begin());
				else s = "#" + s;
				if (!present) cerr << s << endl;
			}
			v.push_back(s);
		}
	}
	if (!dry) {
		ofstream fout(argv[1]);
		if (!fout.is_open()) {
			cerr << "Can't write to " << argv[1] << endl;
			return 1;
		}
		for (string & s : v) fout << s << endl;
	}
	
	return 0;
}
