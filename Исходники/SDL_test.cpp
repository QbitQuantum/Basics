int main ( int argc, char *argv[] )
{

    if ( SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 2;
    }

    if(TTF_Init() == -1)
    {
        std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
        return 7;
    }

    SDL_Window *window = SDL_CreateWindow("SDL_TEST", 80, 80, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return 3;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return 4;
    }
    SDL_RenderClear(renderer);

    SYSTEMTIME t;

    SDL_Surface *ClockPlate = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
    SDL_Renderer *PlateRender = SDL_CreateSoftwareRenderer(ClockPlate);
    DrawPlate(PlateRender);
    SDL_Texture *TexturePlate = SDL_CreateTextureFromSurface(renderer, ClockPlate);
    SDL_DestroyRenderer(PlateRender);
    SDL_FreeSurface(ClockPlate);

    SDL_Color LogoColor = { 255, 0, 0, 255 };
    SDL_Rect LogoXY = { WIDTH/2-80, 70, 160, 40 };
    TTF_Font *LogoFont = TTF_OpenFont("C:/Windows/Fonts/KhmerUIb.ttf", 30);
    SDL_Surface *Logo = TTF_RenderUTF8_Blended(LogoFont, "HAMILTON", LogoColor);
    SDL_Texture *TextureLogo = SDL_CreateTextureFromSurface(renderer, Logo);
    SDL_FreeSurface(Logo);
    TTF_CloseFont(LogoFont);

    SDL_Color NumColor = { 0, 255, 255, 255 };
    SDL_Rect NumXY = { WIDTH/2-80, 280, 160, 40 };
    TTF_Font *NumFont = TTF_OpenFont("C:/Windows/Fonts/DIGITAL-Regular.ttf", 32);
    SDL_Surface *NumClock = NULL;
    SDL_Texture *TextureNum = NULL;
    char Num[8];

    SDL_Color DayColor = { 255, 0, 255, 255 };
    SDL_Rect DayXY = { WIDTH/2+75, HEIGHT/2-18, 80, 36 };
    TTF_Font *DayFont = TTF_OpenFont("C:/Windows/Fonts/DIGITAL-Regular.ttf", 60);
    SDL_Surface *SurfaceDay = NULL;
    SDL_Texture *TextureDay = NULL;
    char Day[6];

    bool Quit = false;
    SDL_Event event;
    while(!Quit)
    {
        while(SDL_PollEvent(&event))
            switch(event.type)
            {
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                        Quit = true;
                    break;
                case SDL_QUIT:
                    Quit = true;
                    break;
                default:
                    break;
            }
        GetLocalTime(&t);
        SDL_RenderCopy(renderer, TexturePlate, NULL, NULL);
        SDL_RenderCopy(renderer, TextureLogo, NULL, &LogoXY);

        sprintf(Day, "%.2d  %s", t.wDay, Week(t.wDayOfWeek));
        SurfaceDay = TTF_RenderUTF8_Blended(DayFont, Day, DayColor);
        TextureDay = SDL_CreateTextureFromSurface(renderer, SurfaceDay);
        SDL_FreeSurface(SurfaceDay);
        SDL_RenderCopy(renderer, TextureDay, NULL, &DayXY);
        SDL_DestroyTexture(TextureDay);

        sprintf(Num, "%.2d:%.2d:%.2d", t.wHour, t.wMinute, t.wSecond);
        NumClock = TTF_RenderUTF8_Blended(NumFont, Num, NumColor);
        TextureNum = SDL_CreateTextureFromSurface(renderer, NumClock);
        SDL_FreeSurface(NumClock);
        SDL_RenderCopy(renderer, TextureNum, NULL, &NumXY);
        SDL_DestroyTexture(TextureNum);

        DrawHand(renderer, t.wHour, t.wMinute, t.wSecond);

        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(TextureLogo);
    SDL_DestroyTexture(TexturePlate);
    TTF_CloseFont(NumFont);

    return 0;
}