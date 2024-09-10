void test_delete()
{
    lasttotpoints = 20;

    // Insert some items
    List<int> l;
    for (int i = 0; i < 25000; i++)
    {
        l.insertAtHead(i);
    }

    // Delete the head a few times
    for (int i = 0; i < 50; i++)
        l.deleteHead();

	int length = l.length();
	if(length != 24950)
		int a = 1/0;

    cout << ".";
    lastpoints += 5;

    // Delete most of the items in the list
    while (l.length() > 50)
    {
        ListItem<int> *tmp = l.getHead();
        if (tmp != NULL)
            l.deleteElement(tmp->value);
        tmp = l.getTail();
        if (tmp != NULL)
            l.deleteElement(tmp->value);
	}
    lastpoints += 10;
    cout << ".";

    // Delete the tail till we're done
    int max = l.length();
    for (int i = 0; i < max; i++)
        l.deleteTail();
	cout << ".";
    lastpoints += 5;
}