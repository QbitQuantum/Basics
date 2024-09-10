int _tmain(int argc, _TCHAR* argv[])
{

	if(argc == 2){
		LONG lResult;
		lResult = tapiRequestMakeCall(argv[1], NULL, NULL, NULL);
		return (0 == lResult);
	}


	return 0;
}