void TextureResourceLoader::divideMapchipGraphs(const Image& baseImage)
{
	const auto mcSize = Vec2(17.0, 17.0);

	this->mcTop			= Texture(clipImage(baseImage, RectF(Vec2(5.0, 5.0), mcSize), tsTransColor));
	this->mcRoad		= Texture(clipImage(baseImage, RectF(Vec2(5.0 + 20.0, 5.0), mcSize), tsTransColor));
	this->mcGrass		= Texture(clipImage(baseImage, RectF(Vec2(5.0 + 40.0, 5.0), mcSize), tsTransColor));
	this->mcGrassUnder	= Texture(clipImage(baseImage, RectF(Vec2(5.0 + 60.0, 5.0), mcSize), tsTransColor));
	this->mcUnder		= Texture(clipImage(baseImage, RectF(Vec2(5.0 + 80.0, 5.0), mcSize), tsTransColor));
}