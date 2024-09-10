void Engine::PerspCamera::setPerspective(const FLOAT &fov, const UINT &width, const UINT &height, const FLOAT &n, const FLOAT &f)
{
	FLOAT ratio = (FLOAT)width / height;
	FLOAT yfar = tanf(fov * 0.5f) * f;
	FLOAT xfar = yfar * ratio;

	*_projectionMatrix = XMMatrixPerspectiveFovRH(fov, ratio, n, f);

	_near = n;
	_far = f;
	_fov = fov * ratio;
	_frusSphereDistance = n + (f - n) * 0.5f;
	_frusSphereRadius = XMVectorGetX(XMVector3Length(XMVectorSet(xfar, yfar, f, 0.0f) - XMVectorSet(0.0f, 0.0f, _frusSphereDistance, 0.0f)));
}