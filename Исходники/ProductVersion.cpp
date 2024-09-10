ProductVersions::ProductVersions(String s)
{
	// strip eventually contained \r characters
	int i;
	while( (i = s.Find('\r')) >= 0)
		s.Remove(i);
	
	// split string on newlines
	Vector<String>sv = Split(s, '\n');
	
	// read all versions from vector
	for(i = 0; i < sv.GetCount(); i++)
		Add(sv[i]);
}