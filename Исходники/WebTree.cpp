void WebTree::parseInput(string i) {
	// Parses the input
	
	string url, keywords, temp;

	int breakpoint, level, rank, currentLevel=0;

	TreeNode *tN = NULL,
			 *tempTN = NULL;
	
	ifstream input(i.c_str());

	if(input.fail()) {
		cout<<"unable to open input file "<<i<<endl;
		exit(0);
	}
	
	while(!input.eof() && getline(input,temp,'\n')) {
		level = temp.find_first_not_of(' ');
		temp = temp.substr(level,temp.length()-level);
		level /= 3;
		breakpoint = temp.find(' ');
		url = temp.substr(0, breakpoint);
		temp = temp.substr(breakpoint+1,temp.length()-breakpoint-1);
		breakpoint = temp.find(' ');
		rank = atoi(temp.substr(0,breakpoint).c_str());
		if(breakpoint>-1) keywords = temp.substr(breakpoint+1,temp.length()-breakpoint-1);

		if(!head) {
			head = new TreeNode(url, rank, size, keywords, tN);
			tN = head;
		}

		else {
			while(currentLevel >= level) {
				tN = tN->getParent();
				currentLevel--;
			}
	
			tempTN = NULL;
			tempTN = new TreeNode(url, rank, size, keywords, tN);
	
			tN->children.add(tempTN);
			tN->children.goTail();
			tN = tN->children.get();
			currentLevel++;
		}

		keywords = "";

		size++;
	}

	input.close();
}