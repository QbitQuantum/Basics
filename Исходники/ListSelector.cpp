void CListSelector::draw(CClientDC &dc, int orgX, int orgY, int width, int height)
{
	
	
	list<CSelectorItem>::iterator iter;
	
	int y0 = orgY;
	int y1 = orgY;
	
	int x0 = orgX;
	int x1 = orgX + width;

	
	//dc.Rectangle(orgX,orgY,orgX + width,orgY + height);
	
	int size=this->itemList.size();

	//dc.LineTo(x1,y1);
	int count=9;
	int start=4;
	int isNeedBreak=FALSE;

	int j=0;

	for(int i= -4 + focusIndex ; 
		i<= 4 + focusIndex;
		i++)
	{

		y0 = orgY + (j)*40;
		y1 = y0 + 40;
		CRect rect2(x0, y0+1, x1, y1);
		dc.Rectangle(&rect2);

		if(i==focusIndex)
		{
			CBrush *p=new CBrush();
			p->CreateSolidBrush(RGB(200,0,000));
			dc.FillRect(&rect2,p);
			dc.SetTextColor(RGB(255,255,255));
			delete p;
		}else{
			dc.SetTextColor(RGB(0,0,0));
		}

		int index = 0;
		if(i<0){
			index = (size*0X100000 + i) % size  ;
		}else{
			index=i % size ;
		}

		CString str(itemList[ index  ].getValue().c_str());		
		dc.DrawText(str,&rect2,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		j++;
	
	}	
	
}