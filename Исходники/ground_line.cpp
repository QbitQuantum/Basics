CGroundLine::~CGroundLine()
{
	s_GroundLines.Remove( m_ListHandle );
	
	m_vStart.Init();
	m_vEnd.Init();
	m_LineWidth = 1;
}