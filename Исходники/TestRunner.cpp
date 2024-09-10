// all comparisons done with upper case (mostly because of Open MVS
void TestRunner::run (int ac, const char **av)
{
	TString testCase;

	if (ac == 1) {
		usage(av[0]);
		return;
	} // if

	for (int i = 1; i < ac; ++i) {
		testCase = av [i];
		testCase.ToUpper();
		if ( testCase == "-H" ) {
			usage(av[0]);
			return;
		} else if ( testCase == "-ALL" ) {
			runAllTests();
			continue;
		} else if (testCase == "-LOG") {
			if (i < ac - 1) {
				setLogToFileNamed(av[++i]);
			} // if
			continue;
		} else if (testCase == "-OUT") {
			if (i < ac - 1) {
				++i;
				int outfile = open(av[i], O_RDWR | O_CREAT | O_TRUNC, 0660);
				if (outfile > 0) {	// make it stdout
					std::cout << "redirecting output to " << av[i] << std::endl;
					close(1);
					dup(outfile);	// ignore possible errors for now
					close(outfile);
				} else {
					std::cout << "output redirection failed" << std::endl;
				} // if
			} // if
			continue;
		} else if (testCase == "-ERR") {
			if (i < ac - 1) {
				++i;
				int outfile = open(av[i], O_RDWR | O_CREAT | O_TRUNC, 0660);
				if (outfile > 0) {	// make it stdout
					std::cerr << "redirecting errors to " << av[i] << std::endl;
					close(2);
					dup(outfile);	// ignore possible errors for now
					close(outfile);
				} else {
					std::cerr << "error redirection failed" << std::endl;
				} // if
			} // if
			continue;
		} else if (testCase == "-LIST") {
			listTests();
			continue;
		} else if (testCase == "-WAIT") {
			fWait = true;
			continue;
		} // if

		Test *test;
		for ( test = fMappings->first(); test != 0 ;
			  test = fMappings->next() ) {
			TString className = test->getClassName();
			className.ToUpper();

			if ( className == testCase ) {
				run(test->getSuite());
				break;
			} // if
		} // for

		if ( !test ) {
			std::cout << "Test " << testCase << " not found." << std::endl;
			return;
		}
	}
}