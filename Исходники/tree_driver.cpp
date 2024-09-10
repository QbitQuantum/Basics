int main( )
{
    BST<int> intBST;	// A BST to perform tests on
    char choice;   		// Command entered by the user
    
    cout << "I have initialized an empty BST of int." << endl;
 
    do
    {
        printMenu( );
        cout << "Enter choice: ";
        cin >> choice; 
        choice = toupper(choice);
        int n = 0;
        
        switch (choice)
        {
            case 'A': // add code to prompt the user for a number n
					  // and insert n random numbers 0-999 into the tree
					  cout << "How many numbers want to be inserted: ";
					  cin >> n;
					  for(int i = 0; i < n; i++)
					  {
					  	intBST.insert(rand() % (999 + 1));
					  }
					  cout << n << " number(s) have been inserted.\n";
                      break;
			case 'H': // add code to print the resuly of height()
					  cout << "The height is: " << intBST.getheight() << endl;
					  cout << "\n";
                      break;
            case 'L': // add code to print the result of leafCount()
            		  cout << "The number of leaves is: " << intBST.getleafcount() << endl;
            		  cout << "\n";
                      break;
            case 'G': // add code to print the result of graph()
            		  intBST.graph(cout);
            		  cout << "\n";
                      break;
            case 'E': // add code to print the result of empty( )
            		  cout << "The tree" << (intBST.empty() ? " is" : " is not") << " empty." << endl;
              		  cout << "\n";
                      break;
            case 'P': // add code to print the result of inorder(), height() and leafCount() with labels
            		  cout << "Display tree by inorder form:" << endl;
            		  intBST.inorder(cout);
            		  cout << endl;
            		  cout << "The height is: " << intBST.getheight() << endl;
            		  cout << "The number of leaves is: " << intBST.getleafcount() << endl;
            		  cout << "\n";
                      break;
            case 'I': // add code to insert a user given item into the tree using insert()
            		  cout << "Input a number: ";
            		  cin >> n;
            		  intBST.insert(n);
                      break;
            case 'S': // add code to search for a user given item in the tree using search() and print result
            		  cout << "Input a number: ";
            		  cin >> n;
            		  cout << "Item " << n << (intBST.search(n) ? " is" : " is not") << " in the tree." << endl;            		  
            		  cout << "\n";
                      break;
            case 'R': // add code to remove a user given item in the tree using remove()
            		  cout << "Input a number: ";
            		  cin >> n;
            		  intBST.remove(n);
                      break;     
            case 'Q': cout << "Test program ended." << endl;
                      break;
            default:  cout << choice << " is invalid." << endl;
        }
    }
    while ((choice != 'Q'));
 
    return EXIT_SUCCESS;
}