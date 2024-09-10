	int BinaryBoard::QuickSplitVertically(Rect originRect, Rect output[2]) const
	{
		Rect tOrigin = QuickCrop(originRect);

		Border b = (tOrigin / blockSize).ToOuterBorder();
		int splitAt = -1;

		for (int y = b.bottom - 2; y > b.top; --y)
		{
			bool blank = true;
			for (int x = b.left; x < b.right; ++x)
			{
				if (!IsBlank(x, y))
				{
					blank = false;
					break;
				}
			}

			if (blank)
			{
				splitAt = y * blockSize;
				break;
			}
		}

		if (splitAt == -1)
		{
			output[0] = tOrigin;
			return 1;
		}

		b = tOrigin.ToOuterBorder();
		b.top = splitAt;
		output[0] = QuickCrop(Rect::FromOuterBorder(b));

		b = tOrigin.ToOuterBorder();
		b.bottom = splitAt;
		output[1] = QuickCrop(Rect::FromOuterBorder(b));

		return 2;
	}