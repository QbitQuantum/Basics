Strokes::Strokes(Strokes &strks)
{
    strokes.clear();
    for (Stroke *stroke = strks.first(); (stroke = strks.current()); strks.next())
    {
        QString d = stroke->serialize();
        addStroke(stroke->serialize());
    }

	maxX = strks.getMaxX();
	maxY = strks.getMaxY();

    currentStroke = 0;
}