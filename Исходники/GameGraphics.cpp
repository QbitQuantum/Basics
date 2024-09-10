void GameGraphics::loadGrassGraphics()
{
	Image grassImage;
	char grassFileName[1024]; game->getStartupPath(grassFileName); strcat_s(grassFileName, GRASS_TEXTURE_PATH);
	grassImage.loadFromFile(grassFileName);

	for (int y = 0; y < game->map.getSize().y; y++)
	{
		for (int x = 0; x < game->map.getSize().x; x++)
		{
			if (game->map.getTile(x,y)->type != TileType::Land)
			{
				grassImage.setPixel(x, y, Color::Transparent);
			}
		}
	}
	grassTexture.loadFromImage(grassImage, IntRect(0, 0, game->map.getSize().x, game->map.getSize().y));
	grassSprite.setTexture(grassTexture, true);
}