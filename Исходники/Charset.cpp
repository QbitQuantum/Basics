	int charset::draw(string numstr, alignment align, vector2d pos, float alpha)
	{
		char length = numstr.length();
		int shift = 0;
		int total = 0;

		switch (align)
		{
		case cha_center:
			for (char i = 0; i < length; i++)
			{
				total += getw(numstr[i]);
			}
			shift -= total / 2;
		case cha_left:
			for (char i = 0; i < length; i++)
			{
				shift += getw(numstr[i]);
				draw(numstr[i], pos + vector2d(shift, 0), alpha);
			}
			break;
		case cha_right:
			for (char i = length - 1; i >= 0; i--)
			{
				shift += getw(numstr[i]);
				draw(numstr[i], pos - vector2d(shift, 0), alpha);
			}
			break;
		}
		return shift;
	}