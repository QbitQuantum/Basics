//-----------------------------------------------------------------------------------------------------------------------------------
void GameMouse::Draw(SpriteBatch* spriteBatch, SpriteFont* spriteFont)
{
	if (IsVisible())
	{
		spriteBatch->Draw(
			GetTexture()->GetTexture(), 
			GetWorldPosition(), 
			nullptr, 
			GetColour() * GetOpacity(),
			GetWorldRotation(), 
			Vector2::Zero, 
			XMVectorDivide(GetSize(), GetTexture()->GetDimensions()));
	}
}