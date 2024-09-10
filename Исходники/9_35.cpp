int main(int argc, const char *argv[])
{
	string str("*****@*****.**");
	cout << "before: " << str << endl;
	
	string::iterator iter = str.begin();
	while (iter != str.end())
	{
		if (isupper(*iter))
			iter = str.erase(iter);
		else
			++iter;
	}
	cout << "after: " << str << endl;

	return 0;
}