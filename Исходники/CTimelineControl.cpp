CTimelineControl::CTimelineControl(uiWindow* parent, int x, int y, int w, int h)
	:uiWindow(L"timeLineControl", x, y, w, h, parent),
	m_cursorResize( UICURSOR_SIZEWE, true ),
	m_cursorArrow( UICURSOR_ARROW, true ),
	m_cursorSelect( IDC_HAND, true ),
	m_cursorMoveValue( UICURSOR_CROSS, true )
{
	changeWindowStyle( UISTYLE_CHILD );
	showWindow(true);

	m_timeLength	= 0.0f;
	m_crollX		= 0;
	m_maxValue = 0.0f;
	m_minValue = 0.0f;

	m_lengthPixel	= 15;	
	m_needSortValue	= true;	
	m_changeTimeAndValue = false;

	m_lbuttonDown = false;
	m_rbuttonDown = false;

	m_selectTimeID = -1;
	m_mouseActionState = -1;
}