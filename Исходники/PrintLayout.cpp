void PrintLayout::printProfileDives(int divesPerRow, int divesPerColumn)
{
	int i, row = 0, col = 0, printed = 0, total = estimateTotalDives();
	int animationOriginal = prefs.animation_speed;

	struct dive *dive;
	if (!total)
		return;

	// disable animations on the profile:
	prefs.animation_speed = 0;

	// setup a painter
	QPainter painter;
	painter.begin(printer);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setRenderHint(QPainter::SmoothPixmapTransform);

	// setup the profile widget
	QPointer<ProfileWidget2> profile = MainWindow::instance()->graphics();
	const int profileFrameStyle = profile->frameStyle();
	profile->setFrameStyle(QFrame::NoFrame);
	profile->setPrintMode(true, !printOptions->color_selected);
	profile->setFontPrintScale(divesPerRow * divesPerColumn > 3 ? 0.6 : 1.0);
	QSize originalSize = profile->size();
	// swap rows/col for landscape
	if (printer->orientation() == QPrinter::Landscape) {
		int swap = divesPerColumn;
		divesPerColumn = divesPerRow;
		divesPerRow = swap;
	}

	// padding in pixels between two dives. no padding if only one dive per page.
	const int padDef = 20;
	const int padW = (divesPerColumn < 2) ? 0 : padDef;
	const int padH = (divesPerRow < 2) ? 0 : padDef;
	// estimate dimensions for a single dive
	const int scaledW = ESTIMATE_DIVE_DIM(pageW, divesPerColumn, padW);
	const int scaledH = ESTIMATE_DIVE_DIM(pageH, divesPerRow, padH);
	// padding in pixels between profile and table
	const int padPT = 5;
	// create a model and table
	ProfilePrintModel model;
	model.setFontsize(7); // if this is changed we also need to change 'const int sr' in the constructor
	// if there is only one dive per page row we pass fitNotesToHeight to be almost half the page height
	QPointer<QTableView> table(createProfileTable(&model, scaledW, (divesPerRow == 1) ? scaledH * 0.45 : 0.0));
	// profilePrintTableMaxH updates after the table is created
	const int tableH = profilePrintTableMaxH;
	// resize the profile widget
	profile->resize(scaledW, scaledH - tableH - padPT);
	// offset table or profile on top
	int yOffsetProfile = 0, yOffsetTable = 0;
	if (printOptions->notes_up)
		yOffsetProfile = tableH + padPT;
	else
		yOffsetTable = scaledH - tableH;

	// plot the dives at specific rows and columns on the page
	for_each_dive (i, dive) {
		if (!dive->selected && printOptions->print_selected)
			continue;
		if (col == divesPerColumn) {
			col = 0;
			row++;
			if (row == divesPerRow) {
				row = 0;
				printer->newPage();
			}
		}
		// draw a profile
		QTransform origTransform = painter.transform();
		painter.translate((scaledW + padW) * col, (scaledH + padH) * row + yOffsetProfile);
		profile->plotDive(dive, true); // make sure the profile is actually redrawn
#ifdef Q_OS_LINUX // on Linux there is a vector line bug (big lines in PDF), which forces us to render to QImage
		QImage image(scaledW, scaledH - tableH - padPT, QImage::Format_ARGB32);
		QPainter imgPainter(&image);
		imgPainter.setRenderHint(QPainter::Antialiasing);
		imgPainter.setRenderHint(QPainter::SmoothPixmapTransform);
		profile->render(&imgPainter, QRect(0, 0, scaledW, scaledH - tableH - padPT));
		imgPainter.end();
		painter.drawImage(image.rect(),image);
#else // for other OS we can try rendering the profile as vector
		profile->render(&painter, QRect(0, 0, scaledW, scaledH - tableH - padPT));
#endif
		painter.setTransform(origTransform);

		// draw a table
		QPicture pic;
		QPainter picPainter;
		painter.translate((scaledW + padW) * col, (scaledH + padH) * row + yOffsetTable);
		model.setDive(dive);
		picPainter.begin(&pic);
		table->render(&picPainter);
		picPainter.end();
		painter.drawPicture(QPoint(0,0), pic);
		painter.setTransform(origTransform);
		col++;
		printed++;
		emit signalProgress((printed * 100) / total);
	}
	// cleanup
	painter.end();
	profile->setFrameStyle(profileFrameStyle);
	profile->setPrintMode(false);
	profile->resize(originalSize);
	// we need to force a redraw of the profile so it switches back from print mode
	profile->plotDive(0, true);
	// re-enable animations
	prefs.animation_speed = animationOriginal;
}