wstring ToLower(wstring in)
{
	in = w_trim(in);
	int (*pf)(int) = tolower;
	transform(in.begin(), in.end(), in.begin(), pf);
	return in;
}