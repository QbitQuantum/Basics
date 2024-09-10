void ShadowLight::CreateProjectionMatrix(float screenDepth, float screenNear)
{
	//Field of view and screen aspect for square light
	float fov = (float)XM_PI / 2.0f;
	float screenAspect = 1.0f;

	projectionMatrix = XMMatrixPerspectiveFovLH(fov, screenAspect, screenNear, screenDepth);
}