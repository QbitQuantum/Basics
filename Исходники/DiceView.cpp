void CDiceView::OnDraw(CDC* pDC)
{
	CDiceDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	//initialize
	CRect viewRect;
	CWnd::GetClientRect(&viewRect);
	
	cellx = viewRect.right/(6+1);
	celly = viewRect.bottom/(5+1);
	radius = celly/3;


	//draw vs
	CRect vsRect;
	vsRect.left = viewRect.right/2 - radius*2;
	vsRect.top = 0;
	vsRect.right = viewRect.right/2 + radius*2;
	vsRect.bottom = celly;
	pDC->DrawText("VS", vsRect, DT_VCENTER|DT_CENTER|DT_SINGLELINE);

	//draw fight info
	for(int j = 0; j<2; j++)
	{
		if(ftInfo[j].country < 0)
			break;
		ftInfo[j].fightRect.left = (j+3)*cellx;
		ftInfo[j].fightRect.top = celly/4;
		ftInfo[j].fightRect.right = (j+3)*cellx + radius;
		ftInfo[j].fightRect.bottom = celly/4 + radius;

		CBrush brush;

		switch(ftInfo[j].country)
		{
			case 0:
				brush.CreateSolidBrush(RGB(128,128,128));
				pDC->SetBkColor(RGB(128,128,128));
				break;
            case 1:
				brush.CreateSolidBrush(RGB(255,0,0));
				pDC->SetBkColor(RGB(255,0,0));
				break;
			case 2:
				brush.CreateSolidBrush(RGB(0,255,0));
				pDC->SetBkColor(RGB(0,255,0));
				break;
			case 3:
				brush.CreateSolidBrush(RGB(0,0,255));
				pDC->SetBkColor(RGB(0,0,255));
				break;
			case 4:
				brush.CreateSolidBrush(RGB(255,255,0));
				pDC->SetBkColor(RGB(255,255,0));
				break;
			case 5:
				brush.CreateSolidBrush(RGB(255,0,255));
				pDC->SetBkColor(RGB(255,0,255));
				break;
			case 6:
				brush.CreateSolidBrush(RGB(0,255,255));
				pDC->SetBkColor(RGB(0,255,255));
				break;
			case 7:
				brush.CreateSolidBrush(RGB(0,128,128));
				pDC->SetBkColor(RGB(0,128,128));
				break;
			default:break;

		}

		pDC->FillRect(ftInfo[j].fightRect,&brush);

		char text[1] = {0};
		pDC->SetTextColor(RGB(255,255,255));
		itoa(ftInfo[j].fightPts,text,10);

		pDC->DrawText(text,ftInfo[j].fightRect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
	}

	//draw button
	buttonRect.left = viewRect.right-100;
	buttonRect.top = viewRect.bottom-50;
	buttonRect.right = viewRect.right-5;
	buttonRect.bottom = viewRect.bottom-5;
	
	CBrush brush;	
	brush.CreateSolidBrush(RGB(160,160,160));
	pDC->FillRect(buttonRect,&brush);
	pDC->SetBkColor(RGB(160,160,160));

	if(btnClicked)
		pDC->DrawEdge(buttonRect,EDGE_SUNKEN,BF_BOTTOMRIGHT | BF_TOPLEFT); 
	else
		pDC->DrawEdge(buttonRect,EDGE_RAISED,BF_BOTTOMRIGHT | BF_TOPLEFT);

	pDC->DrawText("End Turn",buttonRect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
	
	//draw maxConnection
	for(int i = 0; i<8; i++)
	{
		CBrush brush;
		CRect maxConnectionRect;
		maxConnectionRect.left = (i+1)*cellx/1.5 + cellx/2.25 - radius/1.5;
		maxConnectionRect.top =  (5+0.75)*celly - radius/1.5; 
		maxConnectionRect.right = (i+1)*cellx/1.5 +cellx/2.25 + radius/1.5;
		maxConnectionRect.bottom = (5+0.75)*celly + radius/1.5;

		players[i].maxConnectionRect = CRect(maxConnectionRect.left - 5, maxConnectionRect.top - 5, 
			maxConnectionRect.right +5, maxConnectionRect.bottom+5);
	
		switch(i)
		{
			case 0:
				brush.CreateSolidBrush(RGB(128,128,128));
				pDC->SetBkColor(RGB(128,128,128));
				break;
            case 1:
				brush.CreateSolidBrush(RGB(255,0,0));
				pDC->SetBkColor(RGB(255,0,0));
				break;
			case 2:
				brush.CreateSolidBrush(RGB(0,255,0));
				pDC->SetBkColor(RGB(0,255,0));
				break;
			case 3:
				brush.CreateSolidBrush(RGB(0,0,255));
				pDC->SetBkColor(RGB(0,0,255));
				break;
			case 4:
				brush.CreateSolidBrush(RGB(255,255,0));
				pDC->SetBkColor(RGB(255,255,0));
				break;
			case 5:
				brush.CreateSolidBrush(RGB(255,0,255));
				pDC->SetBkColor(RGB(255,0,255));
				break;
			case 6:
				brush.CreateSolidBrush(RGB(0,255,255));
				pDC->SetBkColor(RGB(0,255,255));
				break;
			case 7:
				brush.CreateSolidBrush(RGB(0,128,128));
				pDC->SetBkColor(RGB(0,128,128));
				break;
			default:break;

		}

		pDC->FillRect(maxConnectionRect,&brush);

		char text[1] = {0};
		pDC->SetTextColor(RGB(255,255,255));
		itoa(players[i].maxConnection,text,10);
		pDC->DrawText(text,maxConnectionRect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
		pDC->DrawEdge(maxConnectionRect,EDGE_RAISED,BF_BOTTOMRIGHT | BF_TOPLEFT);

		if(players[i].isMyTurn)
		{
			CPen pen,*oldPen;
			oldPen = pDC->GetCurrentPen();
			pen.CreatePen(PS_SOLID,4,RGB(0,0,0));
			pDC->SelectObject(pen);

			
			pDC->MoveTo(maxConnectionRect.left, maxConnectionRect.top);
			pDC->LineTo(maxConnectionRect.right, maxConnectionRect.top);
			pDC->MoveTo(maxConnectionRect.right, maxConnectionRect.top);
			pDC->LineTo(maxConnectionRect.right, maxConnectionRect.bottom);
			pDC->MoveTo(maxConnectionRect.right, maxConnectionRect.bottom);
			pDC->LineTo(maxConnectionRect.left, maxConnectionRect.bottom);
			pDC->MoveTo(maxConnectionRect.left, maxConnectionRect.bottom);
			pDC->LineTo(maxConnectionRect.left, maxConnectionRect.top);

			pDC->SelectObject(oldPen);
			
		}

	}

	//draw Nodes & draw path
	int visited = 0;
	CPoint from,to;

	for(int num = 0; num<5*6; num++)
	{
		from.x = (num%6 + 1)*cellx;
		from.y = (num/(5+1) + 1)*celly;

		for(set<int>::iterator iter = path[num].begin(); iter!=path[num].end(); iter++)
		{
			if(*iter<visited)
				continue;
			
			to.x = (*iter%6 + 1)*cellx;
			to.y = (*iter/(5+1) + 1)*celly;
			pDC->MoveTo(from);
			pDC->LineTo(to);
		}
		visited++;

		CBrush brush;
		CRect rect(from.x-radius,from.y-radius,from.x+radius,from.y+radius);
		nodes[num].nodeRect = CRect(from.x-radius-5,from.y-radius-5,from.x+radius+5,from.y+radius+5);

		//chooseColor
		switch(nodes[num].country)
		{
			case 0:
				brush.CreateSolidBrush(RGB(128,128,128));
				pDC->SetBkColor(RGB(128,128,128));
				break;
            case 1:
				brush.CreateSolidBrush(RGB(255,0,0));
				pDC->SetBkColor(RGB(255,0,0));
				break;
			case 2:
				brush.CreateSolidBrush(RGB(0,255,0));
				pDC->SetBkColor(RGB(0,255,0));
				break;
			case 3:
				brush.CreateSolidBrush(RGB(0,0,255));
				pDC->SetBkColor(RGB(0,0,255));
				break;
			case 4:
				brush.CreateSolidBrush(RGB(255,255,0));
				pDC->SetBkColor(RGB(255,255,0));
				break;
			case 5:
				brush.CreateSolidBrush(RGB(255,0,255));
				pDC->SetBkColor(RGB(255,0,255));
				break;
			case 6:
				brush.CreateSolidBrush(RGB(0,255,255));
				pDC->SetBkColor(RGB(0,255,255));
				break;
			case 7:
				brush.CreateSolidBrush(RGB(0,128,128));
				pDC->SetBkColor(RGB(0,128,128));
				break;
			default:break;

		}

		if(nodes[num].isChosen)
		{
			CPen pen,*oldPen;
			oldPen = pDC->GetCurrentPen();
			pen.CreatePen(PS_SOLID,7,RGB(0,0,0));
			pDC->SelectObject(pen);
			pDC->Ellipse(rect);
			pDC->SelectObject(oldPen);
		}
	

		pDC->SelectObject(brush);
		pDC->Ellipse(rect);

		CFont font;
		font.CreateFont(
			radius*1.2,                        // nHeight
			0,                         // nWidth
			0,                         // nEscapement
			0,                         // nOrientation
			FW_NORMAL,                 // nWeight
			FALSE,                     // bItalic
			FALSE,                     // bUnderline
			0,                         // cStrikeOut
			ANSI_CHARSET,              // nCharSet
			OUT_DEFAULT_PRECIS,        // nOutPrecision
			CLIP_DEFAULT_PRECIS,       // nClipPrecision
			DEFAULT_QUALITY,           // nQuality
			DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
			"Arial");     
		pDC->SelectObject(&font);

		char text[1] = {0};
		pDC->SetTextColor(RGB(255,255,255));
		itoa(nodes[num].diceNum,text,10);
		pDC->DrawText(text,rect,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
	}
}