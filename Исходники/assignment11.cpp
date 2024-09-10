int main () {
    vector<string> temp;
	BinarySearchTree<string>* treePtr = new BinarySearchTree<string>();
	string usr_input, input = "f,c,h,a,d,g,j";
	parse(input, temp, del);
	int tSize = tokenSize(input, del);
	cout << "Display the binary search tree as it is being built:\n	";
	for(int i =0; i<tSize; i++) {
		treePtr->add(temp[i]);
		cout << temp[i] << ( ( i < (tSize - 1) ) ? "," : "\n" );
	}
	treePtr->drawBinarySearchTree();
	menu();
	while (true) {
		cout << "\nTrace(" << ( (trace == 0) ? "OFF" : "ON" ) << ") -->YOUR CHOICE-> ";
		getline(cin,usr_input);
		if (usr_input.length() > 1) cout << "\nSingle Character ONLY! " << endl;
		else {
            char in = tolower(usr_input[0]);
			if (in == 'p') treePtr->drawBinarySearchTree();
			else if (in == 'e') cout << "Binary search tree is: " << (treePtr->isEmpty() ? "EMPTY\n": "NOT EMPTY\n");
			else if (in == 'h') cout << "Height: " << treePtr->getHeight() << endl;
			else if (in == 'n') cout << "Number of Nodes: " << treePtr->getNumberOfNodes() << endl;
			else if (in == 'i') {
				cout << "Enter token: ";
				getline(cin, input);
				treePtr->add(input);
				tSize++;
				cout << endl << input << " is inserted to the binary search tree.\n";
			}
			else if (in == 'b') {
				treePtr->clear();
				temp.clear();
				cout << "---- Enter a (\'" << del << "\' separated) string -> ";
				getline(cin, input);
				parse(input, temp, del);
				tSize = tokenSize(input,del);
				for (int i = 0; i< tSize; i++) {
					treePtr->add(temp[i]);
					if (trace == 1) treePtr->drawBinarySearchTree();
				}
			}
			else if (in == 's') {
                treePtr->clear();
				temp.clear();
				cout << "---- Enter a (\'" << del << "\' separated) string -> ";
				getline(cin, input);
				parse(input, temp, del);
				tSize = tokenSize(input,del);
				sort(temp.begin(), temp.end());sort(temp.begin(), temp.end());
                treePtr->sortedArray2BST(temp, 0, tSize-1);
			}
			else if (in == 'r') {
                cout << "Enter token: ";
				getline(cin, input);
				treePtr->remove(input);
			}
			else if (in == 't') trace = (trace + 1) % 2;
			else if (in == 'm') menu();
			else if (in == 'c') {
				treePtr->clear();
				tSize = 0;
			}
			else if (in == 'q') exit(0);
			else cout << "Invalid Input ! " << endl;
		}
	}
}