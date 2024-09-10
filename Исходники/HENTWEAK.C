void henon_tweaker(void)
{
	int i;
	char chosen_file[128];
	rect R;
	rect tR;
	int last_time;
	int keyword;
	int current_item;
	int centerx, centery;
	int height, width;
	int row;
	static int lefters[] = {
		1, 2, 0,
		4, 3,
		5,
		12, 6, 7, 8, 9, 10, 11,
		15, 13, 14
	};

	static int righters[] = {
		1, 2, 0,
		4, 3,
		5,
		7, 8, 9, 10, 11, 12, 6,
		14, 15, 13
	};

	static int uppers[] = {
		13, 14, 15,
		0, 2,
		3,
		5, 5, 5, 5, 5, 5, 5,
		6, 8, 11
	};

	static int downers[] = {
		3, 3, 4,
		5, 5,
		8,
		13, 13, 13, 14, 14, 15, 15,
		0, 1, 2
	};

	our_flocktype = flocktype;
	our_tracetype = tracetype;
	henon_slider.value = fha;


	height = 2 + FontHeight + 8 +
		2 * (3 * FontHeight / 2) +
		slider_height(&henon_slider) + 4
		+ 2 * FontHeight + 4;

	width = 2 * sR.Xmax / 3;

	HideCursor();
	PushCursorPosition();
	BasicCenteredBox(&tR, width, height, LIGHTGRAY, "Hnon Tweaks", BLACK);
	Centers(&tR, &centerx, &centery);
	PushMouseRectLimit(&tR);
	items = 0;

	R.Xmin = tR.Xmin + 4 + StringWidth("Flock Size: ") + 4;
	R.Xmax = tR.Xmax - 4;
	R.Ymin = row = tR.Ymin + FontHeight + 8;
	R.Ymax = R.Ymin + FontHeight + 4;
	JString("Flock size: ", R.Xmin - 2, R.Ymin + 2, BLACK, LIGHTGRAY, alignRight, alignTop);
	CreateRadioPanel(&R, SML, flocktypeR, 3, our_flocktype);
	for (i = 0; i < 3; i++)
		bR[items++] = &flocktypeR[i];


	OffsetRect(&R, 0, 3 * FontHeight / 2);
	R.Xmin = centerx;
	row = R.Ymin;
	JString("Trace Type: ", R.Xmin - 2, R.Ymin + 2, BLACK, LIGHTGRAY, alignRight, alignTop);
	CreateRadioPanel(&R, PL, tracetypeR, 2, our_tracetype);
	for (i = 0; i < 2; i++)
		bR[items++] = &tracetypeR[i];

	row += 3 * FontHeight / 2;
	create_slider(&henon_slider, &tR, 4, row - tR.Ymin);
	bR[items++] = &henon_slider.bR;
	bR[items++] = &henon_slider.TB.nR;
	for (i = 0; i < 6; i++)
		bR[items++] = &henon_slider.zR[i];

	if (!fancyflag)
	{
		R = henon_slider.tR;
		InsetRect(&R, 1, 1);
		GrayOut(&R);
	}

	row = henon_slider.tR.Ymax + FontHeight;
	R.Xmin = tR.Xmin + 4;
	R.Xmax = tR.Xmax - 4;
	R.Ymin = row;
	R.Ymax = row + FontHeight + 4;

	CreateRadioPanel(&R, standard_button_texts, doitR, 3, -1);
	for (i = 0; i < 3; i++)
		bR[items++] = &doitR[i];

	current_item = items - 1;
	push(current_item, true);
	move_to_corner(bR[current_item]);

	ShowCursor();
	while (1)
	{
		event e;
		int n = KeyEvent(false, &e);
		int button = (e.State & 0x700) >> 8;
		int X = e.CursorX;
		int Y = e.CursorY;
		int last_item = current_item;
		slider *current_slider = NULL;

		if (fancyflag && XYInRect(X, Y, &henon_slider.tR))
			current_slider = &henon_slider;
		keyword = 0;
		if (n)
			last_time = e.Time;
		else
		{
			if (e.Time - last_time > 5)
			{
				if (button)
					n = 1;
				else
					last_time = e.Time;
			}
		}
		if (n)
		{
			keyword = ShiftArrows(&e);
			if (button == swRight)
				keyword = 0x1b;

			if (!keyword)
			{
				if (e.ASCII && e.ASCII != 0xe0)
					keyword = e.ASCII;
				else
					keyword = e.ScanCode << 8;
			}
			if (button == swLeft)
			{
				keyword = 0x0d;
				if (current_slider)
				{
					if (XYInRect(X, Y, &current_slider->bR))
					{
						PushMouseRectLimit(&current_slider->sR);
						while (button == swLeft)
						{
							reposition_slider_X(current_slider, X, false);
							KeyEvent(false, &e);
							button = (e.State & 0x700) >> 8;
							X = e.CursorX;
							Y = e.CursorY;
						}
						PopMouseRect();
						keyword = 0;
					}
					else if (XYInRect(X, Y, &current_slider->sR))
					{
						reposition_slider_X(current_slider, X, false);
						keyword = 0;
					}
				}
			}