void PuzzlePrinter::drawKillerSudokuCages (const SKGraph* graph,
                                           const QVector<int> & edges)
{
    // Killer Sudokus have cages AND groups: so the cages are drawn differently.
    // We keep the outer wall of the cage on our left and draw a dashed line
    // just inside that boundary.  This reduces ugly criss-crossing of lines.
    //
    // Directions and related arrays are all in clockwise order.
    enum  Direction {East, South, West, North, nDirections};
    const Direction rightTurn [nDirections] = {South, West, North, East};
    const Direction leftTurn [nDirections]  = {North, East, South, West};
    const int       wallOnLeft [nDirections] =
			    {1 << Above, 1 << Right, 1 << Below, 1 << Left};
    const int       wallAhead [nDirections] =
			    {1 << Right, 1 << Below, 1 << Left, 1 << Above};

    const int       deltaX  [nDirections] = {+1, 0, -1, 0};
    const int       deltaY  [nDirections] = {0, +1, 0, -1};

    int   cellInc [nDirections] = {graph->order(), +1, -graph->order(), -1};
    int   offset    = (m_sCell + 6) / 12;
    int   longSide  = m_sCell;
    int   shortSide = m_sCell - offset - offset;

    m_p->setPen (m_dashes);

    for (int n = 0; n < graph->cageCount(); n++) {
	int topLeft = graph->cageTopLeft(n);
	int cell    = topLeft;
	int edge    = edges.at (cell);
	int startX  = m_topX + m_sCell * graph->cellPosX (cell) + offset;
	int startY  = m_topY + m_sCell * graph->cellPosY (cell) + offset;
	int dx      = 0;
	int dy      = 0;
	QLine line (startX, startY, startX, startY);
	Direction direction = East;

	// Keep drawing until we get back to the starting cell and direction.
	do {
	    // If there is a wall on the left, follow it.
	    if (edge & wallOnLeft [direction]) {
		if (edge & wallAhead [direction]) {
		    // Go to wall (shortSide), draw line, turn right, new line.
		    dx = deltaX [direction] * shortSide;
		    dy = deltaY [direction] * shortSide;
		    line.setLine (line.x1(), line.y1(),
				  line.x2() + dx, line.y2() + dy);
		    m_p->drawLine (line);
		    direction = rightTurn [direction];
		    line.setLine (line.x2(), line.y2(), line.x2(), line.y2());
		}
		else {
		    // Extend to start of next cell (longSide).
		    dx = deltaX [direction] * longSide;
		    dy = deltaY [direction] * longSide;
		    line.setLine (line.x1(), line.y1(),
				  line.x2() + dx, line.y2() + dy);
		    cell = cell + cellInc [direction];
		    edge = edges.at (cell);
		}
	    }
	    // Else, if there is no wall on the left ...
	    else {
		// Draw line, turn left, new line, go to start of next cell.
		m_p->drawLine (line);
		direction = leftTurn [direction];
		dx = deltaX [direction] * (longSide - shortSide);
		dy = deltaY [direction] * (longSide - shortSide);
		line.setLine (line.x2(), line.y2(),
			      line.x2() + dx, line.y2() + dy);
		cell = cell + cellInc [direction];
		edge = edges.at (cell);

	    }
	} while (! ((cell == topLeft) && (direction == East)));
    }	// Draw next cage.
}