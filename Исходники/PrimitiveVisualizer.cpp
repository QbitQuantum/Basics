	void XM_CALLCONV PrimitveDrawer::DrawCylinder(FXMVECTOR P1, FXMVECTOR P2, float radius, FXMVECTOR Color)
	{
		auto center = 0.5f * XMVectorAdd(P1, P2);
		auto dir = XMVectorSubtract(P1, P2);
		auto scale = XMVector3Length(dir);
		scale = XMVectorSet(radius, XMVectorGetX(scale), radius, 1.0f);
		XMVECTOR rot;
		if (XMVector4Equal(dir, g_XMZero))
			rot = XMQuaternionIdentity();
		else
			rot = XMQuaternionRotationVectorToVector(g_XMIdentityR1, dir);
		XMMATRIX world = XMMatrixAffineTransformation(scale, g_XMZero, rot, center);
		m_pCylinder->Draw(world, ViewMatrix, ProjectionMatrix, Color);
	}