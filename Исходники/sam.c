static void HexStrToBin(char* str, BYTE* bin, int length)
{
	int i;
	CharUpperBuffA(str, length * 2);

	for (i = 0; i < length; i++)
	{
		bin[i] = 0;

		if ((str[i * 2] >= '0') && (str[i * 2] <= '9'))
			bin[i] |= (str[i * 2] - '0') << 4;

		if ((str[i * 2] >= 'A') && (str[i * 2] <= 'F'))
			bin[i] |= (str[i * 2] - 'A' + 10) << 4;

		if ((str[i * 2 + 1] >= '0') && (str[i * 2 + 1] <= '9'))
			bin[i] |= (str[i * 2 + 1] - '0');

		if ((str[i * 2 + 1] >= 'A') && (str[i * 2 + 1] <= 'F'))
			bin[i] |= (str[i * 2 + 1] - 'A' + 10);
	}
}