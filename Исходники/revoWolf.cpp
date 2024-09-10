void Welcome()
{
	system("cls");
	char s[1500];
	LoadStringA(NULL, (int)MAKEINTRESOURCE(IDS_STRING1), s, sizeof(s)); 
	printf("%s\n",s);
}