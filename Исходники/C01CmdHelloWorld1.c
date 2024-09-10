int main() {
	_wsetlocale(LC_ALL, L"");
	wchar_t* a = L"hello";
	wchar_t* b = L"您好";
	printf("%ls size is %d\n", a, wcslen(a));
	printf("%ls size is %d\n", b, wcslen(b));
	printf("size is %d\n", sizeof(a[0]));
	getchar();
	return 0;
}