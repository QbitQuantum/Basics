int run() {
	int page = 0, npage;
	char *input = (char*)malloc(sizeof(char));
	do {
		npage = drawSide(page);
		drawBoard(page);

		Body *line = newLine(35, 1, 60, 'v', '-');
		Stroke *lineStroke = newStroke(1, newBorder("|"));
		line->addStroke(line, lineStroke);
		stroke.setStrokeJoint(lineStroke, '#');
		registerBody("NULL", line);

		draw();
		gets(input);

		handleInput(&page, npage, input);
		
		clearAndRefresh();
		clearBodies();
	} while(!isKeyword(input, "exit"));

	return 0;
}