	void BaseLayout::snapToParent(MyGUI::Widget* _child)
	{
		if (_child->isUserString("SnapTo"))
		{
			MyGUI::Align align = MyGUI::Align::parse(_child->getUserString("SnapTo"));

			MyGUI::IntCoord coord = _child->getCoord();
			MyGUI::IntSize size = _child->getParentSize();

			if (align.isHStretch())
			{
				coord.left = 0;
				coord.width = size.width;
			} else if (align.isLeft())
			{
				coord.left = 0;
			} else if (align.isRight())
			{
				coord.left = size.width - coord.width;
			} else
			{
				coord.left = (size.width - coord.width) / 2;
			}

			if (align.isVStretch())
			{
				coord.top = 0;
				coord.height = size.height;
			} else if (align.isTop())
			{
				coord.top = 0;
			} else if (align.isBottom())
			{
				coord.top = size.height - coord.height;
			} else
			{
				coord.top = (size.height - coord.height) / 2;
			}

			_child->setCoord(coord);
		}
	}