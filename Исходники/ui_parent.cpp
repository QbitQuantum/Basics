void UIParent::addChild(std::shared_ptr<UIWidget> widget)
{
	Expects(widget->getParent() == nullptr || widget->getParent() == this);

	if (widget->getParent() == nullptr) {
		widget->setParent(this);
		childrenWaiting.push_back(widget);
	}

	markAsNeedingLayout();
}