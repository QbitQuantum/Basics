void ComputeFrustum(const XMMATRIX& viewProj, Frustum& frustum)
{
	XMVECTOR det;
	XMMATRIX invViewProj = XMMatrixInverse(&det, viewProj);

	// Corners in homogeneous clip space
	XMVECTOR corners[8] =
	{                                               //                         7--------6
		XMVectorSet(1.0f, -1.0f, 0.0f, 1.0f),      //                        /|       /|
		XMVectorSet(-1.0f, -1.0f, 0.0f, 1.0f),      //     Y ^               / |      / |
		XMVectorSet(1.0f, 1.0f, 0.0f, 1.0f),      //     | _              3--------2  |
		XMVectorSet(-1.0f, 1.0f, 0.0f, 1.0f),      //     | /' Z           |  |     |  |
		XMVectorSet(1.0f, -1.0f, 1.0f, 1.0f),      //     |/               |  5-----|--4
		XMVectorSet(-1.0f, -1.0f, 1.0f, 1.0f),      //     + ---> X         | /      | /
		XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f),      //                      |/       |/
		XMVectorSet(-1.0f, 1.0f, 1.0f, 1.0f),      //                      1--------0
	};

	// Convert to world space
	for (uint32 i = 0; i < 8; ++i)
		corners[i] = XMVector3TransformCoord(corners[i], invViewProj);

	// Calculate the 6 planes
	frustum.Planes[0] = XMPlaneFromPoints(corners[0], corners[4], corners[2]);
	frustum.Planes[1] = XMPlaneFromPoints(corners[1], corners[3], corners[5]);
	frustum.Planes[2] = XMPlaneFromPoints(corners[3], corners[2], corners[7]);
	frustum.Planes[3] = XMPlaneFromPoints(corners[1], corners[5], corners[0]);
	frustum.Planes[4] = XMPlaneFromPoints(corners[5], corners[7], corners[4]);
	frustum.Planes[5] = XMPlaneFromPoints(corners[1], corners[0], corners[3]);
}