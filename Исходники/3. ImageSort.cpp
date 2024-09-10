int main()
{
	/*定义输入字符串，不超过1024，初始长度1025*/
	char str[1025];
	int i, j, len;
	char c;

	/*从控制台输入*/
	gets_s(str);
	len = strlen(str);

	/*根据ASCII码值，对字符串插入排序*/
	for (i = 1; i<len; ++i)
	{
		c = str[i];
		j = i - 1; 
		while (j >= 0 && str[j] > c)
		{		
			str[j + 1] = str[j];
			--j;
		}//while
		str[j + 1] = c;
	}//for
	printf("%s\n", str);
	system("pause");
}