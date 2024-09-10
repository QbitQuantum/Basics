void UIComponentTabView::refreshTabButtons()
{
	// Add a button per tab
	for(std::size_t i = 0; i < tabs.size(); ++i)
	{
		Widget* tabButton = new Widget();
		tabButton->setRect(parent->getPosition().x + 50.f * i, parent->getPosition().y, 49.f, 20.f);
		//tabButton->addController(new UIDebugWidget(Color::Grey));
	///	tabButton->addController(new UITextNode("Tab " + String::number(i), UITextNode::Center, UITextNode::Center));
		tabButton->onClick.connect(sigc::bind(sigc::mem_fun(this, &UIComponentTabView::onTabButtonClicked), i));
		parent->attach(tabButton);
	}
}