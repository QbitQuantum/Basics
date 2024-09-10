int main()
{

   List list1;
   List copy;

   cout << "---------- This tests the list ADT interface ----------" << endl;
   try {
	   cout << "Adding 5, 23, 4, 67, 1 to list 1...\n";
           list1.insert(5.2);
	   list1.insert(23.1);
	   list1.insert(4.5);
	   list1.insert(67.1);
	   list1.insert(1.0);
	   

   }
   catch( ListException & e1)
   {
          cerr << e1.what();
   }
   catch ( ListIndexOutOfRangeException & e2)
   {
       //handling the exception here
   } 
   catch (...)
   {
         //handling all the other exceptions here
   }

   cout << list1 << endl;

   cout << "Removing item #2 from list 1...\n";
   list1.remove(1);
   cout << list1 << endl; 

   cout << "Copying list 1...\n";
   copy = list1;
   cout << copy << endl;

   cout << "Removing 3rd item from copy of list 1...\n";
   copy.remove(3);
   cout << copy << endl; 
   cout << "Deleting last number from list..." << endl;
   copy.pop_back(5);
   cout << copy << endl; 
   copy.push_back(17.7); 
   cout << "Inserting number to end of list..." << endl;
   cout << copy << endl;
   cout << "The size of the list is..." << endl;
   cout << copy.getLength(); 
   
   return 0;

}