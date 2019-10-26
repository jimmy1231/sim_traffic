#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
	cout << "Initiating..." << endl;
	if (argc > 1) { // input given
		cout << argv[1] << endl;
	} else {		// bad input
		cout << "Error!" << endl;
		cout << "Usage: " << argv[0] << " [-f configFile | -i]" << endl;
		cout << "\t -f, --file" << endl;
		cout << "\t\t Run program with given configFile" << endl;
		cout << "\t -i, --interactive" << endl;
		cout << "\t\t Run program with config params passed through command line" << endl;
	}
    cout << "Finishing..." << endl;
    return 0;
}