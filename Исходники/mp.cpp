// was used to test the scanner
int TestScanner(  string argv ) // int TestScanner(  int argc, char* argv[] )
{
	// name of the file to parse through
	std::string fName = argv;

	Scanner* dispatcher = new Scanner();
	dispatcher->openFile(fName);

	// Adjusted to print tokens to text file
	std::ofstream out("tokens.txt");
    std::streambuf *coutbuf = std::cout.rdbuf();	//save old buffer
    std::cout.rdbuf(out.rdbuf());					//redirect std::cout to tokens.txt


	// Adjusted to print in the proper order
	cout << setw(15) << left << "Token" << setw(8) << "Line #" << setw(10) << "Column #" << setw(45) << "Lexeme"<< endl;	 
	while (dispatcher->hasToken())
	{
		 //Keep on separate couts so that getToken() executes first
		cout << setw(15) << left << EnumToString(dispatcher->getToken()); //set the token	
			cout << setw(8) << dispatcher->getLineNumber() << setw(10) << dispatcher->getColumnNumber();

		if (dispatcher->getLexeme().size() > 45){
			string temp;
			temp = dispatcher->getLexeme().substr(0,44);
			cout << temp << endl;

		} else
			cout << dispatcher->getLexeme()<< endl;
	}

	cout << setw(15) << left << EnumToString(dispatcher->getToken()) 
		<< setw(8) << dispatcher->getLineNumber() << setw(10) << dispatcher->getColumnNumber() 
		<< setw(45) << dispatcher->getLexeme() << endl << endl;

	std::cout.rdbuf(coutbuf);						//reset to standard output

	// press enter to exit
	printf("Done. Press Enter to exit.\n");
	cin.get();
	return 0;
}