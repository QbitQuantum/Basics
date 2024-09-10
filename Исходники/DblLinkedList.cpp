//-------------------  DblLinkedList::DeepCopy() -------------------
// Deep copy source to this object
void DblLinkedList::DeepCopy(DblLinkedList &source)
{
	Node *tempNode;
	assert(tempNode = new(nothrow) Node());
	tempNode = source.current;
	//Delete the old list
	this->~DblLinkedList();
	//Rewind the source list
	source.Rewind();
	//Copy that linked list.
	while (source.current != 0)
	{
		InsertItem(source.CurrentItem());
		source.Forward();
	}
	source.current = tempNode;
	current = tempNode;
	tempNode = 0;
	delete tempNode;
}