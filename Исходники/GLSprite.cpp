bool GLSprite::DrawShaped(
	const math::Vector2 &v2Pos,
	const math::Vector2 &v2Size,
	const Color& color0,
	const Color& color1,
	const Color& color2,
	const Color& color3,
	const float angle)
{
	if (v2Size == math::Vector2(0,0))
	{
		return true;
	}

	// compute flip parameters that will be sent to the VS
	math::Vector2 flipMul, flipAdd;
	GetFlipShaderParameters(flipAdd, flipMul);

	// centralizes the sprite according to the origin
	math::Vector2 v2Center = m_normalizedOrigin * v2Size;

	GLVideo* video = m_video.lock().get();
	ShaderPtr pCurrentVS = video->GetVertexShader();

	math::Matrix4x4 mRot;
	if (angle != 0.0f)
		mRot = math::RotateZ(math::DegreeToRadian(angle));
	pCurrentVS->SetMatrixConstant("rotationMatrix", mRot);

	// rounds up the final position to avoid alpha distortion
	math::Vector2 v2FinalPos;
	if (video->IsRoundingUpPosition())
	{
		v2FinalPos.x = floor(v2Pos.x);
		v2FinalPos.y = floor(v2Pos.y);
	}
	else
	{
		v2FinalPos = v2Pos;
	}

	pCurrentVS->SetConstant("size", v2Size);
	pCurrentVS->SetConstant("entityPos", v2FinalPos);
	pCurrentVS->SetConstant("center", v2Center);
	pCurrentVS->SetConstant("flipMul", flipMul);
	pCurrentVS->SetConstant("flipAdd", flipAdd);
	pCurrentVS->SetConstant("bitmapSize", GetBitmapSizeF());
	pCurrentVS->SetConstant("scroll", GetScroll());
	pCurrentVS->SetConstant("multiply", GetMultiply());

	const bool setCameraPos = pCurrentVS->ConstantExist("cameraPos");
	if (setCameraPos)
		pCurrentVS->SetConstant("cameraPos", video->GetCameraPos());

	if (m_rect.size.x == 0 || m_rect.size.y == 0)
	{
		pCurrentVS->SetConstant("rectSize", GetBitmapSizeF());
		pCurrentVS->SetConstant("rectPos", 0, 0);
	}
	else
	{
		pCurrentVS->SetConstant("rectSize", m_rect.size);
		pCurrentVS->SetConstant("rectPos", m_rect.pos);
	}

	pCurrentVS->SetConstant("color0", color0);
	pCurrentVS->SetConstant("color1", color1);
	pCurrentVS->SetConstant("color2", color2);
	pCurrentVS->SetConstant("color3", color3);

	if (pCurrentVS->ConstantExist("depth"))
		pCurrentVS->SetConstant("depth", video->GetSpriteDepth());

	// apply textures according to the rendering mode (pixel shaded or not)
	ShaderPtr pCurrentPS = video->GetPixelShader();
	SetDiffuseTexture(pCurrentPS);

	pCurrentVS->SetShader();

	// draw the one-pixel-quad applying the vertex shader
	video->GetRectRenderer().Draw(m_rectMode);

	return true;
}