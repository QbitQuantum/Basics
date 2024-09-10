void UIMapWindow::initHudNodes ()
{
	UINode* panel = new UINode(_frontend);
	panel->setImage("bones");
	panel->setStandardPadding();
	panel->setAlignment(NODE_ALIGN_TOP | NODE_ALIGN_CENTER);
	add(panel);

	UINode *innerPanel = new UINode(_frontend);
	innerPanel->setLayout(new UIHBoxLayout(0.01f));
	innerPanel->setPos(panel->getX() + 0.07f, panel->getY());
	_points = new UICavePackerNodePoint(_frontend, 30);
	_points->setFont(HUGE_FONT);
	_points->setId(UINODE_POINTS);
	innerPanel->add(_points);
	add(innerPanel);
}