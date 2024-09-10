int main(int argc, const char *argv[])
{
	string str("hello world!");
	cout << "before: " << str << endl;

	string::iterator iter = str.begin();
	while (iter != str.end())
	{
		if (islower(*iter))
			*iter = toupper(*iter);
		++iter;
	}	
	cout << "after: " << str << endl;
	return 0;
}