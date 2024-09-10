bool GameMob::CollisionGeneral(const sf::FloatRect entityRect){
    int maxHeight, minHeight, maxWidth, minWidth;
    minHeight=entityRect.Top/GameConfig::g_config["tileheight"];
    minWidth=entityRect.Left/GameConfig::g_config["tilewidth"];
    maxHeight=(entityRect.Top+entityRect.Height-1)/GameConfig::g_config["tileheight"];
    maxWidth=(entityRect.Left+entityRect.Width-1)/GameConfig::g_config["tilewidth"];

    if(minHeight<0)minHeight=0;
    if(maxHeight>(*m_map)->m_height)maxHeight=(*m_map)->m_height;
    if(minWidth<0)minWidth=0;
    if(maxWidth>(*m_map)->m_width)maxWidth=(*m_map)->m_width;

    for(int y=minHeight;y<=maxHeight;y++){
        for(int x=minWidth;x<=maxWidth;x++){
            if((*m_map)->Tile(x,y).solid){
                sf::FloatRect  theTile(x*GameConfig::g_config["tilewidth"],y*GameConfig::g_config["tileheight"],GameConfig::g_config["tilewidth"],GameConfig::g_config["tileheight"]);
                if(entityRect.Intersects(theTile)||theTile.Intersects(entityRect)){
                    if((*m_map)->Tile(x,y).boomer && (*m_map)->Tile(x,y).color==GameConfig::ColorToNbr(GetColor()))(*m_map)->Explode(x,y);
                    return true;
                }
            }
        }
    }
    return false;
 }