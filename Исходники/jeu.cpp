int Jeu::start(short niveau)
{
    SoundBuffer musicBuffer = sound_manager::getInstance()->getBuffer("son/acronis.ogg");
    musicSound.SetBuffer(musicBuffer);
    musicSound.SetLoop(true);
    musicSound.SetPitch(1.f);
    musicSound.SetVolume(50.f);
    musicSound.Play();


    clicBuffer = sound_manager::getInstance()->getBuffer("son/clic.ogg");
    clicSound.SetBuffer(clicBuffer);
    clicSound.SetLoop(false);
    clicSound.SetPitch(1.f);
    clicSound.SetVolume(50.f);

    bool invincible(false);
    int invincibleStart;
    Timer timer;

    //Variables :
    const int PANNEL_WIDTH(300);
    const Input & input = app.GetInput();

    //gestionnaires de projectiles
    Projectile_manager *projectile_manager;
    projectile_manager = Projectile_manager::getInstance();

    //Affichage onscreen des scores
    Score_manager *scoreManager;
    scoreManager = Score_manager::getInstance();

    //Variables player :
    Vector2f positionPlayer(m_SCREEN_WIDTH/2 -50, m_SCREEN_HEIGHT - 100);

    std::tr1::shared_ptr<Player> player(new Player(0, 1, positionPlayer));
    std::tr1::shared_ptr<Player> player2(new Player(1, 1,positionPlayer));
    player->addScore(scorePlayer1);
    player2->addScore(scorePlayer2);

    Drop_manager *drop_manager;
    drop_manager = Drop_manager::getInstance();
    //Variable population
    Population *population;
    population = Population::getInstance();
    population->setPlayer(player, player2);

    Level_manager *level_manager;
    level_manager = Level_manager::getInstance();

    //gestionnaires de missiles
    Missile_manager *missile_manager;
    missile_manager = Missile_manager::getInstance();
    missile_manager->setPlayer(player);

    //Activateur d'armes
    Weapon_manager *weapon_manager;
    weapon_manager = Weapon_manager::getInstance();
    weapon_manager->setParams(player, player2);

    //pannel
    const string filepathPanel = "images/pannel.png";
    Vector2f positionPannel(m_SCREEN_WIDTH-PANNEL_WIDTH-30, 100);
    Pannel pannel(filepathPanel, positionPannel, player, player2);

    //Collision
    Vector2f windowSize(m_SCREEN_WIDTH-PANNEL_WIDTH, m_SCREEN_HEIGHT);
    Collision collision(windowSize, player, player2);

    //Background
    Background background(1, m_SCREEN_WIDTH, m_SCREEN_HEIGHT, app);

    Level_manager::getInstance()->startLevel(niveau);
    while (app.IsOpened() )
    {
        if(hasQuitCondition(player, player2, m_quit))
        {
            int state = 0;
            if(level_manager->isFinished() && !population->haveEnnemyInProgress())
            {
                if(!Level_manager::getInstance()->endOfGame())
                    this->saveDatas(player, player2);
                m_menu.setLevel(level_manager->getLevelNumber() + 1);
                state = 1;
            }
            else
                Level_manager::getInstance()->setGameOver();
            drop_manager->reset();
            population->reset();
            weapon_manager->reset();
            missile_manager->reset();
            scoreManager->reset();
            projectile_manager->reset();
            m_quit = false;
            return state;
        }
        if(player->isDead() && player2->isDead())
        {
            Level_manager::getInstance()->setGameOver();
            m_quit = true;
        }
        app.Clear();
        background.manage();
        //Entrées touches :
        Event Event;
        while (app.GetEvent(Event))
        {
            if (Event.Type == sf::Event::Closed)
                app.Close();
        }
        //Déplacements :
        if(!player->isDead())
        {
            if(input.IsKeyDown(Key::R))
            {
                player->moveUp();
                collision.manageCollisionsY();
            }
            else if(input.IsKeyDown(Key::F))
            {
                player->moveDown();
                collision.manageCollisionsY();
            }
            if(input.IsKeyDown(Key::D))
            {
                player->moveRight();
                collision.manageCollisionsX();
            }
            else if(input.IsKeyDown(Key::G))
            {
                player->moveLeft();
                collision.manageCollisionsX();
            }
            if(!(input.IsKeyDown(Key::R))&&!(input.IsKeyDown(Key::F))&&!(input.IsKeyDown(Key::D))&&!(input.IsKeyDown(Key::G)))
            {
                player->dontMove();
                collision.manageCollisionsX();
                collision.manageCollisionsY();
            }
            if(input.IsKeyDown(Key::A))
            {
                //population->freeze();
            }
            if(input.IsKeyDown(Key::Z))
            {
                player->fire0();
            }
            if(input.IsKeyDown(Key::P))
            {
                Weapon_manager::getInstance()->changeWeapon(player);
            }
        }
        if(!player2->isDead())
        {
            if(input.IsKeyDown(Key::Up))
            {
                player2->moveUp();
                collision.manageCollisionsY2();
            }
            else if(input.IsKeyDown(Key::Down))
            {
                player2->moveDown();
                collision.manageCollisionsY2();
            }
            if(input.IsKeyDown(Key::Right))
            {
                player2->moveRight();
                collision.manageCollisionsX2();
            }
            else if(input.IsKeyDown(Key::Left))
            {
                player2->moveLeft();
                collision.manageCollisionsX2();
            }
            if(!(input.IsKeyDown(Key::R))&&!(input.IsKeyDown(Key::D))&&!(input.IsKeyDown(Key::F))&&!(input.IsKeyDown(Key::G)))
            {
                player2->dontMove();
                collision.manageCollisionsX2();
                collision.manageCollisionsY2();
            }
            if(input.IsKeyDown(Key::LShift))
            {
                player2->fire1();
            }
            if(input.IsKeyDown(Key::M))
            {
                //Weapon_manager::getInstance()->changeWeapon(player2);
            }
            if(input.IsKeyDown(Key::H))
            {   /*
                   if(player2->getPlayerKTA())
                   {
                       population->killThemAll();
                       Projectile_manager::getInstance()->killThemAll();
                       player2->setPlayerKTA(false);
                   }*/
            }
        }
        if(input.IsKeyDown(Key::Num2))
        {
            population->stop();
            this->pause(Event, pannel, player, player2);
            population->unStop();
        }
        if(Projectile_manager::getInstance()->havePlayerProjectilesInProgress() || Missile_manager::getInstance()->haveMissilesInProgress() || Projectile_manager::getInstance()->haveEnemyProjectilesInProgress())
        {
            collision.manageProjectileCollision();
        }

        if(player->getLostlife() ||player2->getLostlife())
        {
            if(!invincible)
            {
                timer.start();
                invincibleStart = timer.getTime();
                invincible = true;
            }
            else if(timer.getTime() - invincibleStart > 4 )
            {
                player->resetLostLife();
                player2->resetLostLife();
                invincible = false;
            }
        }
        //Cheat_manager::getInstance()->checkKonami();
        level_manager->checkLevel();
        weapon_manager->manage();
        drop_manager->manage();
        player->draw();
        player2->draw();
        population->manage();
        missile_manager->manage();
        pannel.checkPannel();
        scoreManager->manage();
        app.Display();
        timer.sleep(1);
    }

}