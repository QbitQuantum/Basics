//-----------------------------------------------------------------------------
// LLKeyframeFallMotion::onUpdate()
//-----------------------------------------------------------------------------
BOOL LLKeyframeFallMotion::onUpdate(F32 activeTime, U8* joint_mask)
{
	BOOL result = LLKeyframeMotion::onUpdate(activeTime, joint_mask);
	F32  slerp_amt = clamp_rescale(activeTime / getDuration(), 0.5f, 0.75f, 0.f, 1.f);

	if (mPelvisState.notNull())
	{
		mPelvisState->setRotation(mPelvisState->getRotation() * slerp(slerp_amt, mRotationToGroundNormal, LLQuaternion()));
	}
	
	return result;
}