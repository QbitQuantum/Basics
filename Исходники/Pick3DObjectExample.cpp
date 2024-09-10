void Pick3DObjectExample::CreateWorldSpaceRayFromScreen(const Eegeo::v2& screenPoint, Ray& ray)
{
	const Eegeo::Camera::RenderCamera& renderCamera = m_cameraProvider.GetRenderCamera();

	//normalize the point
	double nx = 2.0 * screenPoint.GetX() / m_renderContext.GetScreenWidth() - 1;
	double ny = - 2.0 * screenPoint.GetY() / m_renderContext.GetScreenHeight() + 1;

	//prepare near and far points
	Eegeo::v4 near(nx, ny, 0.0f, 1.0);
	Eegeo::v4 far(nx, ny, 1.0f, 1.0);

	Eegeo::m44 invVP;
	Eegeo::m44::Inverse(invVP, renderCamera.GetViewProjectionMatrix());

	//unproject the points
	Eegeo::v4 unprojectedNear = Eegeo::v4::Mul(near, invVP);
	Eegeo::v4 unprojectedFar = Eegeo::v4::Mul(far, invVP);

	//convert to 3d
	Eegeo::v3 unprojectedNearWorld = unprojectedNear / unprojectedNear.GetW();
	Eegeo::v3 unprojectedFarWorld = unprojectedFar / unprojectedFar.GetW();

	//check intersection with a ray cast from camera position
	ray.m_origin = renderCamera.GetEcefLocation();
	ray.m_direction = (unprojectedNearWorld - unprojectedFarWorld).Norm();
}