int main(int argc, char* argv[])
{
	// ATL helper macro to convert between ANSI and Unicode strings.
	USES_CONVERSION;
	char oneMoreTime; // ('n' or 'y')
	char pathToComServer[100] = {0}; 

	do
	{
		// Get path to COM server.
		cout << "Please enter path to COM server (or *tlb file)";
		ITypeLib* pTypeLib = NULL;
		cin.ignore(0, '\n');
		cin.get(pathToComServer, 100);
	
		// Load type information for a COM server.
		if(SUCCEEDED(LoadTypeLibEx(A2W(pathToComServer), REGKIND_DEFAULT, &pTypeLib)))
		{
			// Read info about the type lib.
			DumpLibraryStats(pTypeLib);

			// Read info about COM types.
			DumpComTypes(pTypeLib);

			// COM clean up.
			pTypeLib->Release();
		}

		// Want another?
		cout << "Do you want to enter another? (y or n)";
		cin >> oneMoreTime;  
	}while (oneMoreTime != 'n');

	return 0;
}