int main()
{
	setlocale(LC_ALL, "rus");

	Server* tcp = new Server();

	try
	{
		tcp->Startup();
		tcp->InitSocket();
		tcp->Bind(PORT);
		while (true) tcp->Listen(10);
	}
	catch (string s)
	{
		cout << s;

		tcp->CloseConnection();
	}

	return 0;
}