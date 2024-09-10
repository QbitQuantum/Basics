pair< pair<int, int>, pair<int, int> > GUIUtils::addHighGUIWindow(int column, int row, string windowName,
	int imageWidth, int imageHeight, int screenWidth, int screenHeight,
	int xOffset, int yOffset,
	int numberColumns, int numberRows) {

	if (numberColumns < 1 || numberRows < 1)
		return pair< pair<int, int>, pair<int, int> >(pair<int, int>(0, 0), pair<int, int>(0, 0));

	int imageWidthFinal = imageWidth;
	if (imageWidthFinal < 10)
		imageWidthFinal = (screenWidth - WINDOW_OPTIONS_WIDTH) / 2;

	int imageHeightFinal = imageHeight;
	if (imageHeightFinal < 10)
		imageHeightFinal = (screenHeight - WINDOW_DIGITS_HEIGHT) / 2;


	int windowHeightFinal = ((screenHeight - WINDOW_DIGITS_HEIGHT) / numberRows);
	int windowWidthFinal = (imageWidthFinal * windowHeightFinal / imageHeightFinal);

	if ((windowWidthFinal * numberColumns + WINDOW_OPTIONS_WIDTH) > screenWidth) {
		windowWidthFinal = ((screenWidth - WINDOW_OPTIONS_WIDTH) / numberColumns);
		windowHeightFinal = imageHeightFinal * windowWidthFinal / imageWidthFinal;
	}

	namedWindow(windowName, CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO | CV_GUI_EXPANDED);
	resizeWindow(windowName, windowWidthFinal - 2 * WINDOW_FRAME_THICKNESS, windowHeightFinal - WINDOW_FRAME_THICKNESS - WINDOW_HEADER_HEIGHT);

	int x = 0;
	if (column != 0) {
		x = windowWidthFinal * column;
	}

	int y = 0;
	if (row != 0) {
		y = windowHeightFinal * row;
	}

	x += xOffset;
	y += yOffset;

	moveWindow(windowName, x, y);

	return pair< pair<int, int>, pair<int, int> >(pair<int, int>(x, y), pair<int, int>(windowWidthFinal, windowHeightFinal));
}