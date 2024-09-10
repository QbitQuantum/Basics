int main()
{

  // print my name and this assignment's title
  cout << "Lab 5a, The \"MyStaticArray5a.cpp\" Program \n";
  cout << "Programmer: JEREMY THOMPSON\n";
  cout << "Editor(s) used: JNotePad\n";
  cout << "Compiler(s) used: VC++ 2013\n";
  cout << "File: " << __FILE__ << endl;
  cout << "Complied: " << __DATE__ << " at " << __TIME__ << endl;

  StaticArray<int, 1000> a;
  string buf;
  int i = 0;
  
  bool input = true;

  cout << "Enter a number: ";
  cin >> buf;
  cin.ignore(1000, '\n');

  while (input)
  {
    // quit upon entry of q or Q
    if (buf == "q" || buf == "Q") 
      input = false;
    else
    {     
      a[i++] = atoi(buf.c_str());
      cout << "Enter a number or press Q or q to quit: ";
      cin >> buf;
      cin.ignore(1000, '\n');
    }
  }

  // output number of values before 'Q' or 'q'
  if (!input)
    cout << "Number of values entered: " << i << endl; 
 
  // output unsorted list of entered values
  // comma or space-delimited
  for (int j = 0; j < i; j++)
    cout << a[j] << ", ";

  // search loop for an element using lsearch function
  bool search = true;
  
  while (search)
  {
    cout << "\nEnter an element to search for: ";
    cin >> buf;

    // quit upon entry of q or Q
    if (buf == "q" || buf == "Q")
      search = false;
    else
    {
      int j = atoi(buf.c_str());
      cout << "Entered value was found at index: " << a.lsearch(j) << endl;
      
    }
  }
  cout << "\nPress ENTER to continue...";
  cin.get();
}