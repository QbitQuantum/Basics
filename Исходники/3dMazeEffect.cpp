void C3dMazeEffect::DrawMazeGaps(HDC hDC)
{
	int i, j;

	HPEN hPen = CreatePen(PS_SOLID, 1, MAZE_GRID_COLOR);
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

	const int xOffset = GetClientArea().right - m_pMaze->GetMazeSize()*MAZE_GRID_SIZE -1;
	const int yOffset = GetClientArea().top;

	// horizontal gaps
	for(i=0; i<m_pMaze->GetMazeSize()+1; i++)
	{
		for(j=0; j<m_pMaze->GetMazeSize(); j++)
		{
			if(m_pMaze->IsGap(j, i, TRUE))
			{
				MoveToEx(hDC, xOffset+j*MAZE_GRID_SIZE, yOffset+i*MAZE_GRID_SIZE, NULL);
				LineTo(hDC, xOffset+(j+1)*MAZE_GRID_SIZE, yOffset+i*MAZE_GRID_SIZE);
			}
		}
	}

	// vertical gaps
	for(i=0; i<m_pMaze->GetMazeSize(); i++)
	{
		for(j=0; j<m_pMaze->GetMazeSize()+1; j++)
		{
			if(m_pMaze->IsGap(j, i, FALSE))
			{
				MoveToEx(hDC, xOffset+j*MAZE_GRID_SIZE, yOffset+i*MAZE_GRID_SIZE, NULL);
				LineTo(hDC, xOffset+j*MAZE_GRID_SIZE, yOffset+(i+1)*MAZE_GRID_SIZE);
			}
		}
	}

	{	// original pos
		HBRUSH hBrush = CreateSolidBrush(MAZE_ORIGINAL_POS_COLOR);
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		SelectObject(hDC, GetStockObject(NULL_PEN));

		int x, y;
		m_pMaze->GetOriginalPos(x, y);

		Ellipse(hDC,
			xOffset + MAZE_GRID_SIZE/2 + x*MAZE_GRID_SIZE - MAZE_ORIGINAL_POS_SIZE/2,
			yOffset + MAZE_GRID_SIZE/2 + y*MAZE_GRID_SIZE - MAZE_ORIGINAL_POS_SIZE/2,
			xOffset + MAZE_GRID_SIZE/2 + x*MAZE_GRID_SIZE + MAZE_ORIGINAL_POS_SIZE/2,
			yOffset + MAZE_GRID_SIZE/2 + y*MAZE_GRID_SIZE + MAZE_ORIGINAL_POS_SIZE/2);

		SelectObject(hDC, hOldBrush);
		DeleteObject(hBrush);
	}

	{	// target pos
		HBRUSH hBrush = CreateSolidBrush(MAZE_TARGET_POS_COLOR);
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		SelectObject(hDC, GetStockObject(NULL_PEN));

		int x, y;
		m_pMaze->GetTargetPos(x, y);

		Ellipse(hDC,
			xOffset + MAZE_GRID_SIZE/2 + x*MAZE_GRID_SIZE - MAZE_TARGET_POS_SIZE/2,
			yOffset + MAZE_GRID_SIZE/2 + y*MAZE_GRID_SIZE - MAZE_TARGET_POS_SIZE/2,
			xOffset + MAZE_GRID_SIZE/2 + x*MAZE_GRID_SIZE + MAZE_TARGET_POS_SIZE/2,
			yOffset + MAZE_GRID_SIZE/2 + y*MAZE_GRID_SIZE + MAZE_TARGET_POS_SIZE/2);

		SelectObject(hDC, hOldBrush);
		DeleteObject(hBrush);
	}

	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
}