void UIComponentTreeViewItem::onRender(Renderer* renderer, UIView* view)
{
	// Render this item full size

	/*RectangleShape back;
	back.setRect(view->getBounds());
	back.setColor(Color::Red);
	renderer->draw(back);*/

	// Render a little expandable flag if it applies
	if(mParent->getChildCount() > 0)
	{
		RectangleShape back;
		back.setRect(mParent->getChild(0)->getBounds());
		back.setSize(5.f, back.getSize().y);
		back.setColor(Color::Red);
		renderer->draw(back);
	}
}