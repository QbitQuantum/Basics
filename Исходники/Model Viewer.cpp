void ModelViewer::OnDraw()
{
	// Animate the model if requested
	if (mAnimate)
	{
		ulong delta = Time::GetDeltaMS();

		if (delta > 0)
		{
			const Vector3f axis (0.0f, 0.0f, 1.0f);
			Quaternion rot (axis, -Float::Sin(0.0005f * delta));
			mStage->SetRelativeRotation( rot * mStage->GetRelativeRotation() );
		}
	}

	// Fade out the status bar
	if (mSbHighlight != 0 && mTimestamp != 0.0f)
	{
		float current = Time::GetTime();
		float factor = (current - mTimestamp) / 2.0f;
		factor = Float::Clamp(factor, 0.0f, 1.0f);
		mSbHighlight->SetAlpha( (1.0f - factor) * 0.85f );
		if (factor == 1.0f) mTimestamp = 0.0f;
	}

	// If there was a request to reset the viewpoint, now should be a good time as we know what's visible
	if (mResetCamera > 0 && mResetCamera++ > 1)
	{
		mResetCamera = 0;
		const Bounds& bounds = mInst->GetAbsoluteBounds();

		if (bounds.IsValid())
		{
			const Vector3f& center (bounds.GetCenter());
			Vector3f total = bounds.GetMax() - bounds.GetMin();
			total.Normalize();

			// Default positions should always be at a downward angle
			Vector3f down	  (0.175f, -0.5f, -1.0f );
			Vector3f straight ( 0.35f, -1.0f, -0.35f);

			down.Normalize();
			straight.Normalize();

			// How much the camera will be angled downward depends on the dot product
			float dot = total.Dot( Vector3f(0.0f, 0.0f, 1.0f) );
			Vector3f dir ( Interpolation::Linear(down, straight, dot) );

			// Distance should be far enough away to view the entire model
			float distance = Float::Clamp(bounds.GetRadius() * 1.2f, 1.0f, mCam->GetDolly().z);

			// Animate the camera to the calculated position
			mCam->Stop();
			mCam->AnimateTo(center, dir, distance, 0.5f);
		}
	}
}