void string_invert(std::string IN){

	std::cerr << "\tREVERSED: ";
	
	std::string OUT   = std::string("");
	int 		SIZE  = IN.size();
	int 		index = SIZE-1;
	pid_t 		pid;
	int 		status;

	// fork
	for ( int j = 0; j < SIZE; j++) {	// create SIZE number of forks

		if ((pid = fork()) == 0) {		// child, break out
			break;
		} else {						// parent keep making children
			wait(NULL);
			index--;
		}
	}

	std::cerr << IN[index];
	if(index == 0) std::cout << std::endl << std::endl;
	_Exit(0);
}