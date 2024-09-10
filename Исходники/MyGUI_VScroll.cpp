	void VScroll::setPropertyOverride(const std::string& _key, const std::string& _value)
	{
		if (_key == "Range") setScrollRange(utility::parseValue<size_t>(_value));
		else if (_key == "RangePosition") setScrollPosition(utility::parseValue<size_t>(_value));
		else if (_key == "Page") setScrollPage(utility::parseValue<size_t>(_value));
		else if (_key == "ViewPage") setScrollViewPage(utility::parseValue<size_t>(_value));
		else if (_key == "MoveToClick") setMoveToClick(utility::parseValue<bool>(_value));
		else
		{
			Base::setPropertyOverride(_key, _value);
			return;
		}
		eventChangeProperty(this, _key, _value);
	}