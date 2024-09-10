extern int GW_ask_tail_number_string(const char *szInput, char *sTailNum)
{
	std::string	strTailNum;
	int nLength = (int)(strlen(szInput));
	for (int i=nLength-1; i>=0; i--)
	{
		if (szInput[i] >= 0x30 && szInput[i] <= 0x39)
			strTailNum += szInput[i];
		else
			break;
	}
	strcpy(sTailNum, strrev((char*)(strTailNum.c_str())));
	return (int)(strlen(sTailNum));
}