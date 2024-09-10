void Island::makeBumpers()
{
	CI_ASSERT( mOuterVerts.size() == 6 && mInnerVerts.size() == 5 );

	mBumpers.clear();
	mBumperBoundingBoxes.clear();
	mBumperVibrationLevels.clear();

	const float padding = 4;
	const float crookedPaddingPercent = 0.036f;
	const float boundingBoxExpansion = 1.1f;

	// left base
	{
		Path2d bumper;
		bumper.moveTo( mOuterVerts[0] );
		bumper.lineTo( mOuterVerts[1].x, mOuterVerts[1].y + padding );
		bumper.lineTo( mInnerVerts[1].x, mInnerVerts[1].y + padding );
		bumper.lineTo( mInnerVerts[0] );
		bumper.close();
		mBumpers.push_back( bumper );
	}

	// left top
	{
		Vec2f offsetOuter = ( mOuterVerts[2] - mOuterVerts[1] ) * crookedPaddingPercent;
		Vec2f offsetInner = ( Vec2f( mOuterVerts[2].x, mInnerVerts[2].y ) - mInnerVerts[1] ) * crookedPaddingPercent;

		Path2d bumper;
		bumper.moveTo( mOuterVerts[1] + offsetOuter );
		bumper.lineTo( mOuterVerts[2] );
		bumper.lineTo( mOuterVerts[2].x, mInnerVerts[2].y );
		bumper.lineTo( mInnerVerts[1] + offsetInner );
		bumper.close();
		mBumpers.push_back( bumper );
	}

	// right top
	{
		Vec2f offsetOuter = ( mOuterVerts[3] - mOuterVerts[4] ) * crookedPaddingPercent;
		Vec2f offsetInner = ( Vec2f( mOuterVerts[3].x, mInnerVerts[2].y ) - mInnerVerts[3] ) * crookedPaddingPercent;

		Path2d bumper;
		bumper.moveTo( mOuterVerts[3] );
		bumper.lineTo( mOuterVerts[4] + offsetOuter );
		bumper.lineTo( mInnerVerts[3] + offsetInner );
		bumper.lineTo( mOuterVerts[3].x, mInnerVerts[2].y );
		bumper.close();
		mBumpers.push_back( bumper );
	}

	// right base
	{
		Path2d bumper;
		bumper.moveTo( mOuterVerts[4].x, mOuterVerts[4].y + padding );
		bumper.lineTo( mOuterVerts[5] );
		bumper.lineTo( mInnerVerts[4] );
		bumper.lineTo( mInnerVerts[3].x, mInnerVerts[3].y + padding );
		bumper.close();
		mBumpers.push_back( bumper );
	}

	for( size_t i = 0; i < mBumpers.size(); i++ ) {
		mBumperVibrationLevels.push_back( 0 );

		// calculate an expanded bounding box for each bumper to do hit detection, ensuring that the entire edge is covered.
		Rectf bbox = mBumpers[i].calcBoundingBox();

		Vec2f center = bbox.getCenter();
		bbox -= center;
		bbox *= boundingBoxExpansion;
		bbox += center;

		mBumperBoundingBoxes.push_back( bbox );
	}
}