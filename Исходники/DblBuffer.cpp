void DblBuffer::swap()
{
	if( (m_swapped = !m_swapped) ) {
		SetConsoleActiveScreenBuffer(m_hCons2);
	} else {
		SetConsoleActiveScreenBuffer(m_hCons1);
	}
}