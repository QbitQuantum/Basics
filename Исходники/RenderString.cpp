	void RenderString::Render(SpriteFont *spriteFontPtr, SpriteBatch *spriteBatchPtr)
	{
		spriteFontPtr->DrawString(spriteBatchPtr, text.c_str(), XMLoadFloat3(&position), 
			XMLoadFloat4(&color), rotation, XMLoadFloat3(&origin),	XMLoadFloat3(&scale), effects, 
			layerDepth);

	}