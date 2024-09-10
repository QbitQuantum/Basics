    void loadMap(sf::Image mapa, std::string s)
    {
        for (int i = 0; i < mapa.getSize().x; i++)
        {
            for (int j = 0; j < mapa.getSize().y; j++)
            {
                if (mapa.getPixel(i, j) == sf::Color(0, 0, 0))
                {
                    tempWall.setPosition(i * tilesize, j * tilesize);
                    spWall.push_back(tempWall);
                }
                else
                {
                    tempGrass.setPosition(i * tilesize, j * tilesize);
                    spGrass.push_back(tempGrass);

                }

                if (mapa.getPixel(i, j) == sf::Color(255,128,0))
                {
                    //   vecChest.push_back(Chest(sf::Vector2f(i*tilesize,j*tilesize),texChest));
                }
                if (mapa.getPixel(i, j) == sf::Color(0, 0, 255))
                {
                    Player.aSprite.setPosition(i * tilesize, j * tilesize);
                }

                if (mapa.getPixel(i, j) == sf::Color(255, 0, 0))
                {
                    vecSkeleton.push_back(Entity(sf::Vector2f(i*tilesize, j*tilesize), &enemySkeleton));
                    vecSkeleton[vecSkeleton.size()-1].aSprite.setScale(5,5);
                    vecSkeleton[vecSkeleton.size()-1].basespeed=2;
                }
            }
        }

        std::ifstream chests;
        chests.open(s);

        int x, y;
        while(chests >> x >> y)
        {
            std::vector <sf::Vector2i> V;
            sf::Vector2i Vi;
            while(1)
            {
                chests >> Vi.x >> Vi.y;
                if(Vi.x==-1)
                    break;
                V.push_back(Vi);
            }
            vecChest.push_back(Chestwo(x,y,V, texChest));
        }
    }