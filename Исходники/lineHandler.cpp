void LineHandler::deleteLoop(QPolygonF &line, int startPos)
{
	for (int i = startPos; i < line.size() - 3; ++i) {
		bool isCut = false;
		for (int j = i + 2; j < line.size() - 1; ++j) {
			QPointF cut;
			if (QLineF(line[i], line[i + 1]).intersect(QLineF(line[j], line[j + 1]), &cut)
					== QLineF::BoundedIntersection)
			{
				if ((i != 0) || !((j == line.size() - 2)
						&& (QLineF(line.first(), line.last()).length() < (kvadratik * 2))))
				{
					QPainterPath path;
					QPainterPathStroker ps;
					ps.setWidth(kvadratik);
					for (int k = 0; k < line.size() - 1; ++k) {
						path.moveTo(line[k]);
						path.lineTo(line[k + 1]);
						if (ps.createStroke(path).contains(cut)) {
							line.insert(k + 1, cut);
							break;
						}
					}

					line.remove(i + 2, j - i);
					deleteLoop(line, i);
					isCut = true;
					break;
				}
			}
		}

		if (isCut) {
			break;
		}
	}
}