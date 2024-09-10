int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Roboprototype");
	sf::Event e;
	window.setFramerateLimit(60);
	bool in_focus = true; //if false, the window won't update

	//world setup
	Timer fps_clock; //used to determine the fps
	b2Vec2 gravity(0.0, -20.0f); //current gravity for the world
	b2World *world = new b2World(gravity);
	world->SetAllowSleeping(true); //allows particles to come to rest
	float32 time_step = 1.0 / 60.0; //the length of time passed to simulate (seconds)
	int32 velocity_iterations = 7; //how strongly to correct the velocity
	int32 position_iterations = 3; //how strongly to correct the position
	
	//background setup
	sf::Texture background_texture;
	sf::Sprite background_sprite;

	if(!background_texture.loadFromFile("images//background2.png") )
	{
		printf("Failed to load background image on line %d \n", __LINE__);
		window.close();
	}
	
	background_sprite.setTexture( background_texture );

	sf::Vector2f center_pos(window.getSize().x / 2.0, window.getSize().y / 2.0);
	sf::Vector2f view_size(window.getSize().x, window.getSize().y);
	sf::Vector2f level_size(background_texture.getSize().x, background_texture.getSize().y);
	Camera main_view(center_pos, view_size, level_size);

	//game mode setup(live/editor)
	//PUT EVERYTHING EXCEPT THE EDITOR INSIDE THE EDITOR CLASS
	Editor editor; //used to store all objects and edit the level
	int game_state = Editor::GAME_STATE::LIVE; //current mode
	Timer editor_clock;
	Timer game_mode_clock;
	sf::Font font;
	sf::Text game_mode_text; //used to display the current game mode
	sf::Text editor_object_type; //used to display the current type of object in the editor mode
	string game_mode_live = "Mode: Live";
	string game_mode_editor = "Mode: Editor";
	string editor_type[3] = {"Object Type: Static", "Object Type: Dynamic", "Object Type: Kinematic"};
	sf::Vector2i game_mode_text_pos(10, 10); 
	

	if(!font.loadFromFile("fonts//amatic.ttf") )
	{
		printf("Failed to load font on line %d \n", __LINE__);
		window.close();
	}

	game_mode_text.setFont(font);
	game_mode_text.setString( (game_state == Editor::GAME_STATE::LIVE) ? game_mode_live : game_mode_editor );
	game_mode_text.setCharacterSize(50);
	game_mode_text.scale( window.getSize().x / 1600.0, window.getSize().y / 900); //scales based on the window size it was created on
	game_mode_text.setPosition(game_mode_text_pos.x, game_mode_text_pos.y);
	game_mode_text.setColor( sf::Color(0, 0, 0) );

	editor_object_type.setFont(font);
	editor_object_type.setString( editor_type[editor.getObjectType()] );
	editor_object_type.setCharacterSize(50);
	editor_object_type.scale(window.getSize().x / 1600.0, window.getSize().y / 900); //scales based on the window size it was created on
	editor_object_type.setColor( sf::Color(0, 0, 0) );
	sf::Vector2i editor_object_pos( game_mode_text_pos.x, game_mode_text_pos.y + editor_object_type.getGlobalBounds().height * 1.5 );
	editor_object_type.setPosition( window.mapPixelToCoords(editor_object_pos) );

	//mouse setup
	Timer mouse_clock;
	sf::Vector2i mouse_pos;
	sf::Vector2f mouse_pos_world; //world coordinates for the current mouse position

	//particles///////////
	bool particle_toggle = true; //if true, particles are constantly created
	sf::CircleShape particle_shape;
	particle_shape.setFillColor( sf::Color(255, 255, 255, 180) );
	particle_shape.setOutlineThickness(3);
	particle_shape.setOutlineColor( sf::Color(255, 0, 0, 150) );
	particle_shape.setRadius(3);
	particle_shape.setOrigin( particle_shape.getRadius(), particle_shape.getRadius() );

	b2ParticleSystem *particle_system; //the world the particles inhabit
	b2ParticleSystemDef particle_system_def;
	b2ParticleDef *particle_def = new b2ParticleDef; //definition of an individual particle

	particle_system_def.density = 1;
	particle_system_def.radius = (particle_shape.getRadius() + (particle_shape.getOutlineThickness() / 2.0) ) * PIXELS_TO_METERS;
	particle_system_def.maxCount = 500; //maximum number of particles on the screen

	particle_system = world->CreateParticleSystem(&particle_system_def); //creates the particle system to hold all the particles
	particle_system->SetRadius( particle_shape.getRadius() );
	particle_system->SetDestructionByAge(true); //particles are automatically destroyed based on their age
	particle_system->SetGravityScale(50.0);	
	
	particle_def->lifetime = 0.25; //number of seconds particle will stay alive
	particle_def->color.Set(0, 255, 255, 255);
	particle_def->flags = b2_elasticParticle;
	particle_def->position.Set( window.getSize().x / 2.0, window.getSize().y / 2.0 );
	//end particles////////////////////////////////////	

	//creates kinematic platform boundaries
	mouse_pos_world.x = -50.0;
	mouse_pos_world.y = window.getSize().y / 1.35;
	sf::Vector2f left_boundary(0.0, mouse_pos_world.y);
	sf::Vector2f right_boundary(background_texture.getSize().x, mouse_pos_world.y);

	//player setup
	b2FixtureDef fixture;
	sf::Vector2f player_speed = sf::Vector2f(400.0, 600.0);
	Timer player_clock;
	Timer player_jump_clock;
	sf::Texture player_texture;

	if(!player_texture.loadFromFile("images//player.png") )
	{
		printf("Error %d : Failed to load player texture.\n", __LINE__);
		return -1;
	}

	fixture.restitution = 0.1;
	fixture.friction = 1.0;
	fixture.density = 2.0;
	Object player(window, world, fixture, player_texture, -1, Editor::BODY_TYPE::DYNAMIC, POLY_SHAPE);
	player.getBody()->SetFixedRotation(true);
	
	string file = "level1.txt";
	editor.loadFile(window, world, player, file);

    while (window.isOpen())
    {
		window.setView( *(main_view.getView()) );

        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();

			else if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
				window.close();

			else if(e.type == sf::Event::LostFocus)
				in_focus = false;

			else if(e.type == sf::Event::GainedFocus)
				in_focus = true;

			else if(e.type == sf::Event::MouseWheelMoved)
				main_view.zoomControl(window, e);
			
        }

		if(in_focus == true)
		{
			editor_clock.update();

			//checks for game mode change
			game_mode_clock.update();
			editor.gameModeToggle(game_mode_text, game_mode_clock, game_mode_live, game_mode_editor, game_state);

			//update mouse position
			mouse_clock.update();
			updateMousePos(mouse_pos, mouse_pos_world, window);

			if(game_state == Editor::GAME_STATE::LIVE) //if you're in live mode
			{
				main_view.boundaryControl(player.getSprite()->getPosition()); //camera follows player in live mode

				//update clocks
				player_clock.update();
				player_jump_clock.update();				

				//checks for player commands
				playerCommandUpdate(player_clock, player_jump_clock, player_speed, player);

				//update world
				world->Step(time_step, velocity_iterations, position_iterations);
			
				particleToggle(player, mouse_clock, particle_toggle, particle_def, particle_system);
				Object::updatePosition(player); //updates the player sprite
				Object::updatePosition(editor.getDynamicObjects()); //updates the sprite position of the dynamic objects
				Object::updatePosition(editor.getKinematicObjects()); //updates the sprite position of the kinematic objects
				Physics::kinematicBoundaries(left_boundary, right_boundary, editor.getKinematicObjects());
			}

			else if(game_state == Editor::GAME_STATE::EDITOR) //if you're in editor mode
			{
				main_view.boundaryControl(mouse_pos_world); //camera follows mouse in edit mode
				//determines how to place objects to the screen in editor mode
				editor.keyboardActionCommands(window, world, player, mouse_clock, editor_object_type, mouse_pos_world, editor_type); 
				editor.keyboardCycleCommands(editor_clock); //used to cycle through objects in editor mode
			}			
			 
			window.clear(sf::Color(187, 255, 255) ); 

			window.draw( background_sprite );
			Draw::drawParticles(window, particle_shape, particle_system);
			Draw::draw( window, editor.getStaticObjects() ); //draws all the static objects to the screen
			Draw::draw( window, editor.getDynamicObjects() ); //draws all the dynamic objects to the screen
			Draw::draw( window, editor.getKinematicObjects() ); //draws all the kinematic objects to the screen
			Draw::draw( window, player ); //draws the player to the screen
			Draw::drawText(window, game_mode_text, game_mode_text_pos);	//draws live/editor text to the screen		
			
			if(game_state == Editor::GAME_STATE::EDITOR) //draws editor only stuff
			{
				Draw::drawEditor(window, editor, mouse_pos_world, editor_object_type, editor_object_pos, game_state);
			}
			
			window.display();
		}        
    }
	
    return 0;
}