	void ScrollBar::setPropertyOverride(const std::string& _key, const std::string& _value)
	{
		/// @wproperty{ScrollBar, Range, size_t} Диапазон прокрутки.
		if (_key == "Range")
			setScrollRange(utility::parseValue<size_t>(_value));

		/// @wproperty{ScrollBar, RangePosition, size_t} Положение прокрутки.
		else if (_key == "RangePosition")
			setScrollPosition(utility::parseValue<size_t>(_value));

		/// @wproperty{ScrollBar, Page, size_t} Шаг прокрутки при нажатии на кнопку начала или конца.
		else if (_key == "Page")
			setScrollPage(utility::parseValue<size_t>(_value));

		/// @wproperty{ScrollBar, ViewPage, size_t} Шаг прокрутки при нажатии на одну из частей от кнопки до трекера.
		else if (_key == "ViewPage")
			setScrollViewPage(utility::parseValue<size_t>(_value));

		/// @wproperty{ScrollBar, WheelPage, size_t} Шаг прокрутки при прокрутке колесиком мыши.
		else if (_key == "WheelPage")
			setScrollWheelPage(utility::parseValue<size_t>(_value));

		/// @wproperty{ScrollBar, MoveToClick, bool} Режим перескакивания бегунка к месту клика.
		else if (_key == "MoveToClick")
			setMoveToClick(utility::parseValue<bool>(_value));

		/// @wproperty{ScrollBar, VerticalAlignment, bool} Вертикальное выравнивание.
		else if (_key == "VerticalAlignment")
			setVerticalAlignment(utility::parseValue<bool>(_value));

		/// @wproperty{ScrollBar, Repeat, bool} Sets whether scrollbar buttons should be triggered repeatedly so long as the mouse button is pressed down.
		else if (_key == "Repeat")
			setRepeatEnabled(utility::parseValue<bool>(_value));

		/// @wproperty{ScrollBar, RepeatTriggerTime, float} How long the mouse needs to be pressed on a scrollbar button for repeating to start.
		else if (_key == "RepeatTriggerTime")
			setRepeatTriggerTime(utility::parseValue<float>(_value));

		/// @wproperty{ScrollBar, RepeatStepTime, float) The time between each repeat step once repeating has started.
		else if (_key == "RepeatStepTime")
			setRepeatStepTime(utility::parseValue<float>(_value));

		else
		{
			Base::setPropertyOverride(_key, _value);
			return;
		}

		eventChangeProperty(this, _key, _value);
	}