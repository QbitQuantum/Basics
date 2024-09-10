	void TabItem::setButtonWidth(int _width)
	{
		TabControl* owner = getParent() != nullptr ? getParent()->castType<TabControl>(false) : nullptr;
		if (owner != nullptr)
			owner->setButtonWidth(this, _width);
	}