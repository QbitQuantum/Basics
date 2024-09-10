int main()
{
  cout << "\n\nLab 10a LinkedListDriver.cpp\n";
  cout << "Programmer: Aysin Oruz \n";
  cout << "Editor(s) used: JNotePad and Xcode \n";
  cout << "Compiler(s) used: Xcode and Terminal \n";
  cout << "Description: The purpose of this lab is for you to learn how to create and apply aLinkedList.";
  cout << "File: " <<  __FILE__ << endl;
  cout << "Compiled: " << __DATE__ << " at " << __TIME__ << endl;
  
  LinkedList<int> s;
  int l;
  
  //isEmpty Function Test
  cout << "\nTesting isEmpty() Function\n";
  cout << "Expected >> Empty\n";
  assert(s.isEmpty() == 1);
  if (s.isEmpty() == 1)
    cout << "Actual >> Empty!\n";
  else
    cout << "Actual >> Full!\n\n";
  
  //Insert Function Test and Length
  cout << "\nTesting Insert function in empty list\n";
  cout << "LinkedList >> ";
  for (int i = 0; i < 4; i++)
  {
    s.insert(i);
    cout << i << ", ";
  }
  cout << "\n\nTesting length() function\n";
  cout << "Expected >> 4 elements!\n";
  assert(s.length() == 4);
  cout << "Actual >> " << s.length() << " elements!\n";
  
  //First Function
  cout << "\nTesting First Function\n";
  cout << "Expected >> 3\n";
  s.first(l);
  cout << "Actual >> " << l << endl << endl;
  
  //Getnext Function
  cout << "Testing GetNext Function\n";
  cout << "List >> ";
  for (int i = 1; i < s.length(); i++)
  {
    s.getNext(l); cout << l << " ";
  }
  
  //Find()
  cout << "\n\nTesting Find() - Looking for 1 -\n";
  l = 1;
  cout << "Expected >> 1\n";
  assert(s.find(l) == 1);
  if (s.find(l) == 1)
    cout << "Actual >> 1\n";
  else
    cout << "Actual >> 1 cannot be found!\n\n";
  
  //Testing Retrieve Function
  cout << "\nTesting Retrieve() - Retrieve 1 in the list\n";
  cout << "Expected >> 1\n";
  assert(s.retrieve(l) == 1);
  cout << "Actual >> " << l << endl;
  
  //Getnext Function
  cout << "\nTesting GetNext Function\n";
  cout << "Expected >> 0\n";
  assert(s.getNext(l) == 1);
  cout << "Actual >> " << l << endl;
  
  //Testing Replace
  cout << "\nReplace 2 by 25 in the list\n";
  cout << "Expected >> 3 25 1 0\n";
  s.find(2); s.replace(25); s.first(l);
  cout << "Actual >> " << l << " ";
  for ( int i = 1; i < s.length(); i++)
  {
    s.getNext(l);
    cout << l << " ";
  }
  cout << endl;
  
  //Test Remove
  cout << "\nTesting Remove() - Removing 3 -\n";
  l = 3; s.remove(l);
  cout << "Expected >> 25 1 0\n";
  s.first(l);
  cout << "Actual >> " << l << " ";
  for (int i = 1; i < s.length(); i++)
  {
    s.getNext(l); cout << l << " ";
  }
  
  //Testing [] Operator
  cout << "\n\nTesting [] function. Geting the number in index \n";
  cout << "Expected >> 25\n";
  l = 0;
  cout << "Actual >> " << s[l] << endl;
  
  // Const object copy testing with assignment UPON declaration
  {
    const LinkedList<int> copy = s;
    cout << "\nConst object copy testing with assignment UPON declaration\n";
    cout << "\nTesting length()\n";
    cout << "Expected >> 3\n";
    cout << "Actaul >> " << copy.length() << endl;
    
    //isEmpty Function
    cout << "\nTesting isEmpty()\n";
    cout << "Expected >> List is Empty\n";
    assert(copy.isEmpty() == 0);
    if (copy.isEmpty() == 0)
      cout << "Actual >> List is Empty\n";
    else
      cout << "Actual >> List is NOT Empty\n";
    
  }
  // Const object copy testing with assignment After declaration
  {
    LinkedList<int> copy; copy= s;
    int extra[] = {100, 200, 300};
    
    //Insert Function Test and Length
    cout << "\nTesting Insert function in full list by adding extra insertion #\n";
    for (int i = 0; i < 3; i++)
      copy.insert(extra[i]);
    cout << "LinkedList >> 300 200 100 25 1 0\n";
    cout << "\nTesting length() function\n";
    cout << "Expected >> 6 elements!\n";
    assert(copy.length() == 6);
    cout << "Actual >> " << copy.length() << " elements!\n";
    
    //First Function
    cout << "\nTesting First Function\n";
    cout << "Expected >> 300\n";
    copy.first(l);
    cout << "Actual >> " << l << endl << endl;
    
    //Getnext Function
    cout << "Testing GetNext Function\n";
    cout << "List >> ";
    for (int i = 1; i < copy.length(); i++)
    {
      copy.getNext(l); cout << l << " ";
    }
    
    //Find()
    cout << "\n\nTesting Find() - Looking for 1 -\n";
    l = 1;
    cout << "Expected >> 1\n";
    assert(copy.find(l) == 1);
    if (copy.find(l) == 1)
      cout << "Actual >> 1\n";
    else
      cout << "Actual >> 1 cannot be found!\n\n";
    
    //Testing Retrieve Function
    cout << "\nTesting Retrieve() - Retrieve 1 in the list\n";
    cout << "Expected >> 1\n";
    assert(copy.retrieve(l) == 1);
    cout << "Actual >> " << l << endl;
    
    //Getnext Function
    cout << "\nTesting GetNext Function\n";
    cout << "Expected >> 0\n";
    assert(copy.getNext(l) == 1);
    cout << "Actual >> " << l << endl;
    
    //Testing Replace
    cout << "\nReplace 200 by 5 in the list\n";
    cout << "Expected >> 300 5 100 25 1 0\n";
    copy.find(200); copy.replace(5); copy.first(l);
    cout << "Actual >> " << l << " ";
    for ( int i = 1; i < copy.length(); i++)
    {
      copy.getNext(l);
      cout << l << " ";
    }
    cout << endl;
    
    //Test Remove
    cout << "\nTesting Remove() - Removing 100 -\n";
    l = 100; copy.remove(l);
    cout << "Expected >> 300 5 25 1 0\n";
    copy.first(l);
    cout << "Actual >> " << l << " ";
    for (int i = 1; i < copy.length(); i++)
    {
      copy.getNext(l); cout << l << " ";
    }
    
    //Testing [] Operator
    cout << "\n\nTesting [] function. Geting the number in index \n";
    cout << "Expected >> 25\n";
    l = 2;
    cout << "Actual >> " << copy[l] << endl;
    
    //MakeEmpty
    cout << "\nTesting makeEmpty()\n";
    cout << "Expected >> List has been emptied\n";
    copy.makeEmpty(); assert(copy.isEmpty() == 1);
    cout << "Actual >> List has been emptied\n";
  }
  
  //MakeEmpty
  cout << "\nTesting makeEmpty()\n";
  cout << "Expected >> List has been emptied\n";
  s.makeEmpty(); assert(s.isEmpty() == 1);
  cout << "Actual >> List has been emptied\n";
  
  
}