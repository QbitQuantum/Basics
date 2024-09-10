    void MapLevel::loadLevel(std::size_t level, sf::Image& levelData)
    {
        LOG_CALL("MapLevel::loadLevel");
        int imageX0 = level * LevelWidth;
        int imageY0 = 0;

        sf::Vector2u dataSize = levelData.getSize();
        LOG_DEBUG("LevelData size: %d, %d", dataSize.x, dataSize.y);

        mVertices.setPrimitiveType(sf::Quads);
        mVertices.resize(LevelWidth * LevelHeight * 4);


        for (std::size_t j = 0; j < LevelHeight; ++j) {
            for (std::size_t i = 0; i < LevelWidth; ++i) {
                int imageX = imageX0 + i;
                int imageY = imageY0 + j;

                Tile tile = getTileFromColor(levelData.getPixel(imageX, imageY));
                mWorld[i][j] = tile;

                if (tile == Tile::Wall) {
                    sf::Vector2i texCoords = getTexCoords(tile);
                    sf::Vertex* quad = &mVertices[(i + j * LevelWidth) * 4];
                    int tu = texCoords.x;
                    int tv = texCoords.y;

                    int left = WorldOffsetX + i * TileWidth;
                    int top = WorldOffsetY + j * TileHeight;
                    int right = WorldOffsetX + (i + 1) * TileWidth;
                    int bottom = WorldOffsetY + (j + 1) * TileHeight;

                    // Define 4 corners of vertice
                    quad[0].position = sf::Vector2f(left, top);
                    quad[1].position = sf::Vector2f(right, top);
                    quad[2].position = sf::Vector2f(right, bottom);
                    quad[3].position = sf::Vector2f(left, bottom);

                    quad[0].texCoords = sf::Vector2f(tu * TileWidth, tv * TileHeight);
                    quad[1].texCoords = sf::Vector2f((tu + 1) * TileWidth, tv * TileHeight);
                    quad[2].texCoords = sf::Vector2f((tu + 1) * TileWidth, (tv + 1) * TileHeight);
                    quad[3].texCoords = sf::Vector2f(tu * TileWidth, (tv + 1) * TileHeight);

                    // Register wall in Box2D
                    b2utils::createGround(mBoxWorld, (left + right) / 2, (top + bottom) / 2, TileWidth, TileHeight);

                } else if (tile == Tile::PlayerSpawn) {
                    mPlayerSpawnPos.x = i;
                    mPlayerSpawnPos.y = j;

                } else if (tile == Tile::DestinationSpawn) {
                    mDestinationList.push_back(Position(i, j));

                } else if (tile == Tile::SourceSpawn) {
                    mSourceList.push_back(Position(i, j));
                }
            }
        }
    }