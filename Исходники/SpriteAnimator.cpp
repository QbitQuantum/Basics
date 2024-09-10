SpriteAnimator::SpriteAnimator(string file, int numberOfSprites, float fps)
{
	nSprites = numberOfSprites;
	loadSprites(file);

	Sprite* sprite = new Sprite();
	sprite->initWithTexture(sprites[0]);
	image = new CentSprite(sprite, 0, 0, 0, 0);

	internalTimer = CatacombTimer(1 / fps);

	initialPosition = Vector2F(0, 0);
}