	void SeparatorTextureControl::updatePosition()
	{
		if (getCurrentSeparator() != nullptr)
		{
			MyGUI::UString value = getCurrentSeparator()->getPropertySet()->getPropertyValue("Offset");
			MyGUI::Align corner = getCurrentSeparator()->getCorner();

			int offset = 0;
			if (MyGUI::utility::parseComplex(value, offset))
			{
				if (corner.isTop())
					mHorizontalSelectorControl->setCoord(MyGUI::IntCoord(0, offset, mTextureRegion.width, 1));
				else if (corner.isLeft())
					mVerticalSelectorControl->setCoord(MyGUI::IntCoord(offset, 0, 1, mTextureRegion.height));
				else if (corner.isBottom())
					mHorizontalSelectorControl->setCoord(MyGUI::IntCoord(0, mTextureRegion.height - offset, mTextureRegion.width, 1));
				else if (corner.isRight())
					mVerticalSelectorControl->setCoord(MyGUI::IntCoord(mTextureRegion.width - offset, 0, 1, mTextureRegion.height));
			}
		}
	}