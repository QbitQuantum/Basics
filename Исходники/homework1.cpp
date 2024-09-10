int main(int argc, char* argv[]) {
	//error messagea
	if  (argc != 5 and argc != 6 and argc != 7) {
		std::cerr << "arguments can not be fit in" << argv[0] ;
		return 1;
	}
	std::string row;
	std::ifstream myFile(argv[1]);

	if (!myFile.good()) {
		std::cerr << "The file is not correct!" << argv[1] << "\n";
	}
	//std::string row; //input each row to a string
	std::vector<std::string> inputs; //Input vectors to hold all the points
	while (std::getline(myFile, row)) {
		inputs.push_back(row);
	}
	std::cout << "The input:"<<std::endl; //print out the input
	for (unsigned int i = 0 ; i < inputs.size() ; ++i ) {
		std::cout << inputs[i] << std::endl;
	}
///////////starts to do the replace, dialation, erosion and floodfill
	std::vector<std::string> results; // create a vector called results for later print out 
	// dilation
	if (argc == 5) {
		results = dilation(inputs, argv[4][0]);
		for (unsigned int i = 0 ; i < results.size() ; ++i ) {
			std::cout << results[i] << std::endl;
		}
	}
	//replace+erosion
	if (argc == 6) {
		std::string a = "replace";
		std::string b = "erosion";
		if (!a.compare(argv[3])) {
			results = replace(inputs, argv[4][0], argv[5][0]);
		}
		if (!b.compare(argv[3])) {
			results = erosion(inputs, argv[4][0], argv[5][0]);
		}
	}
	//floodfill
	if (argc ==7) {
		//convert the string in arguments to integers
		int r = atoi(argv[4]);
		int c = atoi(argv[5]);
		char temp = argv[6][0];
		floodfill(inputs, r, c, temp);
		results = inputs;
	}
	std::cout << "The output:"<<std::endl;
	//print out the output
	for (unsigned int i = 0 ; i < results.size() ; ++i ) {
		std::cout << results[i] << std::endl;
	}
	//output to a file
	std::ofstream outputs;
	outputs.open(argv[2]);
	for (unsigned int i = 0 ; i < results.size() ; ++i) {
		outputs << results[i] <<"\n" ;
	}
	outputs.close();
	return 0;
}