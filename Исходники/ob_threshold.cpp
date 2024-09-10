void draw_meter(THRESHOLDOBJ * st)
{
	PAINTSTRUCT ps;
	HDC hdc;
	char szdata[20];
	RECT rect;
	int  act,width,mid,height,bottom,y1,y2;
	HBRUSH actbrush,bkbrush;
	HPEN bkpen;
	float min, max;

	
	GetClientRect(st->displayWnd, &rect);
	//width=rect.right>>1;
	width=(int)((float)rect.right/200.0f*st->barsize);
	mid=rect.right>>1;
    	
	min=st->in_ports[0].in_min;
	max=st->in_ports[0].in_max;

	hdc = BeginPaint (st->displayWnd, &ps);
	bottom=rect.bottom-10;
	height=(bottom-rect.top-20);

    act=bottom-(int)(size_value(min,max,st->gained_value,0.0f,(float)height,0));
	y1 =bottom-(int)(size_value(min,max,(float)st->from_input,0.0f,(float)height,0));
	y2 =bottom-(int)(size_value(min,max,(float)st->to_input,0.0f,(float)height,0));

	if (act>bottom) act=bottom;
	if (act<bottom-height) act=bottom-height;

	actbrush=CreateSolidBrush(st->color);
    bkbrush=CreateSolidBrush(st->bkcolor);
	bkpen =CreatePen (PS_SOLID,1,st->bkcolor);
	if (st->redraw) FillRect(hdc, &rect,bkbrush);
    
   	SelectObject (hdc, bkpen);		
   	SelectObject (hdc, bkbrush);
	if (st->bigadapt)
	{
		Rectangle(hdc,15,st->old_y1,50,st->old_y1+15);
		MoveToEx(hdc,5, st->old_y1,NULL);	
		LineTo(hdc,rect.right, st->old_y1);
	}

	if (st->smalladapt)
	{
		Rectangle(hdc,15,st->old_y2,50,st->old_y2+15);
		MoveToEx(hdc,5, st->old_y2,NULL);	
		LineTo(hdc,rect.right, st->old_y2);
	}

	if ((st->last_value<act)&&(!st->redraw)) 
	{
			SelectObject (hdc, bkbrush);		
			Rectangle(hdc,mid-width,st->last_value,mid+width,act);
	}
	else
	{
			SelectObject (hdc, actbrush);
			Rectangle(hdc,mid-width,bottom,mid+width,act);
	}

	if ((st->fontsize>0))
	{
		RECT txtpos;int x;
		SelectObject(hdc, st->font);
		SetBkMode(hdc, OPAQUE);
		SetBkColor(hdc, st->fontbkcolor);
		SetTextColor(hdc,st->fontcolor);

		//wsprintf(szdata, "%d   ",(int)(st->gained_value+0.5f));
		//ExtTextOut( hdc, rect.right-40,10, 0, &rect,szdata, strlen(szdata), NULL ) ;

		txtpos.left=5;txtpos.right=50;
		txtpos.top=0;txtpos.bottom=0;
		sprintf(szdata, " %.2f ",st->from_input);
		DrawText(hdc, szdata, -1, &txtpos, DT_CALCRECT);
		x=txtpos.bottom;
		txtpos.top=y1-x;txtpos.bottom=txtpos.top+x;
		DrawText(hdc, szdata, -1, &txtpos, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	

		txtpos.left=5;txtpos.right=50;
		txtpos.top=0;txtpos.bottom=0;
		sprintf(szdata, " %.2f ",st->to_input);
		DrawText(hdc, szdata, -1, &txtpos, DT_CALCRECT);
		txtpos.top=y2+1;txtpos.bottom+=y2+1;
		DrawText(hdc, szdata, -1, &txtpos, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		
	}
	
	SelectObject (hdc, DRAW.pen_ltblue);		
	MoveToEx(hdc,5, y1,NULL);	
	LineTo(hdc,rect.right, y1);
	st->old_y1=y1;

	MoveToEx(hdc,5, y2,NULL);	
	LineTo(hdc,rect.right, y2);
	st->old_y2=y2;

	DeleteObject(actbrush);
	DeleteObject(bkbrush);
	DeleteObject(bkpen);
	st->last_value=act;
	st->redraw=0;
	EndPaint( st->displayWnd, &ps );
}