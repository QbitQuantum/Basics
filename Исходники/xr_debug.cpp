void DisplayStreamInfos(HWND hW)
{
	HWND hWS=GetDlgItem(hW,IDC_SAREA);
	HDC hdc;RECT r;HBRUSH hBO;int ch,dy,i,j,id;
	
	//----------------------------------------------------//
	
	GetClientRect(hWS,&r);                                // get size of stream display
	hdc=GetDC(hWS);                                       // device context
	r.right--;                                            // leave the right border intact
	ScrollDC(hdc,-1,0,&r,&r,NULL,NULL);                   // scroll one pixel to the left
	
	//----------------------------------------------------//
	
	hBO = (HBRUSH) SelectObject(hdc,hBStream[0]);                    // clean the right border
	PatBlt(hdc,r.right-1,0,1,r.bottom,PATCOPY);
	
	//----------------------------------------------------//
	
	dy=r.bottom/MAXCHAN;                                  // size of one channel area
	
	for(ch=0;ch<MAXCHAN;ch++)                             // loop the channels
  {
		if(s_chan[ch].iIrqDone)
		{
			s_chan[ch].iIrqDone=0;
			PatBlt(hdc,r.right-1,ch*r.bottom/MAXCHAN,
				1,dy,BLACKNESS);
			continue;
    }
		
		
		if(s_chan[ch].bOn)                                  // channel is on?
    {
			j=s_chan[ch].sval;if(j<0)  j=-j;                  // -> get one channel data (-32k ... 32k)
			j=(dy*j)/32768;   if(j==0) j=1;                   // -> adjust to display coords
			i=(dy/2)+(ch*r.bottom/MAXCHAN)-j/2;               // -> position where to paint it
			
			
			
			if     (s_chan[ch].iMute)    id=1;                // -> get color id
			else if(s_chan[ch].bNoise)   id=2;
			else if(s_chan[ch].bFMod==2) id=3;
			else if(s_chan[ch].bFMod==1) id=4;
			else                         id=5;
			
			SelectObject(hdc,hBStream[id]);                   // -> select the brush
			PatBlt(hdc,r.right-1,i,1,j,PATCOPY);              // -> paint the value line
    }
		
		if(ch) SetPixel(hdc,r.right-1,                      // -> not first line?
			ch*r.bottom/MAXCHAN,RGB(0,0,0));    // --> draw the line (one dot scrolled to the left)
  }
	
	//----------------------------------------------------//
	
	SelectObject(hdc,hBO);                                // repair brush
	
	ReleaseDC(hWS,hdc);                                   // release context
}