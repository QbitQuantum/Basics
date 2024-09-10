int CTaiTestEdit::MoveOnWhichParam(CPoint &point)
{
	CRect r(0,0,0,0);

	int nPa = -1;
	CHARFORMAT cf;
	this->GetDefaultCharFormat (cf);
	int nHeight = cf.yHeight+cf.yOffset;

	CDC* pDC = GetDC();
	CFont* pOldF = pDC->SelectObject (&m_Font);

	int nOld = pDC->SetMapMode(MM_TWIPS  ); 
	POINT p;
	p.x = 100;
	p.y = nHeight;

	pDC->SetMapMode(nOld  ); 

	CHARFORMAT fmt = GetCharFormat(CFM_SIZE);
	float f2 = GetDeviceCaps( pDC->m_hDC ,  LOGPIXELSX)/1440.0f*fabs((float)fmt.yHeight)+2 ;
	int nLine = point.y /f2;

	nLine = -1;

	int nLine2 = GetLineCount();
	int j = 0;
	int nNow = 0;
	for(;j<nLine2;j++)
	{
		CPoint pt;
		GetPosFormChar(pt, nNow);
		char ch[2048];
		int j2= GetLine( j,ch ) ;
		if(j2<0)
			continue;
		nNow+=j2;
		if(pt.y==point.y && pt.y==0)
		{
			nLine = j;
			break;
		}
		if(pt.y>point.y)
		{
			nLine = j-1;
			if(nLine<0) nLine = 0;
			break;
		}
	}
	if(	nLine == -1)
	{
		nLine = nLine2-1;
	}



	r.top = nLine*fabs(f2)-1;

	CRect r2;
	m_editDlg.GetWindowRect(r2);


	int nx = 0;
	j = 0;
	CString s = "";
	int nRtn = -1;
	if(nLine<=nLine2)
	{
		char ch[1024];
		j= GetLine( nLine,ch ) ;
		if(j>0)
			ch[j] = 0;
		s = ch;

		int i = 0;

		nRtn = GetCharFormPos(point);
		if(nRtn>=0)
		{
			int nTot = 0;
			int j = 0;
			char ch[1024];
			CString sTmp;
			for( i = 0;i<nLine;i++)
			{
				j= GetLine( i,ch ) ;
				if(j>0)
					ch[j] = 0;
				sTmp = ch;
				nTot+=j;
			}

			int nTotOld = nTot;



			TRACE("nRtn = %d\n",nRtn);

			j= GetLine(nLine,ch ) ;
			if(j>0)
				ch[j] = 0;
			CString ss2 = ch;
			if(this->m_jiShu )
			{
				for( i= 0;i<m_jiShu->numPara ;i++)
				{
					if(m_nParamInfo [i].m_nParamB == -1)
						continue;
					if(nRtn>=this->m_nParamInfo [i].m_nParamB && nRtn<=this->m_nParamInfo [i].m_nParamB+this->m_nParamInfo [i].m_nParamCount)
					{
					
						nPa = i;
						int n2 = m_nParamInfo [i].m_nParamB-nTotOld;
						if(n2<0) 
						{
							n2 = 0;

						}
						CString ss3 = ss2.Left (n2);
						r.left = pDC->GetTextExtent(ss3).cx;
						ss3 = "";
						if(n2+m_nParamInfo [i].m_nParamCount<=ss2.GetLength ()) 
						{
							ss3 = ss2.Mid (n2,m_nParamInfo [i].m_nParamCount);
						}
						else
						{
							pDC->SelectObject (pOldF);
							this->ReleaseDC (pDC);

							CString s33 = "n2+m_nParamInfo  = ";
							CString s44;
							s44.Format ("%d,   ",n2+m_nParamInfo [i].m_nParamCount);
							s33+=s44;
							s33+=ss2;
							s44.Format ("=%d,   ",ss2.GetLength ());
							s33+=s44;

							return false;
						}

						r.right = r.left +5+ pDC->GetTextExtent(ss3).cx;
					}
				}
			}
		}
	}
	pDC->SelectObject (pOldF);
	this->ReleaseDC (pDC);

	if(nPa<0 || nPa>=0 && m_nPaPre!=nPa && m_nPaPre >=0 )//
	{
		if(m_editDlg.IsWindowVisible ()) 
		{
			m_editDlg.ShowWindow (SW_HIDE);
			if(m_nPaPre>=0 && m_nPaPre<m_jiShu->numPara )
			{
				CString s;
				s = m_editDlg.GetText ();
				float f = atof(s);

			
				if(f>=m_jiShu->min[m_nPaPre] && f<=m_jiShu->max[m_nPaPre] )
				{
					if(m_jiShu && m_nParamInfo [m_nPaPre].m_nParamB!=-1)
					{
						this->m_nParamInfo [m_nPaPre].fVal = f;
						s = "   " + s;
						s+="   ";
						int nAdd = s.GetLength ()-this->m_nParamInfo [m_nPaPre].m_nParamCount ;
						SetSel(m_nParamInfo [m_nPaPre].m_nParamB,m_nParamInfo [m_nPaPre].m_nParamB+m_nParamInfo [m_nPaPre].m_nParamCount);
						ReplaceSel(s);
						m_nParamInfo [m_nPaPre].m_nParamCount +=nAdd;
						for(int j = m_nPaPre+1;j<m_jiShu->numPara ;j++)
						{
							m_nParamInfo [j].m_nParamB += nAdd;
						}
					}
				}
				else
					AfxMessageBox("参数数值超过最大值或最小值!");

			}
		}
	}

	if(nPa >=0)
	{
		{
			CString s;
			s = CLongString::FloatToString(m_nParamInfo [nPa].fVal);
			if(m_jiShu)
				m_editDlg.SetText (s,m_jiShu->min[nPa],m_jiShu->max[nPa]);
			else
				m_editDlg.SetText (s);

			CPoint pt;
			GetPosFormChar(pt, m_nParamInfo [nPa].m_nParamB );

			r.left = pt.x;
			r.right =r.left+r2.Width ();
			r.top = pt.y;
			r.bottom =r.top+r2.Height ();
			m_editDlg.MoveWindow (r);

			m_editDlg.ShowWindow (SW_SHOW);
			m_editDlg.SetSelEdit ();
		}
	}

	m_nPaPre = nPa;

	return nPa;
}