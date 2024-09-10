int
main( int argc, char* argv[] )
    {
    srand(time(nullptr));
    LabData lab( 31, 31 );

    // Setup SDL related stuff
    SDL_Init( SDL_INIT_VIDEO );
    atexit( SDL_Quit );
    atexit( IMG_Quit );

    size_t hwin = 17;
    size_t wwin = 16;
    Term::SDL::Context term( wwin, hwin );
    term.Tilemap( "tileset.png" );
    SDL_Surface* screen = SDL_SetVideoMode(
        term.Framebuffer().Width()  * term.TileWidth(),
        term.Framebuffer().Height() * term.TileHeight(),
        32, SDL_SWSURFACE );
    term.RenderTarget( screen );
    Term::Char clearChar('\0');
    clearChar.PriColor( Term::Color::Black );
    clearChar.SecColor( Term::Color::Black );
    term.Framebuffer().ClearChar( clearChar );
    SDL_EnableKeyRepeat( 100, 100 ); // Basically the movementspeed of the player.

    Term::TTY tty( term.Framebuffer() );

    GenerateLabyrinth( lab );
    MakePrettySymbols( lab );

    bool running = true;
    while(running)
        {
        SDL_Event event;
        while( SDL_PollEvent(&event) ) switch( event.type )
            {
            case SDL_QUIT:
                running = false; break;
            case SDL_KEYDOWN: switch( event.key.keysym.sym )
                {
                case SDLK_ESCAPE:
                    running = false; break;
                case SDLK_UP:
                    MovePlayer( lab, 0, -1 ); break;
                case SDLK_DOWN:
                    MovePlayer( lab, 0, 1 ); break;
                case SDLK_LEFT:
                    MovePlayer( lab, -1, 0 ); break;
                case SDLK_RIGHT:
                    MovePlayer( lab, 1, 0 ); break;
                default: break;
                } break;
            }

        if( lab.win )
            {
            std::string winstr( "!!!WIN!!!" );
            int x = rand() % (term.Framebuffer().Width()+winstr.length()) - winstr.length();
            int y = rand() % (term.Framebuffer().Height()+winstr.length()) - winstr.length();
            tty.PriColor( RandomColor() );
            tty.SecColor( RandomColor() );
            tty.Place(x,y).Put( winstr );
            }
        else
            {
            term.Framebuffer().Clear();
            term.Framebuffer().Copy( lab.symbuf, 0, 1,
                -(term.Framebuffer().Width()/2) + lab.xplayer,
                -(term.Framebuffer().Height()/2) + lab.yplayer,
                term.Framebuffer().Width(), term.Framebuffer().Height() );
            tty.Place( term.Framebuffer().Width()/2, term.Framebuffer().Height()/2+1 );
            tty.PriColor( Term::Color::White );
            tty.SecColor( Term::Color::Black );
            tty.Put( 1 );
            for( auto itoken : lab.tokens )
                {
                tty.Place(
                    (itoken % lab.width) +(term.Framebuffer().Width())/2 - lab.xplayer ,
                    (itoken / lab.width) +(term.Framebuffer().Height()/2) - lab.yplayer +1 );
                tty.Put( 9 );
                }
            tty.Place(0,0).PriColor( Term::Color::Black ).SecColor( Term::Color::White );
            if( lab.door == 0 )
                {
                tty.Put( "Tokens left: " );
                std::stringstream ss;
                ss << lab.tokens.size();
                tty.Put( ss.str() );
                }
            else
                {
                tty.Put( "Find the door!" );
                tty.Place(
                    lab.door % lab.width + term.Framebuffer().Width()/2 - lab.xplayer,
                    lab.door / lab.width + term.Framebuffer().Height()/2 + 1 - lab.yplayer );
                tty.Put( 239 );
                }
            }
        term.Print();
        SDL_Flip(screen);
        SDL_Delay(50);
        }
    }