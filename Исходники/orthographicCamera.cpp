void eel::OrthographicCamera::SetLens(FLOAT width, FLOAT height, FLOAT nearZ, FLOAT farZ)
{
	UpdateProjection(XMMatrixOrthographicLH(width, height, nearZ, farZ));
}