TEST_F(EntityFixture, PlayerTest) {
    GetInput().assignKey(sf::Keyboard::W, Input::Up);
    GetInput().assignKey(sf::Keyboard::A, Input::Left);
    GetInput().assignKey(sf::Keyboard::S, Input::Down);
    GetInput().assignKey(sf::Keyboard::D, Input::Right);
    GetInput().assignMouseButton(sf::Mouse::Left, Input::Shoot);
    GetInput().setMouseLock(true);
    GetWindow().setMouseCursorVisible(false);

    dot.setFillColor(sf::Color::Red);

    // Add behaviors
    playerUpdater = da::BehaviorPtr(new PlayerUpdater(GetView(), GetInput()));
    GetManager().addBehavior(playerUpdater);
    GetManager().addBehavior(velocitiesUpdater);
    GetManager().addBehavior(walker);
    GetManager().addBehavior(poseUpdater);
    GetManager().addBehavior(xformHistorian);

    // Add spatial
    GetRenderer().registerSpatial<SpriteSpatial>();

    // Create entity
    entity = GetManager().create();
    entity->addAttribute(new da::Transform);
    entity->addAttribute(new da::Depth);

    da::TexturePtr texture = GetContent().load<sf::Texture>("mans.png");
    entity->addAttribute(new Sprite(texture));
    entity->addAttribute(new TransformHistory);
    entity->addAttribute(new Collider);
    entity->addAttribute(new Velocities);

    Poses *poses = new Poses;

    Pose pose(6);
    for (unsigned int j = 0; j < DirectionCount; j++) {
        for (unsigned int i = 0; i < pose.getFrameCount(); i++) {
            Pose::Frame frame = {
                sf::IntRect(i * 16, j * 24, 16, 24),
                sf::Vector2f(8, 20)
            };

            pose.setFrame((CardinalDirection)j, i, frame);
        }
    }
    poses->addPose("walk", pose);

    poses->isLoop = true;
    poses->timePerFrame = sf::seconds(0.25f);
    poses->setPose("walk", 0);
    entity->addAttribute(poses);

    Player *player = new Player;
    player->walkSpeed = 100.f;
    player->viewDistance = 40.f;
    entity->addAttribute(player);

    GetManager().refresh(entity);

    Run(update, emptyHandler, draw);
}