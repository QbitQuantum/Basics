void DX11SpriteBatch::BuildSpriteQuad(const Sprite& sprite, MeshData::SpriteVertex v[4])
{
	const CD3D11_RECT& dest = sprite.DestRect;
	const CD3D11_RECT& src  = sprite.SrcRect;

	// Dest rect defines target in screen space.
	v[0].pos = PointToNdc(dest.left,  dest.bottom, sprite.Z);
	v[1].pos = PointToNdc(dest.left,  dest.top,    sprite.Z);
	v[2].pos = PointToNdc(dest.right, dest.top,    sprite.Z);
	v[3].pos = PointToNdc(dest.right, dest.bottom, sprite.Z);

	// Source rect defines subset of texture to use from sprite sheet.
	v[0].tex = Vector2((float)src.left  / mTexWidth, (float)src.bottom / mTexHeight); 
	v[1].tex = Vector2((float)src.left  / mTexWidth, (float)src.top    / mTexHeight); 
	v[2].tex = Vector2((float)src.right / mTexWidth, (float)src.top    / mTexHeight); 
	v[3].tex = Vector2((float)src.right / mTexWidth, (float)src.bottom / mTexHeight); 

	v[0].color = (u32)sprite.Color;
	v[1].color = (u32)sprite.Color;
	v[2].color = (u32)sprite.Color;
	v[3].color = (u32)sprite.Color;

	// Quad center point.
	float tx = 0.5f*(v[0].pos.x + v[3].pos.x);
	float ty = 0.5f*(v[0].pos.y + v[1].pos.y);

	XMVECTOR scaling     = XMVectorSet(sprite.Scale, sprite.Scale, 1.0f, 0.0f);
	XMVECTOR origin      = XMVectorSet(tx, ty, 0.0f, 0.0f);
	XMVECTOR translation = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMMATRIX T           = XMMatrixAffineTransformation2D(scaling, origin, sprite.Angle, translation);

	// Rotate and scale the quad in NDC space.
	for(int i = 0; i < 4; ++i)
	{
		XMFLOAT3 vec = v[i].pos;
		XMVECTOR p = XMLoadFloat3(&vec);
		p = XMVector3TransformCoord(p, T);
		XMStoreFloat3(&vec, p);
		v[i].pos.Set(vec.x, vec.y, vec.z);
	}
}