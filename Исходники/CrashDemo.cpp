int _tmain(int argc, _TCHAR* argv[])
{
	printf("main start\r\n");
	_set_se_translator(trans_func);
	try
	{
		TestStackOverFlow();
	}
	catch(...)
	{
		printf("catch ...\n");
	}
	_alloca(2000);

	printf("main finish\r\n");
	return 0;
}