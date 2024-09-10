/************************************************************************\
通过键盘输入100以内正整数的加、减运算式，请编写一个程序输出运算结果字符串。
输入字符串的格式为：“操作数1 运算符 操作数2”，“操作数”与“运算符”之间以一个空格隔开。
补充说明：
1、操作数为正整数，不需要考虑计算结果溢出的情况。
2、若输入算式格式错误，输出结果为“0”。
【输入】 pInputStr：  输入字符串
lInputLen：  输入字符串长度
【输出】 pOutputStr： 输出字符串，空间已经开辟好，与输入字符串等长；
【注意】只需要完成该函数功能算法，中间不需要有任何IO的输入输出
示例
输入：“4 + 7”  输出：“11”
输入：“4 - 7”  输出：“-3”
输入：“9 ++ 7”  输出：“0” 注：格式错误
\************************************************************************/
void CharIntegerOperation(const char *pInputStr, long lInputLen, char *pOutputStr)
{
	int i, am(0);
	for (i = 0; i<lInputLen; i++)
	{
		switch (pInputStr[i])
		{
		case '+': am = 1;
			break;
		case '-': am = 2;
			break;
		}
		if (am != 0) break;
	}
	if (pInputStr[i - 1] != ' ' && pInputStr[i + 1] != ' ')
	{
		pOutputStr[0] = '0';
		pOutputStr[1] = '\0';
		return;
	}
	int mid(i), a1(0), a2, b1, b2(lInputLen - 1);
	for (i = 0; i <= mid; i++)
	{
		if (pInputStr[i] == ' '){
			a2 = i - 1;
			break;
		}
	}
	for (i = mid + 1; i<lInputLen; i++)
	{
		if (pInputStr[i] != ' '){
			b1 = i;
			break;
		}
	}

	int n1(0), n2(0);
	for (i = a1; i <= a2; i++)
	{
		if (pInputStr[i] >= '0' && pInputStr[i] <= '9')
			n1 = n1 * 10 + pInputStr[i] - '0';
		else{
			pOutputStr[0] = '0';
			pOutputStr[1] = '\0';
			return;
		}
	}
	for (i = b1; i <= b2; i++)
	{
		if (pInputStr[i] >= '0' && pInputStr[i] <= '9')
			n2 = n2 * 10 + pInputStr[i] - '0';
		else{
			pOutputStr[0] = '0';
			pOutputStr[1] = '\0';
			return;
		}
	}

	int res(0);
	switch (am)
	{
	case 1: res = n1 + n2;
		break;
	case 2: res = n1 - n2;
		break;
	}
	char buffer[20];
	_itoa_s(res, buffer, 10);
	strcpy_s(pOutputStr,10, buffer);
}