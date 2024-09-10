	void WidgetLayout::SetPosition(const Vec2F& position)
	{
		RectF parentRect = GetParentRectangle();
		RectF rectangle(mData->offsetMin + mData->anchorMin*parentRect.Size(),
						mData->offsetMax + mData->anchorMax*parentRect.Size());

		Vec2F delta = position - rectangle.LeftBottom() + rectangle.Size()*mData->pivot;
		mData->offsetMin += delta;
		mData->offsetMax += delta;

		SetDirty();
	}