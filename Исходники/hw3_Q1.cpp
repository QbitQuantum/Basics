int main()
{
	BST tree;

	string inputFileName = "hw3_Q1_input.txt"; // input file with operations 
	string outputFileName = "hw3_Q1_output.txt"; // output file

	//open files
	ifstream inputFile;
	inputFile.open(inputFileName.c_str());
	if (!inputFile)
		cout << "Error opening the input file " << endl;
	
	outputFile.open(outputFileName.c_str());
	if (!outputFile)
		cout << "Error opening the output file " << endl;

	//read operations from the input file
	string op;
	int x;
	while(inputFile >> op)
	{
		if (op == "insert")
		{
			inputFile >> x; // read the value x for insert
			tree.insert(x);
			//cout << "Inserted " << x << endl;
			//tree.displayInOrder();
			//cout << endl;
		}
		if (op == "remove")
		{
			inputFile >> x; // read the value x for remove 
			tree.remove(x);
			//cout << "Deleted " << x << endl;
			//tree.displayInOrder();
			//cout << endl;
		}