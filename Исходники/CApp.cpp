int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The background scrolling offset
            int scrollingOffset = 0;

			//Angle of rotation
			double degrees = 0;

			//The dot that will be moving around on the screen
			Dot dot ( 100, 300);

			//Opening Fonts and message
			TTF_Font *times;
			times = TTF_OpenFont("arial.ttf", 14);

			SDL_Color white = {255, 255, 255};
			
			std::stringstream health;
			health <<"Health:" << dot.hp << "    Points: " << POINTS;

			const std::string str = health.str();

			SDL_Surface *surface = TTF_RenderText_Solid(times,
									health.str().c_str(), white);


			 SDL_Texture * texture = SDL_CreateTextureFromSurface(gRenderer,
					 surface);

			  int texW = 0;
			  int texH = 0;
			  SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
			  SDL_Rect dstrect = { 0, 0, texW, texH };

			
			//creating enemies
			std::vector<Enemy*> enemies;

			for (int i = 0; i < NumberEnemies; i++)
			{
				enemies.push_back(new Enemy(i*100, 0));
			}
			
			//Flip type
			SDL_RendererFlip flipType = SDL_FLIP_NONE;

			//While application is running
			while( !quit)
			{

				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
				if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					dot.handleEvent(e);
				}

				//rotating
					degrees += 1;


					//collision between enemies and bullets
				for (int i = 0; i < enemies.size(); i++)
				{
					for (int j = 0; j < bulletsUp.size(); j++)
					{
						enemies[i]->move(bulletsUp[j]->getColliders());
					}

					for (int j = 0; j < bulletsLeft.size(); j++)
					{
						enemies[i]->move(bulletsLeft[j]->getColliders());
					}

					for (int j = 0; j < bulletsRight.size(); j++)
					{
						enemies[i]->move(bulletsRight[j]->getColliders());
					}

					enemies[i]->move(dot.getColliders());

					enemies[i]->shoot(enemies[i]->mPosX, enemies[i]->mPosY);

					dot.move( enemies[i]->getColliders());
				}


				//moving of bullets
				for (int i = 0; i < bulletsUp.size(); i++)
				{
					bulletsUp[i]->moveUp(dot.getColliders());
				}

				for (int i = 0; i < bulletsLeft.size(); i++)
				{
					bulletsLeft[i]->moveLeft(dot.getColliders());
				}

				for (int i = 0; i < bulletsRight.size(); i++)
				{
					bulletsRight[i]->moveRight(dot.getColliders());
				}

				for (int i = 0; i < enemyBullets.size(); i++)
				{
					enemyBullets[i]->enemyMove(dot.getColliders());
				}

				//Scroll background
                --scrollingOffset;
                if( scrollingOffset < -gBGTexture.getWidth() )
                {
                    scrollingOffset = 0;
                }

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				SDL_RenderClear( gRenderer );

				//Render background
                gBGTexture.render( scrollingOffset, 0 );
				SDL_RenderCopy(gRenderer, texture, NULL, &dstrect);
                gBGTexture.render( scrollingOffset + gBGTexture.getWidth(), 0 );

				//Render Dot
				dot.render();

				//displaying enemeies and bullets
				for (int i = 0; i < enemies.size(); i++)
				{
					enemies[i]->render(degrees,flipType);
				}

				for (int i = 0; i < bulletsUp.size(); i++)
				{
					bulletsUp[i]->render();
				}

				for (int i = 0; i < bulletsLeft.size(); i++)
				{
					bulletsLeft[i]->render();
				}

				for (int i = 0; i < bulletsRight.size(); i++)
				{
					bulletsRight[i]->render();
				}

				for (int i = 0; i < enemyBullets.size(); i++)
				{
					enemyBullets[i]->render();
				}

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}