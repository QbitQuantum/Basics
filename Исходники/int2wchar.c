int main()
{
	_wsetlocale(LC_ALL, L"");
	int myIntValue = 20;
	wchar_t m_reportFileName[256];
	wchar_t a = L'中';
	swprintf_s(m_reportFileName, 256, L"%wc,%d", a, myIntValue);
	printf("%d\n", wcslen(m_reportFileName));
	wprintf(L"%s\n", m_reportFileName);
	getchar();
}