	void EditListControl::clear()
	{
		SendMessageW(getWindow(), LVM_DELETEALLITEMS, 0, 0);
	}