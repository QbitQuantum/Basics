/*Foo::Foo()
{
          offSet = 0;
          velocity = 0;
          
          frame = 0;
          status = FOO_RIGHT;
}
void Foo::move()
{
     offSet += velocity;
     
     if( ( offSet < 0 ) || ( offSet + FOO_WIDTH > SCREEN_WIDTH ) )
         offSet -= velocity;
}
void Foo::show()
{
     if( velocity < 0 )
     {
         status = FOO_LEFT;
         
         frame++;
     }
     else if( velocity > 0 )
     {
          status = FOO_RIGHT;
          
          frame++;
     }
     else
         frame = 0;
         
     if( frame >= 4 )
         frame = 0;
         
     if( status == FOO_RIGHT )
         apply_surface( offSet, SCREEN_HEIGHT - FOO_HEIGHT, foo, screen, &clipsRight[frame] );
     else if( status == FOO_LEFT )
          apply_surface( offSet, SCREEN_HEIGHT - FOO_HEIGHT, foo, screen, &clipsLeft[frame] );
}
void Foo::handle_events()
{
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Set the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_RIGHT: velocity += FOO_WIDTH / 4; break;
            case SDLK_LEFT: velocity -= FOO_WIDTH / 4; break;
        }
    }
    //If a key was released
    else if( event.type == SDL_KEYUP )
    {
        //Set the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_RIGHT: velocity -= FOO_WIDTH / 4; break;
            case SDLK_LEFT: velocity += FOO_WIDTH / 4; break;
        }
    }
}

void set_clips()
{
     //clip the sprite sheet
     clipsRight[0].x = 0;
     clipsRight[0].y = 0;
     clipsRight[0].w = FOO_WIDTH;
     clipsRight[0].h = FOO_HEIGHT;
     
     clipsRight[1].x = FOO_WIDTH;
     clipsRight[1].y = 0;
     clipsRight[1].w = FOO_WIDTH;
     clipsRight[1].h = FOO_HEIGHT;
     
     clipsRight[2].x = FOO_WIDTH * 2;
     clipsRight[2].y = 0;
     clipsRight[2].w = FOO_WIDTH;
     clipsRight[2].h = FOO_HEIGHT;
     
     clipsRight[3].x = FOO_WIDTH * 3;
     clipsRight[3].y = 0;
     clipsRight[3].w = FOO_WIDTH;
     clipsRight[3].h = FOO_HEIGHT;
     
     clipsLeft[0].x = 0;
     clipsLeft[0].y = FOO_HEIGHT;
     clipsLeft[0].w = FOO_WIDTH;
     clipsLeft[0].h = FOO_HEIGHT;
     
     clipsLeft[1].x = FOO_WIDTH;
     clipsLeft[1].y = FOO_HEIGHT;
     clipsLeft[1].w = FOO_WIDTH;
     clipsLeft[1].h = FOO_HEIGHT;
     
     clipsLeft[2].x = FOO_WIDTH * 2;
     clipsLeft[2].y = FOO_HEIGHT;
     clipsLeft[2].w = FOO_WIDTH;
     clipsLeft[2].h = FOO_HEIGHT;
     
     clipsLeft[3].x = FOO_WIDTH * 3;
     clipsLeft[3].y = FOO_HEIGHT;
     clipsLeft[3].w = FOO_WIDTH;
     clipsLeft[3].h = FOO_HEIGHT;
}*/
int main( int argc, char* args[] )
{
     bool quit = false;
     
     int frame = 0;
     
     bool cap = true;
     
     Timer fps;
     Timer update;
     
     
     
     if( init() == false )
         return 1;
     
     if( load_files() == false )
         return 1;
     //set_clips();
     Dot myDot;
     
     update.start();
     
     while( quit == false)
     {
            fps.start();
            while( SDL_PollEvent(&event) )
            {
                   myDot.handle_input();
                                  
                   if( event.type == SDL_QUIT )
                       quit = true;
            }
            
            myDot.move();
            myDot.set_camera();
            //std::stringstream fpsm;
            //fpsm << "FPS: " << frame / ( fps.get_ticks() / 1000.f );
            apply_surface( 0, 0, background, screen, &camera );
            //SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
            myDot.show();
            
            if( update.get_ticks() > 1000.f )
            {
                
                std::stringstream fpsm;
                
                fpsm << "FPS: " <<  ( frame );
                fpsmessage = TTF_RenderText_Solid(font, fpsm.str().c_str(), textColor );
                
                frame = 0;
                update.start();
            }
            apply_surface( 10, 10, fpsmessage, screen);
            if( SDL_Flip( screen ) == -1 )
                return 1;
            
            frame++;
            if( ( ( fps.get_ticks() ) < 1000 / FRAMES_PER_SECOND ) )
                SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - ( fps.get_ticks() ) );
                
            
        
     }
     
     clean_up();
     return 0;
}