CLayoutControl::CLayoutControl(const CDialogTemplate& rTmpl,
							   const CLayoutContainer& parent,
							   UINT nID, UINT nAnchor)
	: m_nID(nID), m_nAnchor(nAnchor)
{
	CDialogItemTemplate item = rTmpl.FindControl(nID);
	ATLASSERT( item.IsValid() );

	const CRect& rcParent = parent.GetBounds();
	
	m_rcMargins.SetRect( item.GetX() - rcParent.left,
		item.GetY() - rcParent.top,
		rcParent.right - item.GetX() - item.GetWidth(),
        rcParent.bottom - item.GetY() - item.GetHeight() );
	//ATLASSERT( m_rcMargins.left >= 0 && m_rcMargins.top >= 0 );
	rTmpl.MapDialogRect(m_rcMargins);
}