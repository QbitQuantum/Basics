	IntCoord Window::_getActionScale(Widget* _widget)
	{
		if (_widget->isUserString("Scale"))
		{
			IntCoord result = IntCoord::parse(_widget->getUserString("Scale"));

			if (result == IntCoord(1, 1, 0, 0) && !mMovable)
				result.clear();

			return result;
		}
		else if (_widget->isUserString("Action"))
		{
			const std::string& action = _widget->getUserString("Action");
			if (action == "Move")
			{
				if (mMovable)
					return IntCoord(1, 1, 0, 0);
				else
					return IntCoord();
			}

			IntCoord coord;
			Align align = Align::parse(action);

			if (align.isLeft())
			{
				coord.left = 1;
				coord.width = -1;
			}
			else if (align.isRight())
			{
				coord.width = 1;
			}

			if (align.isTop())
			{
				coord.top = 1;
				coord.height = -1;
			}
			else if (align.isBottom())
			{
				coord.height = 1;
			}

			return coord;
		}

		return IntCoord();
	}