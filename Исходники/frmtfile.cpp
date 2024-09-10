/////////////////////////////////////////////////////////////////////////////
//                    CFragment::AddString
void CFragment::AddString( CSTR_line* Comingline, PageElementCount* Count)
{
 CFPage    Page;
 CSTR_line line;
 CSTR_attr line_attr;
 CFString* String;
 RECT     TmpRect,*PrevStringRect;
 uchar      Flag_Continuation_Strings = FALSE;
 uchar      dist;

 if(CheckLineForFilling(Comingline)==FALSE)
	return;
 line = *Comingline;
 CSTR_GetLineAttr(line , &line_attr);
 SetRect(&TmpRect, line_attr.col - TemplateOffset.x ,
                 line_attr.row - TemplateOffset.y,
                 line_attr.col - TemplateOffset.x+ line_attr.wid,
  				 line_attr.row - TemplateOffset.y + line_attr.hei);
 UnionRect(&m_rectFrag, &m_rectFrag, &TmpRect);
 dist = line_attr.hei/2;

 if( m_wStringsCount>0 ) {
   String = (CFString*)m_arStrings[m_wStringsCount-1];
   PrevStringRect=&String->m_rectString ;
   if( TmpRect.top < PrevStringRect->bottom  &&  TmpRect.left > PrevStringRect->right &&
	   abs(TmpRect.top    - PrevStringRect->top)    <=dist &&
       abs(TmpRect.bottom - PrevStringRect->bottom) <=dist )
       Flag_Continuation_Strings = TRUE;
 }

 if(!Flag_Continuation_Strings)	{
	++m_wStringsCount;
	++Count->Strings;
	m_arStrings.push_back( new CFString() );
	String = m_arStrings[m_wStringsCount-1];
	String->S_Flags = line_attr.Flags; //NEGA_STR
 }

 assert(String);
 String->ExtractWordsFromString( Comingline ,Count );
}