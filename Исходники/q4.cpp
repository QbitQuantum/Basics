void removeEntry(HashTable<int> &HT, int x)			//remove entry
{
	try
	{
		HT.remove(x);								//remove key if possible
	}
	catch (NonexistentEntry& err)					//show error if not
	{
		cout << "Exception: " << err.getMessage()
			<< endl << endl;						
	}
}