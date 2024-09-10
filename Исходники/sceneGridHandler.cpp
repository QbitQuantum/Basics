void SceneGridHandler::drawLineY(qreal pointY, QRectF const &sceneRect)
{
	pointY -= sceneRect.y();
	QLineF const newLine(0, pointY, sceneRect.width(), pointY);

	// checking whether the scene already has this line or not.
	// if not (lineIsFound is false), then adding it
	foreach (QLineF const &line, mLines) {
		if (qAbs(line.y1() - newLine.y1()) < indistinguishabilitySpace
				&& line.y2() == line.y1())
		{
			return;
		}
	}

	mLines.push_back(newLine);
}