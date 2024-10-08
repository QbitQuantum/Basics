int _jGetString(char *dest, char *start, int maxlen, GS_TYPE type)
{
	/*
	 * Returns 1 if OK; 0 if rejected or quit.
	 */

	int y;
	event e;
	int i;
	int startx;
   int key;

   curpos = 0;
	HideCursor();
	startx = QueryX();
	y = QueryY();

	lrects = malloc(maxlen * sizeof(rect));
	for (i = 0; i < maxlen; i++)
	{
		rect R;

		R.Xmin = startx + i * StringWidthX;
		R.Xmax = R.Xmin + StringWidthX - 1;
		R.Ymax = y;
		R.Ymin = R.Ymax - FontHeight + 1;
		lrects[i] = R;
	}


	tbuf = malloc(maxlen + 1);
	memset(tbuf, ' ', maxlen);
	tbuf[maxlen] = 0;

	i = 0;
	if (start)
	{
		for (i = 0; i < maxlen && start[i]; i++)
			tbuf[i] = start[i];
	}
	curpos = min(i, maxlen - 1);



	TextAlign(alignLeft, alignBottom);

	DrawString(tbuf);

	/* Now highlight somebody */
	InvertRect(&lrects[curpos]);


	while (1)
	{
      key = 0;

		KeyEvent(true, &e);
      if (e.ASCII && e.ASCII != 0xe0)
         key = e.ASCII;
      else if (e.ScanCode != 0xff)
         key = e.ScanCode << 8;

      



		if (key)
		{
			if (key == 0x0d || key == 0x1b)
				break;

			if (key == 0x08)	/* backspace */
            backspace(maxlen);
         else if (key == 0x15)      /* control U */
         {
            while(curpos)
               backspace(maxlen);
         }
			else
			{
				int acceptable = 0;

				if (type == GS_ANYTHING)
					acceptable = isprint(key);
				else if (type == GS_INTEGER)
					acceptable = isdigit(key) || key == '-';
				else if (type == GS_UNSIGNED)
					acceptable = isdigit(key);
				else if (type == GS_FLOAT)
					acceptable = isdigit(key) || key == '.' || key == '-' || key == 'E' || key == 'e';

				if (acceptable)
				{
					InvertRect(&lrects[curpos]);
					MoveTo(lrects[curpos].Xmin, lrects[curpos].Ymax);
					DrawChar(key);
					tbuf[curpos] = key;

					if (curpos < maxlen - 1)
						curpos++;

					InvertRect(&lrects[curpos]);
				}
			}

		}
		else
		{
			int button = (e.State & 0x700) >> 8;

			if (button == swRight)
			{
				key = 0x1b;
				break;
			}
		}
	}
	if (key != 0x1b)
		strcpy(dest, tbuf);

	ShowCursor();
	free(lrects);
	free(tbuf);
	return (key != 0x1b);
}