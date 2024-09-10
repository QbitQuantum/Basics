void UICanvas::showMessageBox(const String& message)
{
	Widget* modalBackground = new Widget();
	
	UIWindow* surface = addSurface("modal");
	surface->attach(modalBackground);
	modalBackground->setRect(surface->getRect());

	UILabel* label = new UILabel(message);
	label->setSize(700,50);
	//label->setCenter(modalBackground->getMiddlePosition());
	modalBackground->attach(label);
};