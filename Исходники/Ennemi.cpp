void Ennemi::initCaracteristics()
{

    se::Config* conf = se::Config::getInstance();

    int vitesseMin, vitesseMax = 1;

    if(conf->get(MIN_SPEED,vitesseMin)&&conf->get(MAX_SPEED,vitesseMax))
    {
        std::uniform_int_distribution<> dis(vitesseMin,vitesseMax);

        speed.x = static_cast<float>(dis(gen));
        speed.y = static_cast<float>(dis(gen));
    }
    else
    {
        speed.x = static_cast<float>(dis(gen));
        speed.y = static_cast<float>(dis(gen));
    }

    nspeed = se::Utils::norm(speed);

    sf::RenderWindow& window = se::GraphicEngine::getInstance()->getRenderWindow();

    std::uniform_int_distribution<> disMod(0,3);
    std::uniform_int_distribution<> varMod(0,100);

    float startX = 0;
    float startY = 0;
    int varPart = varMod(gen);

    switch(disMod(gen))
    {
    case 0 :
        startX = varPart;
        startY = -varPart;
        break;
    case 1 :
        startX = window.getSize().x + varPart;
        startY = varPart;
        break;
    case 2 :
        startX = window.getSize().x + varPart;
        startY = window.getSize().y + varPart;
        break;
    case 3 :
        startX = -varPart;
        startY = window.getSize().y +varPart;
        break;
    default :
        ;
        break;
    }

    myEntity->setPosition(startX,startY);

    myEntity->setOrigin(SIZE,SIZE);

    myShadow->setOrigin(SIZE,SIZE);


}