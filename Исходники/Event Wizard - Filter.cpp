	bool operator < (const SortedACE& b)
	{
		CString first = name;
		CString second = b.name;

		first.Remove('*');
		second.Remove('*');

		return first < second;
	}