/*************************************************************************
* Date last modified: July 9th, 2013
* Description: Gets user input for SML program 
* Input parameters: 
* Returns:
* Precondition: User inputs a valid program
* Postcondition: Memory is updated with users program
*************************************************************************/
void SimpletronSimulator::getProgram(Simpletron &program)
{
	int instruction = 00000, counter = 000;

	cout << "*** Welcome to Simpletron ***" << endl;
	cout << "*** Please enter your program one instruction at a time ***" << endl;
	cout << "*** I will type the location number followed by a question mark ***" << endl;
	cout << "*** Then type the word for that memory location ***" << endl;
	cout << "*** Type -99999 to stop entering your program ***" << endl;

	while(instruction != -99999)
	{
		_flushall();
		cout << counter<< " ? ";
		cin >> instruction;
		if(instruction != -99999)
		{
			program.memory[counter] = instruction;
		}
		counter++;
	}
	cout << "*** Program loading completed ***" << endl;
}