	// -------------------------------------------------------
	void BasePretzel::updateBounds(const ci::Vec2f &offset, const ci::Rectf &parentBounds){
		mOffset.set(offset);
		mParentBounds = parentBounds;

		mBounds.x2 = parentBounds.getWidth();
        
        mGlobalOffset.set( mGlobal->getGlobalPos() );
	}