void RenderPolyWallSprite::Render(const TriMatrix &worldToClip, const PolyClipPlane &clipPlane, AActor *thing, subsector_t *sub, uint32_t subsectorDepth, uint32_t stencilValue)
{
	if (RenderPolySprite::IsThingCulled(thing))
		return;

	const auto &viewpoint = PolyRenderer::Instance()->Viewpoint;
	DVector3 pos = thing->InterpolatedPosition(viewpoint.TicFrac);
	pos.Z += thing->GetBobOffset(viewpoint.TicFrac);

	bool flipTextureX = false;
	FTexture *tex = RenderPolySprite::GetSpriteTexture(thing, flipTextureX);
	if (tex == nullptr || tex->UseType == FTexture::TEX_Null)
		return;

	DVector2 spriteScale = thing->Scale;
	double thingxscalemul = spriteScale.X / tex->Scale.X;
	double thingyscalemul = spriteScale.Y / tex->Scale.Y;
	double spriteHeight = thingyscalemul * tex->GetHeight();

	DAngle ang = thing->Angles.Yaw + 90;
	double angcos = ang.Cos();
	double angsin = ang.Sin();

	// Determine left and right edges of sprite. The sprite's angle is its normal,
	// so the edges are 90 degrees each side of it.
	double x2 = tex->GetScaledWidth() * spriteScale.X;
	double x1 = tex->GetScaledLeftOffset() * spriteScale.X;
	DVector2 left, right;
	left.X = pos.X - x1 * angcos;
	left.Y = pos.Y - x1 * angsin;
	right.X = left.X + x2 * angcos;
	right.Y = left.Y + x2 * angsin;

	//int scaled_to = tex->GetScaledTopOffset();
	//int scaled_bo = scaled_to - tex->GetScaledHeight();
	//gzt = pos.Z + scale.Y * scaled_to;
	//gzb = pos.Z + scale.Y * scaled_bo;

	DVector2 points[2] = { left, right };

	TriVertex *vertices = PolyRenderer::Instance()->FrameMemory.AllocMemory<TriVertex>(4);

	bool foggy = false;
	int actualextralight = foggy ? 0 : viewpoint.extralight << 4;

	std::pair<float, float> offsets[4] =
	{
		{ 0.0f,  1.0f },
		{ 1.0f,  1.0f },
		{ 1.0f,  0.0f },
		{ 0.0f,  0.0f },
	};

	for (int i = 0; i < 4; i++)
	{
		auto &p = (i == 0 || i == 3) ? points[0] : points[1];

		vertices[i].x = (float)p.X;
		vertices[i].y = (float)p.Y;
		vertices[i].z = (float)(pos.Z + spriteHeight * offsets[i].second);
		vertices[i].w = 1.0f;
		vertices[i].u = (float)(offsets[i].first * tex->Scale.X);
		vertices[i].v = (float)((1.0f - offsets[i].second) * tex->Scale.Y);
		if (flipTextureX)
			vertices[i].u = 1.0f - vertices[i].u;
	}

	bool fullbrightSprite = ((thing->renderflags & RF_FULLBRIGHT) || (thing->flags5 & MF5_BRIGHT));
	int lightlevel = fullbrightSprite ? 255 : thing->Sector->lightlevel + actualextralight;

	PolyDrawArgs args;
	args.SetLight(GetColorTable(sub->sector->Colormap, sub->sector->SpecialColors[sector_t::sprites], true), lightlevel, PolyRenderer::Instance()->Light.WallGlobVis(foggy), fullbrightSprite);
	args.SetTransform(&worldToClip);
	args.SetFaceCullCCW(true);
	args.SetStencilTestValue(stencilValue);
	args.SetTexture(tex);
	args.SetClipPlane(clipPlane);
	args.SetSubsectorDepthTest(true);
	args.SetWriteSubsectorDepth(false);
	args.SetWriteStencil(false);
	args.SetStyle(TriBlendMode::TextureMasked);
	args.DrawArray(vertices, 4, PolyDrawMode::TriangleFan);
}