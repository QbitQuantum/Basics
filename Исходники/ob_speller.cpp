void draw_speller(SPELLEROBJ * st)
{
	PAINTSTRUCT ps;
	HDC hdc;
	char szdata[400];
	RECT rect;
	HBRUSH actbrush;
	int ballx,bally,i;

	
	GetClientRect(st->displayWnd, &rect);
	hdc = BeginPaint (st->displayWnd, &ps);


	//ballx=(int) ((rect.right/100.0f)*st->xpos);
	//bally=(int) ((rect.bottom/100.0f)*st->ypos);

	ballx=(int)st->xpos;
	bally=(int)st->ypos;
	
	actbrush=CreateSolidBrush(RGB(180,0,0));
    
   	SelectObject (hdc, DRAW.pen_white);		
   	SelectObject (hdc, DRAW.brush_ltgreen);
	Rectangle(hdc,0,0,rect.right,rect.bottom);

    SelectObject(hdc, DRAW.mediumFont);
	SetTextColor(hdc,RGB(255,0,0));

	SelectObject (hdc, DRAW.pen_red);	
	
    sprintf(szdata, "->  %s",st->word);  // st->selstart,st->selend,st->suggestions,
	DrawText(hdc, szdata, -1, &rect, DT_CENTER | DT_WORDBREAK );

	// sprintf(szdata, "PAD: %d SEL: %d",st->paddle,st->select); 
    // ExtTextOut( hdc, 10,10, 0, &rect,szdata, strlen(szdata), NULL ) ;

	for (i=0;i<st->selections;i++)
	{
		if ((st->dict[st->selstart+i].type==EXTEND_CHARACTERS) 
			||(st->dict[st->selstart+i].type==FINAL_CHARACTERS)
			||(st->dict[st->selstart+i].type==DICTIONARY))
			strcpy(szdata, st->dict[st->selstart+i].tag);
		else strcpy(szdata,"inv");
		
		if (i==st->select) { SetTextColor(hdc,RGB(255,0,0)); SetBkColor(hdc,RGB(255,255,0)); }
		else { SetTextColor(hdc,RGB(255,0,0)); SetBkColor(hdc,RGB(30,30,30)); }

		ExtTextOut( hdc, 100,80+i*30, 0, &rect,szdata, strlen(szdata), NULL ) ; 

		/*
		switch (i)
		{
			case 0:	ExtTextOut( hdc, 150,50, 0, &rect,szdata, strlen(szdata), NULL ) ; break;
			case 1:	ExtTextOut( hdc, 250,100, 0, &rect,szdata, strlen(szdata), NULL ) ; break;
			case 2:	ExtTextOut( hdc, 50,100, 0, &rect,szdata, strlen(szdata), NULL ) ; break;
			case 3:	ExtTextOut( hdc, 150,150, 0, &rect,szdata, strlen(szdata), NULL ) ; break;
		}
		*/
	}

	if (st->dictfile[0])
	{
		char fn[256];

		SelectObject(hdc, DRAW.scaleFont);
		SetTextColor(hdc,RGB(255,255,255));
		SetBkColor(hdc,RGB(0,0,50));
		reduce_filepath(fn,st->dictfile);
		sprintf(szdata,"Wörterbuch: %s, %d words.",fn, st->wordcount);
		ExtTextOut( hdc, 360, 70, 0, &rect,szdata, strlen(szdata), NULL );

		//ExtTextOut( hdc, 360, 80, 0, &rect,st->fn, strlen(st->fn), NULL );

	}
	if (st->suggestions)
	{
		SelectObject(hdc, st->sugfont);
		SetTextColor(hdc,RGB(255,255,0));
		SetBkColor(hdc,RGB(40,40,0));

		for (i=0;(i<st->suggestions);i++)
		{
			strcpy(szdata, st->dict[st->suggest[i]].tag);
			ExtTextOut( hdc, 360,100+i*20, 0, &rect,szdata, strlen(szdata), NULL );
		}
		if (i==MAX_SUGGEST)
		{
			strcpy(szdata, "(...)");
			ExtTextOut( hdc, 360,100+i*20, 0, &rect,szdata, strlen(szdata), NULL );
		}

	}
   	SelectObject (hdc, DRAW.brush_orange);
//	Rectangle(hdc,ballx,bally,ballx+20,bally+20);

   
	DeleteObject(actbrush);
	EndPaint( st->displayWnd, &ps );
}