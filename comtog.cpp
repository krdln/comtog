#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char ** argv) {
	if (argc < 4 || argc > 5) {
		cerr << "Comment Toggler" << endl;
		cerr << endl;
		cerr << "For each line containg pattern, toggles #-comment for next n-1 of them." << endl;
		cerr << "Toggled lines are printed on output (changed)." << endl;
		cerr << "Provided excessive argument, performs a dry run." << endl;
		cerr << endl;
		cerr << "	Usage: " << argv[0] << " <file> <pattern> <n> <dry?>" << endl;
		cerr << endl;
		return 1;
	}
	int tyle = atoi(argv[3]);
	
	vector<string> v;
	
	{
		ifstream fin(argv[1]);
		if (!fin.is_open()) {
			cerr << "Can't read from " << argv[1] << endl;
		}
		string s;
		int jeszcze = 0;
		while (getline(fin, s)) {
			if (jeszcze == 0 && s.find(argv[2]) != string::npos) jeszcze = tyle;
			if (jeszcze) {
				jeszcze--;
				if (s[0] == '#') s.erase(s.begin());
				else s = "#" + s;
				cerr << s << endl;
			}
			v.push_back(s);
		}
	}
	if (argc == 4 ) {
		ofstream fout(argv[1]);
		if (!fout.is_open()) {
			cerr << "Can't write to " << argv[1] << endl;
		}
		for (string & s : v) fout << s << endl;
	}
	
	return 0;
}
