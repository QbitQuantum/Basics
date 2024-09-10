int _tmain(int argc, _TCHAR* argv[])
{
	HMODULE lib = LoadLibrary(L"dlllib.dll");
	if (lib == 0){
		printf("Error load library\n");
		system("pause");
		return -1;
	}
	AddFunction Add = (AddFunction)GetProcAddress(lib, "Add");
	AddFunction Sub = (AddFunction)GetProcAddress(lib, "Sub");
	AddFunction Mul = (AddFunction)GetProcAddress(lib, "Mul");
	DivFunction Div = (DivFunction)GetProcAddress(lib, "Div");
	int a = 6;
	int b = 2;
	printf("a=%i b=%i\n", a,b);
	printf("Add %i\n", Add(a, b));
	printf("Sub %i\n", Sub(a, b));
	printf("Mul %i\n", Mul(a, b));
	printf("Div %f\n", Div(a, b));
	FreeLibrary(lib);
	_wsystem(L"pause");
	return 0;
}