void RunList(const char* filename) 
{
  List <int> List;
  ListItr <int> itr = List.zeroth();
  ifstream myfile;
  myfile.open(filename);
  char line1 [1000];
  char command;
  int value;
   
  myfile.getline(line1,1000);
   
  while(myfile >> command >> value)
  {
    //cout << command << value << endl;
    if (command == 'i')
    {
      List.insert(value,itr);
      //++itr;
    }
    else //command == 'd'
    {
      List.remove(value);
    }
  }


}