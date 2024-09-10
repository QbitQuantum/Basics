void CRyujo::Render(HDC hdc)
{
	TransparentBlt(hdc,
		int(m_tInfo.fX - m_tInfo.fCX /2 ),
		int(m_tInfo.fY - m_tInfo.fCY /2 ),
		(int)m_tInfo.fCY, (int)m_tInfo.fCY,
		(*m_pMapBmp)[m_strEnemyID]->GetMemDC(),
		0,0,
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,RGB(255,0,216));
}