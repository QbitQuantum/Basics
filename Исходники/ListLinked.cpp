List<DataType>& List<DataType>::operator=(const List& other)
{
	
	if (!isEmpty())
	{
		clear();
	}

	List<DataType> temp = other;
	temp.gotoPrior();
	ListNode previous = NULL;
	previous.dataItem = temp.getCursor();
	temp.gotoBeginning();
	while (temp.cursor.next != NULL)
	{
		insert(temp.cursor.dataItem);
		temp.gotoNext();
	}
	gotoBeginning();
	while (getCursor() != previous.dataItem)
	{
		gotoNext();
	}

	return this;
	
	/*
	clear();
	ListNode* temp = other.head;
	while (temp != NULL)
	{
		insert(temp->dataItem);
		temp = temp->next;
	}
	cursor = temp;
	gotoBeginning();
	head = cursor;
	return this;
	*/
}