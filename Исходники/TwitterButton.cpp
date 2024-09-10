void TwitterButton::drawClicked(RoundRect shape, String const &text, int frame)const
{
	static Point clickPoint;
	if (frame <= 1) {
		clickPoint = Mouse::Pos();
	}
	shape.draw(HSV(0, 0.0, 0.85));
	//FontAsset(FONT_ASSET_NAME).drawCenter(text, shape.rect.center, Palette::Black);
	TextureAsset(L"twitterIcon").scale(0.07).drawAt(shape.rect.center);
}