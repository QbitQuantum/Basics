	void ScrollViewBase::updateScrollPosition()
	{
		// размер контекста
		IntSize contentSize = getContentSize();
		// текущее смещение контекста
		IntPoint contentPoint = getContentPosition();
		// расчетное смещение
		IntPoint offset = contentPoint;

		IntSize viewSize = getViewSize();

		Align align = getContentAlign();

		if (contentSize.width > viewSize.width)
		{
			// максимальный выход влево
			if ((offset.left + viewSize.width) > contentSize.width)
			{
				offset.left = contentSize.width - viewSize.width;
			}
			// максимальный выход вправо
			else if (offset.left < 0)
			{
				offset.left = 0;
			}
		}
		else
		{
			if (align.isLeft())
			{
				offset.left = 0;
			}
			else if (align.isRight())
			{
				offset.left = contentSize.width - viewSize.width;
			}
			else
			{
				offset.left = (contentSize.width - viewSize.width) / 2;
			}
		}

		if (contentSize.height > viewSize.height)
		{
			// максимальный выход вверх
			if ((offset.top + viewSize.height) > contentSize.height)
			{
				offset.top = contentSize.height - viewSize.height;
			}
			// максимальный выход вниз
			else if (offset.top < 0)
			{
				offset.top = 0;
			}
		}
		else
		{
			if (align.isTop())
			{
				offset.top = 0;
			}
			else if (align.isBottom())
			{
				offset.top = contentSize.height - viewSize.height;
			}
			else
			{
				offset.top = (contentSize.height - viewSize.height) / 2;
			}
		}

		if (offset != contentPoint)
		{
			if (nullptr != mVScroll) mVScroll->setScrollPosition(offset.top);
			if (nullptr != mHScroll) mHScroll->setScrollPosition(offset.left);
			setContentPosition(offset);
		}
	}