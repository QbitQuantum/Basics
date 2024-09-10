void MultiSlider::setup()
{
	float numSliders = (float)mData.size();
	vec2 size = getSize();
	size.y = mSliderHeight = std::max( size.y - mPadding.mTop - mPadding.mBottom,
		( (float)FontSize::SMALL + mPadding.mBottom + mPadding.mTop ) );
	mSliderSpacing = mPadding.mTop;
	size.y = mSliderHeight * numSliders + mPadding.mTop * 2.0f + mPadding.mBottom * 2.0f;
	if( mData.size() > 1 ) size.y += mSliderSpacing * ( numSliders - 1.0f );
	setSize( size );

	vec2 hitRectSize = mHitRect.getSize();
	float width = hitRectSize.x - ( mPadding.mLeft + mPadding.mRight );
	Rectf rect = mHitRect;
	int index = 0;
	for( auto &it : mData ) {
		rect.y1 = mHitRect.y1 + mPadding.mTop + ( mSliderSpacing + mSliderHeight ) * index;
		rect.y2 = rect.y1 + mSliderHeight;

		rect.x1 = mHitRect.x1 + mPadding.mLeft;
		rect.x2 = rect.x1 + width;

		string sliderName = it.mKey;
		LabelRef label = Label::create( sliderName + "_LABEL", sliderName, FontSize::SMALL );
		mLabelsMap[sliderName] = label;
		addSubView( label );

		float labelHeight = label->getHeight();
		float offset = ( rect.getHeight() - labelHeight ) / 2.0f;
		label->setOrigin( vec2( rect.x1, rect.y1 + offset ) );
		index++;
	}
	View::setup();
}