#include <iostream>
#include "load.h"

using namespace std;

int main(int argc, char *argv[])
{
	cout << "Initiating..." << endl;
	if (argc < 3) // input given
	{		// bad input
		cout << "Error!" << endl;
		cout << "Usage: " << argv[0] << " [-f configFile | -i]" << endl;
		cout << "\t -f, --file" << endl;
		cout << "\t\t Run program with given configFile" << endl;
		cout << "\t -i, --interactive" << endl;
		cout << "\t\t Run program with config params passed through command line" << endl;
		exit(EXIT_FAILURE);
	}

	FILE *config = nullptr;
	config = fopen(argv[2], "r");
	if (config == nullptr)
	{
		fprintf (stderr, "*** Failed to open config file \'%s\' for reading! ***\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	/* Initialize everything right here */
	load_world(argv[1], config);

	cout << "Finished simulation" << endl;
	return 0;
}