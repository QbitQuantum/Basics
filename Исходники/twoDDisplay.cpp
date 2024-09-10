	foreach (const QLine &line, mLines) {
		painter->drawLine(line.x1() * pixWidth, line.y1() * pixHeight, line.x2() * pixWidth, line.y2() * pixHeight);
	}