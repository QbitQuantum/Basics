void testBQ( const string & fileName )
{
  cout << "\n********** Priority queues **********\n\n";
  ifstream f1;
  f1.open( fileName.c_str() );
  if( f1.fail( ) ){
    cout << "Error opening " << fileName;
    exit( 1 );
  } 

  int numItems = 10000;

  cout << "Part 1. Inserting words in Binomial Queue\n";
  BinomialQueue BQ;
  HashTable HT ( BUCKET_SIZE );

  string wordToSearch, line;
  int numberOfLines = 1;
  BQ.setNumberOfComparisonsAndAssignments( 0, 0 );
  while( f1 ){ // read the document file
    getline( f1, line );
    string::iterator it;
    for( it = line.begin( ); it < line.end( ); it++ ){
      if( isspace( *it ) || ( ispunct( *it ) && *it != 39) ){
      // || *it == 34){
        if( wordToSearch != "" && !HT.contains( wordToSearch ) ){
          BinomialNode *bn = BQ.insert( wordToSearch, numberOfLines );
          // BinomialNode *bn = BQ.insertFast( wordToSearch, numberOfLines ); 
          HT.insert( wordToSearch , bn );
        }
        else if( HT.contains( wordToSearch ) ){
          HT.updateLineNumberForWord( wordToSearch, numberOfLines );
        }
        wordToSearch.clear();
        continue;
      }
      else{
        wordToSearch += *it; // build up the word
      }
    }
    numberOfLines++;
    line.clear(); // prepare to read a new line
  }

  cout << BQ.getCurrentSize( ) << " items inserted in Binomial Queue\n\n";
  // BQ.printRoots( );  // debugging

/************************************************************
 * (2) Count and print out the total number of comparisons 
 * and assignments executed for the insertions of all the 
 * N elements into the binomial queue.
 ***********************************************************/
  cout << "Part 2. Print out number of operations\n";
  cout << "Number of comparisons : " << BQ.getCmps( ) << endl;
  cout << "Number of assignments : " << BQ.getAsmts( ) << endl;

/************************************************************
 * (3) Test the deleteMin() operation by applying a sequence 
 * of 10 deleteMin() and by printing out the result (i.e. key 
 * deleted along with associated line numbers).
 ***********************************************************/
  cout << "\nPart 3. ";
  cout << "Executing 10 deleteMin() operations:\n";
  for( int i = 0; i < 10; ++i ){
    string minValue = BQ.findMin( ); // save element for printing line numbers
    cout << "Min. val.:  " << setw( 10 ) << left << minValue << "  "; // print element
    HT.printLineNumbersForWord( minValue ); 
    BQ.deleteMin( ); // delete here.
    HT.remove( minValue );
  }
  cout << endl;
/************************************************************
 * (4) Test the function find() as follows: Prompt the user 
 * to input a string key. Execute the private function 
 * find(key). If find returns a pointer to a node that indeed 
 * holds key printout that find() was successful; printout 
 * the set of line numbers as well. Otherwise, printout that 
 * find() did not find the key.
 ***********************************************************/
  cout << "Part 4. Testing find() function [once]:\n";
  cout << "Enter a string key: ";
  string key;
  cin >> key;
  BinomialNode *keyNode1 = HT.find( key );
  if( keyNode1 ){
    cout << "find() function found the key \"" << key << "\"";
    cout << " in lines: ";
    HT.printLineNumbersForWord( key ); 
    cout << endl;
  }
  else{
    cout << "find() function did not find the key \"" << key << "\"" << endl;
  }
  // delete keyNode1;

/******************************************************************
 * (5) You are ready to implement now the remove(key) operation. 
 * For a given key, find its position p (p is a pointer) in the 
 * priority queue using the hash table. If the key is found delete
 * it from the bq (Hint: your code should percolate the key up all 
 * the way to the root and then delete the root). Test your 
 * implementation by applying a sequence of remove(key) operations, 
 * and verify their correctness. For instance after remove(key), 
 * find(key) should return “not found”. Prompt the user 5 times 
 * to input a key. Execute then the remove(key) operation and 
 * verify (by printing whether the removal was successful or not).
 *****************************************************************/
  cout << "Part 5. Removing 5 keys and verifying the result" << endl;
  key = "";
  // BinomialNode *keyNode2;
  for( int i = 0; i < 5; ++i ){
    cout << "Enter a key to remove: ";
    cin >> key;
    BinomialNode *keyNode2 = HT.find( key );
    if( keyNode2 ){
      cout << "The key: \"" << key << "\" is removed " << endl;
      BQ.remove( keyNode2 );  // remove from Binomial Queue
      HT.remove( key );       // update Hash Table as well
      cout << "Trying to find it..." << endl;
      BinomialNode *temp = HT.find( key );
      if( temp ) // this should not happen
        cout << "Hmm.. \"" << temp->element << "\" found!" << endl;
      else       // good!
        cout << "Good! Deletion is successful" << endl;

      // cout << BQ.getCurrentSize( ); // debugging
      // BQ.printRoots( ); 
    }
    else{ 
      cout << "Cannot remove because the key \"" << key << "\" was not found" << endl;
    }
  }
/******************************************************************
 * (6) Write a faster insert(key) function for the binomial queue. 
 * In order to achieve that you have to modify the merge() function 
 * and make it specific to the merging of one element only.
 *****************************************************************/

  cout << "\nPart 6. Testing fast insert(key) function [5 times]\n";
  cout << "Keys will be inserted in line 0\n";
  for( int i = 0; i < 5; ++i ){
    key = "";
    cout << "Enter a key to insert: ";
    cin >> key;
    BinomialNode *bn = BQ.insertFast( key, 0 );
    HT.insert( key , bn );
    cout << "\"" << key << "\" inserted in Binomial Queue at address: " << bn << endl;
    cout << "\"" << key << "\" found in Hash Table and has pointer:   " << HT.find( key ) << endl;
    // cout << BQ.getCurrentSize( ); // debugging
    // BQ.printRoots( ); 
  }

  cout << "\nPart 6a. Checking the improvement of insertFast() function over the original insert() function [3 times]: \n";
  
  for( int i = 0; i < 3; ++i ){
    string w3 = "";
    cout <<  "\nEnter the key to check: ";
    cin >> w3;
    BQ.setNumberOfComparisonsAndAssignments( 0, 0 );
    cout << "insert(\"" << w3 << "\", 10 )\n";
    BinomialNode *bn = BQ.insert( w3, 10 );
    HT.insert( "w3", bn );
    cout << "\t\tNumber of comparisons = " << BQ.getCmps( ) << endl;
    cout << "\t\tNumber of assignments = " << BQ.getAsmts( );
    // BQ.printRoots( ); 

    cout << "\nNow remove it, reset the counters and test in again:\n\n";
    BQ.remove( bn );
    HT.remove( "w3");
    BQ.setNumberOfComparisonsAndAssignments( 0, 0 );
    cout << "insertFast(\"" << w3 << "\", 10 )\n";
    BinomialNode *bn2 = BQ.insertFast( w3, 10 );
    HT.insert( "w3", bn2 );
    cout << "\t\tNumber of comparisons = " << BQ.getCmps( ) << endl;
    cout << "\t\tNumber of assignments = " << BQ.getAsmts( );    
    // BQ.printRoots( ); 
  }
////////////////////////////////////////////////////////////////////////////////

  f1.close();
  cout << endl << "End of program. Thanks" << endl;
}