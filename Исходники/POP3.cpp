bool Pop3::GetListItems(ValueMap& list, dword type1, dword type2)
{
	StringStream s(data);
	while(!s.IsEof()) {
		String line = s.GetLine();
		Vector<String> s = Split(line, ' ');
		if(s.GetCount() < 2)
			return false;
		list.Add(Scan(type1, s[0]), Scan(type2, s[1]));
	}
	return true;	
}