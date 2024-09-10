// reads in a report from cin and 
// saves the wds in the linked list
// arg: nothing
// rets: true if all the words were read correctly
bool BogScorer::read_report()
{
  string status;
  string word;
  bool insert_worked;
  
  while (cin >> status)
  {
	status = ToUpper(status);
	cin >> word;
	word = ToUpper(word);
	insert_worked = insert(word,status);
	if (!insert_worked)
	{
	  return false;
	}
  }
  return true;
}