void CVirtualLCD::UpdateScreenContent()
{
/*
#pragma warning(disable : 4996) 
  	  HANDLE h= CreateFile("c:\\polys", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, NULL);
	    for (int i=0; i<400; i++)
	    {
  	    char s[100000]= "";
	      sprintf(s, "POLY=%d,", i);
        for (int p=0; p<table[i].nbPoly; p++)
        {
          strcat(s, "{");
          for (int pt= 0; pt<table[i].poly[p].nbPoints; pt++)
            sprintf(s, "%s%d,%d,", s, table[i].poly[p].points[pt].x, table[i].poly[p].points[pt].y);
          s[strlen(s)-1]='}';
        }
	      sprintf(s, "%s\npoly=%d,", s, i);
        for (int p=0; p<table_LCD[i].nbPoly; p++)
        {
          strcat(s, "{");
          for (int pt= 0; pt<table_LCD[i].poly[p].nbPoints; pt++)
            sprintf(s, "%s%d,%d,", s, table_LCD[i].poly[p].points[pt].x, table_LCD[i].poly[p].points[pt].y);
          s[strlen(s)-1]='}';
        }
        strcat(s, "\n");
        DWORD wrote;
	      WriteFile(h, s, strlen(s), &wrote, NULL);
	    }
	    CloseHandle(h);
	*/
  u64 *e= (u64 *)AT91C_SLCDC_MEM;
  RECT re={0, 0, Skin.HighResScreen.x, Skin.HighResScreen.y};
  FillRect(m_hMemDC, &re, m_hBrushRepaint);

  re.right=Skin.screen.right; re.bottom=Skin.screen.bottom;
  FillRect(m_hMyDC, &re, m_hBrushRepaint);

  SelectObject(m_hMemDC, GetStockObject(DC_PEN));
  SetDCPenColor(m_hMemDC, Skin.screenfore);

  SelectObject(m_hMyDC, GetStockObject(DC_PEN));
  SetDCPenColor(m_hMyDC, Skin.screenfore);

  if (Skin.NbHighResPoly<400 || Skin.NbLowResPoly<400) return;
  SetPolyFillMode(m_hMyDC, WINDING);
  SetPolyFillMode(m_hMemDC, WINDING);
  for (int r=0; r<10; r++)
    for (int c=0; c<40; c++)
      if ((e[r]&((u64)1<<c))!=0)	
      {
        if (Skin.lowres[r*40+c].NbPoly==-1)
        {
          TSourceGraphic *sg= (TSourceGraphic*)&Skin.lowres[r*40+c];
          BitBlt(m_hMyDC, sg->p[0], sg->p[1], sg->p[2], sg->p[3], Skin.dc, sg->p[4], sg->p[5], SRCCOPY);
        } else
          for (int n=0; n<Skin.lowres[r*40+c].NbPoly; n++)
            Polygon(m_hMyDC, Skin.lowres[r*40+c].poly[n].points, Skin.lowres[r*40+c].poly[n].NbPoints);
        if (Skin.highres[r*40+c].NbPoly==-1)
        {
          TSourceGraphic *sg= (TSourceGraphic*)&Skin.highres[r*40+c];
          BitBlt(m_hMemDC, sg->p[0], sg->p[1], sg->p[2], sg->p[3], Skin.dc, sg->p[4], sg->p[5], SRCCOPY);
        } else
          for (int n=0; n<Skin.highres[r*40+c].NbPoly; n++)
            Polygon(m_hMemDC, Skin.highres[r*40+c].poly[n].points, Skin.highres[r*40+c].poly[n].NbPoints);
      }
  HDC hdc= ::GetDC(m_hWnd);
  BitBlt(hdc, 0,0, Skin.screen.right,Skin.screen.bottom, m_hMyDC, 0,0, SRCCOPY);
  ::ReleaseDC(m_hWnd, hdc);
}