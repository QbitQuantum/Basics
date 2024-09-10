	TexturedQuad TextureRegion::rotated(const double angle) const
	{
		return TexturedQuad(texture,
			uvRect,
			RectF(size).rotated(angle),
			size * 0.5f);
	}