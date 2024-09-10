Point pointFromString(string s)
{
	s = stripCommas(s);

	//Now, parse
	istringstream iss(s);
	Point pt;
	if(!(iss >> pt.x >> pt.y))
		pt.SetZero();
	return pt;
}