int main(int argc, char** varg)
{
  if(argc < 4)//this is how to use this
  {
    cerr << "usage: cmd file1 file2 output" << endl;
    return 1;
  }

  //these are for holding each files occurances of strings, or lack thereof
  set<WORD> file1, file2;
  
  //Java like Scanner object
  Scanner scan;
  //open the file given as argument 1
  scan.openFile(varg[1]);
  //to the first file 'file1' we will add each string that is in there
  //for the first occurance we set count at 1, and increment as needed
  //to the second file 'file2' we will add each string from 'file1'
  //and set the count to 0
  while(scan.hasMoreData())
  {
    ScanLine line;
    line.openString(scan.nextLine());
    while(line.hasMoreData())
    {
      string nxt_token = line.next();
      nxt_token = Utils::trimBlanks(nxt_token);

      //add elements to 'file2' once with count 0
      if(file2.count(nxt_token) == 0)
      {
	WORD f_two;
	f_two.token = nxt_token;
	f_two.count = 0;
        file2.insert(f_two);
      }
      //add first occurance to file1 with count 1
      if(file1.count(nxt_token) == 0)
      {
	WORD f_one;
	f_one.token = nxt_token;
	f_one.count = 1;
        file1.insert(f_one);
      }
      else
      {
	//replace the word with a word of equal token and +1 count
	set<WORD>::iterator it = file1.find(WORD(nxt_token));
	int ct = it->count;
	ct++;
	file1.erase(it);
	WORD replace;
	replace.token = nxt_token;
	replace.count = ct;
	file1.insert(replace);
      }
    }
  }
  scan.close();//close file1

  cout << "++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

  scan.openFile(varg[2]);//open file2

  //to the second file 'file2' we will add each word we find, or
  //increment as needed if it occurred in the first file
  //if a string occurs in 'file2' that doesn't exist in 'file1'
  //we will add any token to 'file1' list from 'file2' list and set count to 0
  while(scan.hasMoreData())
  {
    ScanLine line;
    line.openString(scan.nextLine());
    while(line.hasMoreData())
    {
      string nxt_token = line.next();
      nxt_token = Utils::trimBlanks(nxt_token);
      
      //if the word doesn't already exist in 'file1' add it with count 0
      if(file1.count(nxt_token) == 0)
      {
	WORD f_two;
	f_two.token = nxt_token;
	f_two.count = 0;
        file1.insert(f_two);
      }
      //add the first occurance of a word to 'file2' with count 1
      if(file2.count(nxt_token) == 0)
      {
	WORD f_one;
	f_one.token = nxt_token;
	f_one.count = 1;
        file2.insert(f_one);
      }
      else
      {
	//replace the word with a word of equal token and +1 count	
	set<WORD>::iterator it = file2.find(WORD(nxt_token));
	int ct = it->count;
	ct++;
	file2.erase(it);
	WORD replace;
	replace.token = nxt_token;
	replace.count = ct;
	file2.insert(replace);
      }
    }
  }
  scan.close();

  ofstream outStream;
  Utils::FileOpen(outStream, varg[3]);//open the output file
  //write to it...
  outStream << Utils::Format(compare(file1, file2), 2, 6) << endl;
  Utils::FileClose(outStream);//close it
}