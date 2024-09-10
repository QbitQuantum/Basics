char* number (int x)
{
		int i, j, k;
		char buff[16];
		static char string[12] = "           ";

		_itoa (x, buff, 10);
		k = strlen (buff);
		i = k + (k-1)/3;
		string[i--] = 0;
		j = 0;
		while (1)
		{
			string[i--] = buff[--k];
			if (i < 0) break;
			if (++j % 3 == 0) string[i--] = ',';
		}
		return (string);
}