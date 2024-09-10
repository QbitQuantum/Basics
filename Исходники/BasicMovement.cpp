int main()
{
    srand(time(NULL));

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Astroides");
    //used for getting the mouse posistion.
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    const int window_height = desktop.height;
    const int window_width = desktop.width;

    window.setFramerateLimit(60);
    sf::Clock clock = sf::Clock();
    sf::Time elapsedTime;

    //BackGround
    sf::Texture backGroundTexture;
    sf::Sprite backGroundSprite;
    backGroundTexture.loadFromFile("Resorces/Img/background.png");
    backGroundSprite.setTexture(backGroundTexture);
    backGroundSprite.setPosition(0, 0);


    //Entities
    Player player = Player();
    EnemyManager eManager;
    ProjectileManager* projectileMgr = ProjectileManager::instance();
    InputManager* inputMgr = InputManager::instance();

    //set up world.
    sf::Vector2f worldBounds = sf::Vector2f(MAP_WIDTH, MAP_HEIGHT);

    int numPacksSwarmers = 10;
    int numSwarmersPerPack = 10;
    int numSwarmerEnemies = numPacksSwarmers * numSwarmersPerPack;
    int numFactories = 20;

    //create some Enemies
    for (int i = 0; i < numPacksSwarmers; i++)
    {
        for (int z = 0; z < numSwarmersPerPack; z++)
        {
            Swarmer * e = new Swarmer((1000 * i), (700 * i)); //Starts all enemy in the center of the screen.
            eManager.addEnemy(e);
        }
    }

    for (int i = 0; i < numFactories; i++)
    {
        Factory * f = new Factory(&eManager);
        eManager.addFactory(f);
    }


    // Start game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event Event;
		
        while (window.pollEvent(Event))
		{
            if (Event.type == Event.KeyPressed && Event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
            switch (Event.type)
            {				
                // Close window : exit
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }//end switch
        }//end while
		InputManager::instance()->UpdatePressedKeys(Event);
	
        player.Update(worldBounds);
        projectileMgr->Update(window);

        //Get the mouse posistion and send it to the swarm method.
        POINT mousePos;
        if (GetCursorPos(&mousePos))
        {
            if (ScreenToClient(window.getSystemHandle(), &mousePos))
            {
                //std::cout << "mouse pos : (" << mousePos.x << ", " << mousePos.y << ")" << std::endl;
                eManager.swarmEAI(player.GetPos());
            }
        }
        //eManager.flocking();
        eManager.CheckCollisions();
        eManager.UpdateFactories(&player);
        eManager.UpdatePredators(player.GetPos());
        eManager.CollisionSwarm(&player);
        eManager.CollisionPred(&player);

        //prepare frame
        window.clear();
        window.setView(player.getView());
        window.draw(backGroundSprite);
        player.Draw(window);
        projectileMgr->Draw(window);
        eManager.Draw(window, worldBounds);

        window.setView(player.getMiniMapView());
        window.draw(backGroundSprite);
        player.Draw(window);
        projectileMgr->Draw(window);
        eManager.Draw(window, worldBounds);

        // Finally, display rendered frame on screen
        window.display();
        clock.restart();
    } //loop back for next frame

    return EXIT_SUCCESS;

}