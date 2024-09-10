	void CoreLayer2D_Imp::DrawRectangleAdditionally(RectF drawingArea, Color color, RectF uv, Texture2D* texture, AlphaBlendMode alphaBlend, int32_t priority)
	{
		Sprite sprite;

		std::array<Color, 4> col = { color, color, color, color };

		SafeAddRef(texture);

		sprite.pos = drawingArea.GetVertexes();
		sprite.col = col;
		sprite.uv = uv.GetVertexes();
		sprite.Texture_ = CreateSharedPtrWithReleaseDLL(texture);
		sprite.AlphaBlend_ = alphaBlend;
		sprite.Priority = priority;

		sprites.push_back(sprite);
	}