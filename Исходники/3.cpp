int main()
{
	char string[STRING_LENGTH];
	gets_s(string, STRING_LENGTH * sizeof(char));
	printf("%d", lengthOfLongestSubstring(string));
	return 0;
}