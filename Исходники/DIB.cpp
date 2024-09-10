//////////////////
// Delete Object. Delete DIB and palette.
//
BOOL CDib::DeleteObject()
{
	m_pal.DeleteObject();
	if (m_hdd) {
		DrawDibClose(m_hdd);
		m_hdd = NULL;
	}
	memset(&m_bm, 0, sizeof(m_bm));
	return CBitmap::DeleteObject();
}