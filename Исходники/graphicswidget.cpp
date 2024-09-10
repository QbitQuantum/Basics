void GraphicsWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

	//set up painting with antialiasing etc
	QPainter painter;

	painter.begin(&elements);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setRenderHint(QPainter::HighQualityAntialiasing);
	painter.setRenderHint(QPainter::SmoothPixmapTransform);

	//transform coordinates to fit everything neatly on the screen
	painter.save();
	painter.setWorldTransform(getCurrentTransform());

	if (grid != nullptr)
	{
		//loop through and draw each entry
		for (const auto& cell: grid->getCells())
		{
			GridEntry &entry = grid->getEntry(cell);
			if (entry.modified) {
				entry.modified = false;
				painter.save();

				painter.translate(cell.x(), cell.y());

				QPen pen(Qt::black);
				pen.setWidthF(0);

				painter.setPen(pen);
				if (entry.type == GridEntry::Wall)
					painter.setBrush(Qt::darkBlue);

				else if (entry.type == GridEntry::Start)
					painter.setBrush(Qt::yellow);

				else if (entry.type == GridEntry::End)
					painter.setBrush(Qt::red);

				else if (entry.path)
					painter.setBrush(Qt::white);

				else if (entry.searched)
					painter.setBrush(Qt::cyan);
				
				else
					painter.setBrush(Qt::darkGreen);

                painter.drawConvexPolygon(DISPLAY_HEXAGON);

				painter.restore();
			}
		}
	}

	painter.restore();
	painter.setPen(Qt::white);

	QPainter screenPainter(this);
	screenPainter.fillRect(rect(), QBrush(Qt::black));
	screenPainter.drawImage(0, 0, elements);
}