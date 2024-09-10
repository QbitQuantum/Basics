int main()
{
	LinkedList list;
	double input;	

	// Store values in list
	for (int i = 1; i <= 10 ; i++)
		list.add(i * 2.5);
	// Print list
	cout << "These a the contents of the list:\n";
	list.print();
	cout << "Removing \"5.0\" from list.\n";
	list.remove(5.0);
	cout << "These a the contents of the list:\n";
	list.print();
	cout << "Enter a value to remove from list: ";
	cin  >> input;
	list.remove(input);
	cout << "These a the contents of the list:\n";
	list.print();

	return 0;
}