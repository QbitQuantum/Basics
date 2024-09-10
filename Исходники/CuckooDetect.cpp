void portScanner()
{
	char buf[10000];
	FILE *p = _popen("netstat -an", "r");
	string s;
	for (size_t count; (count = fread(buf, 1, sizeof(buf), p));)
	{
		s += string(buf, buf + count);
	}
	if (s.find(":2042") != std::string::npos)
	{
		createAndWriteFile("portnumber.txt");
		printf("Cuckoo Sandbox is detected. Port number 2042. \n");
	}
	_pclose(p);
}