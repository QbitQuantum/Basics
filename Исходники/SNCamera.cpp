/**
*  @brief
*    Gets the current camera viewport corners
*/
bool SNCamera::GetViewportCorners(Vector3 &vUpperRight, Vector3 &vLowerRight, Vector3 &vLowerLeft, Vector3 &vUpperLeft, bool bContainerSpace, float fDistance)
{
	// Get the viewport
	const Renderer &cRenderer = GetSceneContext()->GetRendererContext().GetRenderer();
	const uint32 nViewportWidth  = static_cast<uint32>(cRenderer.GetViewport().GetWidth());
	const uint32 nViewportHeight = static_cast<uint32>(cRenderer.GetViewport().GetHeight());

	// Get near x/y/z
	const float fAspectRadio = static_cast<float>(nViewportWidth)/(static_cast<float>(nViewportHeight)*m_fAspect);
	const float e			 = static_cast<float>(1/Math::Tan(Math::DegToRad*m_fFOV*0.5f));

	// Get viewport corners
	vUpperRight.SetXYZ( fDistance/e,  fAspectRadio*fDistance/e, -fDistance);
	vLowerRight.SetXYZ( fDistance/e, -fAspectRadio*fDistance/e, -fDistance);
	 vLowerLeft.SetXYZ(-fDistance/e, -fAspectRadio*fDistance/e, -fDistance);
	 vUpperLeft.SetXYZ(-fDistance/e,  fAspectRadio*fDistance/e, -fDistance);

	// Transform the corners into container space?
	if (bContainerSpace) {
		Matrix3x4 mWorld = GetViewMatrix();
		mWorld.Invert();
		vUpperRight = mWorld*vUpperRight;
		vLowerRight = mWorld*vLowerRight;
		vLowerLeft  = mWorld*vLowerLeft;
		vUpperLeft  = mWorld*vUpperLeft;
	}

	// Done
	return true;
}