int wxListCtrlEx::FindItemWithPrefix(const wxString& searchPrefix, int start)
{
	const int count = GetItemCount();
	for (int i = start; i < (count + start); i++)
	{
		int item = i % count;
		wxString namePrefix = GetItemText(item, 0).Left(searchPrefix.Length());
		if (!namePrefix.CmpNoCase(searchPrefix))
			return i % count;
	}
	return -1;
}