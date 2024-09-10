void CNewYC::GetFontExtractWidth(CDC *pDC,CElecMapView *pView)
{
	CDC memdc;
	memdc.CreateCompatibleDC(pDC);
	float minx,miny,maxx,maxy;
	pView->GetFloatRect(&minx,&miny,&maxx,&maxy);
	if (!IntersectRect(minx,miny,maxx,maxy)) 
	{
		return;
	}
	GetRect(&minx,&miny,&maxx,&maxy);
	CPoint pt1,pt2,pt3,pt4;
	pt1=pView->UPtoLP(m_yc.rect.x0,m_yc.rect.y0);
	pt2=pView->UPtoLP(m_yc.rect.x0,m_yc.rect.y1);
	pt3=pView->UPtoLP(m_yc.rect.x1,m_yc.rect.y1);
	pt4=pView->UPtoLP(m_yc.rect.x1,m_yc.rect.y0);
	int hintcount,unitcount,hinthz,unithz;int hintdis,unitdis;
	hintcount=GetCharLen(m_yc.hint,33,&hinthz);
	unitcount=GetCharLen(m_yc.unit,17,&unithz);
	hintdis=0;unitdis=0;
	if (hintcount>0) hintdis=pView->ULtoLL(m_yc.hintdis);
	if (unitcount>0) unitdis=pView->ULtoLL(m_yc.unitdis);
	char s[256];
	memcpy(s,YC_STRING,sizeof(char)*m_yc.digitlength);
	s[m_yc.digitlength]='\0';
	CString tmpstr;
	tmpstr="";
	tmpstr=tmpstr+m_yc.hint;
	tmpstr=tmpstr+s;
	tmpstr=tmpstr+m_yc.unit;
	if ((pt3.x-pt1.x-hintdis-unitdis>(YC_MINDISWIDTH*(m_yc.digitlength+hintcount+unitcount+1)
		+pView->ULtoLL(m_yc.fontjj)*(m_yc.digitlength+hintcount+unitcount-hinthz-unithz)))&&
		(pt3.y-pt1.y>YC_MINDISHEIGHT))
	{
		m_yc.lgfont.lfHeight=pt3.y-pt1.y;
		m_yc.lgfont.lfWidth=(LONG)(pt3.x-pt1.x-hintdis-unitdis
			-pView->ULtoLL(m_yc.fontjj)*(m_yc.digitlength+hintcount+unitcount-hinthz-unithz))/
			(m_yc.digitlength+hintcount+unitcount);
		while (true) 
		{
			CFont m_font;
			LOGFONT tempfont;
			tempfont=m_yc.lgfont;
			m_font.CreateFontIndirect(&tempfont);
			CFont * m_oldfont=memdc.SelectObject(&m_font);
			CSize size;
			size=memdc.GetOutputTextExtent(tmpstr,m_yc.digitlength+hintcount+unitcount);//+2);
			size.cx=size.cx;//-m_yc.lgfont.lfWidth*1;//+qq;
			memdc.SelectObject(m_oldfont);
			//if ((minlen<=(pt3.x-pt1.x)*FontSizePercent)||(m_yc.lgfont.lfWidth<=0))
			if (((size.cx*(m_yc.digitlength+hintcount+unitcount+1)/(m_yc.digitlength+hintcount+unitcount))<=
				(pt3.x-pt1.x-hintdis-unitdis
				-pView->ULtoLL(m_yc.fontjj)*(m_yc.digitlength+hintcount+unitcount-hinthz-unithz)))||(m_yc.lgfont.lfWidth<=0))
			{
				m_yc.fontheight=pView->LLtoUL(m_yc.lgfont.lfHeight);
				m_yc.fontwidth=pView->LLtoUL(m_yc.lgfont.lfWidth);
				break;
			}else{
				m_yc.lgfont.lfWidth--;
			}
		}
	}

	CNewYCTool::canuse=true;
	CNewYCTool::m_yc=this->m_yc;
	sprintf(CNewYCTool::m_yc.ename,"");
	CNewYCTool::m_yc.fontwidth=(float)(pView->ULtoLL(m_yc.fontwidth));
	CNewYCTool::m_yc.fontheight=(float)(pView->ULtoLL(m_yc.fontheight));
	CNewYCTool::m_yc.fontjj=(float)(pView->ULtoLL(m_yc.fontjj));
	CNewYCTool::m_yc.hintdis=(float)(pView->ULtoLL(m_yc.hintdis));
}