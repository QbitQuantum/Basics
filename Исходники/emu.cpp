int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        cerr << "usage: dcpu <flags> <filename>\n";
        return 1;
    }

    bool debug = false;
    int time_to_kill_ms = 0;

    // -d runs in debug mode, prints out memory dump at end

    for(int a = 1; a < argc - 1; a++)
    {
        if(!strcmp(argv[a], "-d"))
        {
            debug = true;
        }else
        {
            cerr << "invalid command <" << argv[a] << ">. ignoring\n";
        }
    }

    ifstream inFile(argv[argc - 1], ios::in);
    if(!inFile.good())
    {
        cerr << "Could not open <" << argv[argc - 1] << ">\n";
        return 1;
    }

    Dcpu cpu(inFile, debug);

    sf::Thread cpu_thread(&start, &cpu);

    sf::RenderWindow app(sf::VideoMode(TERMINAL_WIDTH * 4 * 4, TERMINAL_HEIGHT * 8 * 4), "DCPPU: DCPU-16 Emulator");

    app.SetFramerateLimit(30); // Getting 1500 fps on somthing this simple seems wasteful

    sf::Image font;
    if(!font.LoadFromFile("font.png"))
    {
        cerr << "Could not load font\n";
        return 1;
    }

    unsigned short *buf = cpu.GetScreenBuffer();
    buf += TERMINAL_WIDTH * TERMINAL_HEIGHT;

    // load and encode character set into RAM
    for(int char_off = 0; char_off < 128; char_off++)
    {
        int font_off_x = (char_off * 4) % 128;
        int font_off_y = ((char_off * 4) / 128) * 8;

        unsigned int font_char = 0;
        int x_ = 0;
        int y_ = 0;
        for(int x = font_off_x; x < font_off_x + 4; x++)
        {
            for(int y = font_off_y; y < font_off_y + 8; y++)
            {
                sf::Color pix = font.GetPixel(x, y); 
                if(pix != sf::Color(2, 1, 2))
                    font_char |= 1 << (31-((y_ * 4) + x_));
                y_++;
            }
            x_++;
        }
        unsigned short lowerword = font_char & 0xffff;
        unsigned short upperword = (font_char >> 16) & 0xffff;
        buf[char_off * 2] = upperword;
        buf[char_off * 2 + 1] = lowerword;
    }


    sf::Image screen;
    screen.Create(128, 96); // create black image
    screen.SetSmooth(false);
    sf::Sprite screen_sprite(screen);
    screen_sprite.SetScale(4.0, 4.0);

    cpu_thread.Launch();

    bool running = true;
    while(running)
    {
        sf::Event Event;
        while(app.GetEvent(Event))
        {
            if(Event.Type == sf::Event::Closed)
            {
                cpu.kill();
                running = false;
                app.Close();
            }
            if (Event.Type == sf::Event::TextEntered)
            {
                if (Event.Text.Unicode < 128)
                {
                    char c = static_cast<char>(Event.Text.Unicode);
                    cpu.PushInBuff(c);
                }
            }

        }
        app.Clear();

        unsigned short *buffer = cpu.GetScreenBuffer();

        for(int y = 0; y < TERMINAL_HEIGHT; y++)
        {
            for(int x = 0; x < TERMINAL_WIDTH; x++)
            {
                unsigned short sc = buffer[y * 32 + x];
                int fg_off = (sc >> 12) & 0xf;
                int bg_off = (sc >> 8) & 0xf;
                sf::Color fg = color_table[fg_off];
                sf::Color bg = color_table[bg_off];
                char c = sc & 0x7f;
                bool blink = (sc & 0x80) == 0x80 && (time(0) % 2 == 0); // if bit 15 set, blink on for 1 sec, off for 1 sec

                DrawCharacter(screen, buffer + (TERMINAL_WIDTH*TERMINAL_HEIGHT), c, fg, bg, blink, x, y);
            }
        }

        app.Draw(screen_sprite);
        app.Display();
    }
    
    return 0;
}