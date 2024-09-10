void main(void)
{
	char ConsoleBuf[MAX_BUF2] = { 0, };

	int count;
	PutS("> Console Calculator\n");
	PutS("> Available Command :  print [a]|[z] , quit , <Enter>\n> \n");

	while (1)
	{
		PutS("> ");		// Prompt
		count = GetS(ConsoleBuf);

		if (!ParseBuf(ConsoleBuf))	// 입력이 NULL 이면 멈춘다.
		{
			break;
		}
	}
	PutS(ConsoleBuf);	
	PutInt(count);
	return;
}