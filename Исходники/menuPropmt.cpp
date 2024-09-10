void Menu::Delete(BinarySearchTree<DataRecord>& b)
{
	//Asks user for which record to delete.

	//pass that key to the hash function to see if data exists.
	DataRecord LookingFor(5, 14.8);
	DataRecord Temp;
	if (b.getEntry(LookingFor, Temp))
	{
		DataStack.push(Temp);
		b.remove(Temp);
		return;
	}
	//can't be found
	cout << "cant be found\n";
	return;

}