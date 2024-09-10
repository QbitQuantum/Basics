	void PretzelTextField::updateBounds(const ci::vec2 &offset, const ci::Rectf &parentBounds) {
		BasePretzel::updateBounds(offset, parentBounds);

		// this could be cleaner
		mTextFieldBounds = Rectf(mLabelSize.x + 25, mBounds.y1 + 5, mBounds.x2 - 10, mBounds.y2 - 5);
	}