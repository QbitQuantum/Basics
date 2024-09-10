 void SpaceTurnRight::draw(CDC &dc)
{
    if(m_bFirstDraw){
	for(int i=0;i<SIZE_OF_VERTEX-1;++i)
	{
		(m_pt+i)->x = (m_pt3d+i)->x;
		(m_pt+i)->y = (m_pt3d+i)->y;
	}
	}
	CPen pen;   //╩Фжф╩╜╠й
	pen.CreatePen(PS_SOLID,2,RGB(255,128,0));
	CPen* poldpen = dc.SelectObject(&pen);

	dc.Polygon(m_pt,SIZE_OF_VERTEX-1);


	m_bFirstDraw = FALSE;
	dc.SelectObject(poldpen);
	pen.DeleteObject();

	m_tips->draw(dc);
	//pen.DeleteObject();
}