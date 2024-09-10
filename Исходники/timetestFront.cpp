//template <class Object>
void RunList(ifstream& stream){
   char iord;
   int number;
   
   //string dummy;
   //getline(stream, dummy);
  
   char dummy[256];
   stream.getline(dummy, 256); 
   
   List<int> list;
   ListItr<int> listItr = list.zeroth();
   
   while(stream >> iord >> number){
      if(iord == 'i'){
      list.insert(number, listItr);
      listItr.advance();
      //cout << "Inserted " << number << endl;
      }
      
      else /*if(iord == 'd')*/{
      list.remove(number);
      //cout << "Deleted " << number << endl;
      }
   }
   
   stream.clear();
   stream.seekg(0, ios::beg); 
}