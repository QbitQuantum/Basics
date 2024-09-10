int _tmain(int argc, _TCHAR* argv[])
{
	int a=10;
	int b=4;
/*	cout << &a << "=" << a << endl << &b << "=" << b << endl;
	Swap(&a,&b,sizeof(int));
	cout << &a << "=" << a << endl << &b << "=" << b;

	*/
	//=====================================

	char* nodes[]={"A-","E#","Bb","D"};
	char* myfavnode = "E#";
	
	char* result = (char*)lsearch(nodes,myfavnode,4,sizeof(char*),xcomp);

	cout << result << endl;	
	system("pause");
	return 0;
}