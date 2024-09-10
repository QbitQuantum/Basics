sf::Vector2f EntityWithWeapon::searchhotspot(sf::Image tmpimg)
{

            sf::Vector2f turret_pos;
//Recherche des pixels de centrage
  for(unsigned int i=0; i<tmpimg.getSize().x; i++)
    {
      for(unsigned int j=0; j<tmpimg.getSize().y; j++)
        {
          sf::Color tmpcolor = tmpimg.getPixel(i, j);
          if(tmpcolor==sf::Color(255,0,0))//Affection de la position de la turret
            {
              turret_pos.x=i;
              turret_pos.y=j;
            }
        }
    }

    return turret_pos;
}