int main(void)
{
	const char *hay = "Do Re";
	const char *needle = "Re";
	char* result = StrStr(hay, needle);
	printf("%d\n", *result);
}