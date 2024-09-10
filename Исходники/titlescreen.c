/****************************************
* TitleScreen: Display the title screen *
*****************************************
* display title screen, get input
*/
void TitleScreen(void)
{

  Uint32 frame = 0;
  Uint32 start = 0;

  /* NOTE for 'depth', think pages like a restaurant menu, */
  /* not heirarchical depth - choice of term is misleading */
  int menu_depth; // how deep we are in the menu

  int i, j, tux_frame = 0;
  int done = 0;
  int firstloop = 1;
  int menu_opt = NONE;
  int sub_menu = NONE;
  int update_locs = 1;
  int redraw = 0;
  int key_menu = 1;
  int old_key_menu = 5;


  if (settings.sys_sound)
  {
    settings.menu_sound = 1;
    settings.menu_music = 1;
  }

  start = SDL_GetTicks();


  /*
  * Display the Standby screen.... 
  */
  show_logo();
  snd_welcome = LoadSound("harp.wav");

  if (snd_welcome && settings.menu_sound)
  {
    PlaySound(snd_welcome);
  }

  /* Load media and menu data: */
  if (!load_media())
  {
    fprintf(stderr, "TitleScreen - load_media() failed!");
    return;
  }

  SDL_WM_GrabInput(SDL_GRAB_ON); // User input goes to TuxType, not window manager


  /***************************
  * Tux and Title animations *
  ***************************/

  LOG( "->Now Animating Tux and Title onto the screen\n" );

  Tuxdest.x = 0;
  Tuxdest.y = screen->h;
  Tuxdest.w = Tux->frame[0]->w;
  Tuxdest.h = Tux->frame[0]->h;

  Titledest.x = screen->w;
  Titledest.y = 10;
  Titledest.w = title->w;
  Titledest.h = title->h;

  spkrdest.x = screen->w - speaker->w - 10;
  spkrdest.y = screen->h - speaker->h - 10;
  spkrdest.w = speaker->w;
  spkrdest.h = speaker->h;

  /* --- wait if the first time in the game --- */

  if (settings.show_tux4kids)
  {
    while ((SDL_GetTicks() - start) < 2000)
    {
      SDL_Delay(50);
    }
    settings.show_tux4kids = 0;
  }

  SDL_ShowCursor(1);    
  /* FIXME not sure the next line works in Windows: */
  TransWipe(CurrentBkgd(), RANDOM_WIPE, 10, 20);
  /* Make sure background gets drawn (since TransWipe() doesn't */
  /* seem to work reliably as of yet):                          */
  SDL_BlitSurface(CurrentBkgd(), NULL, screen, NULL);
  SDL_UpdateRect(screen, 0, 0, 0, 0);

  /* --- Pull tux & logo onscreen --- */
  for (i = 0; i <= (PRE_ANIM_FRAMES * PRE_FRAME_MULT); i++)
  {
    start = SDL_GetTicks();
    SDL_BlitSurface(CurrentBkgd(), &Tuxdest, screen, &Tuxdest);
    SDL_BlitSurface(CurrentBkgd(), &Titledest, screen, &Titledest);


    Tuxdest.y -= Tux->frame[0]->h / (PRE_ANIM_FRAMES * PRE_FRAME_MULT);
    Titledest.x -= (screen->w) / (PRE_ANIM_FRAMES * PRE_FRAME_MULT);
    /* Don't go past 0; */
    if (Tuxdest.y < 0)
      Tuxdest.y = 0;
    if (Titledest.x < 0)
      Titledest.x = 0;

    SDL_BlitSurface(Tux->frame[0], NULL, screen, &Tuxdest);
    SDL_BlitSurface(title, NULL, screen, &Titledest);

    SDL_UpdateRect(screen, Tuxdest.x, Tuxdest.y, Tuxdest.w, Tuxdest.h);
    SDL_UpdateRect(screen, Titledest.x, Titledest.y, Titledest.w + 40, Titledest.h);

    while ((SDL_GetTicks() - start) < 33) 
    {
      SDL_Delay(2);
    }
  }

  recalc_rects();

  /* Pick speaker graphic according to whether music is on: */
  if ( settings.menu_music )
    SDL_BlitSurface(speaker, NULL, screen, &spkrdest);
  else
    SDL_BlitSurface(speakeroff, NULL, screen, &spkrdest);

  /* Start playing menu music if desired: */
  if (settings.menu_music)
    MusicLoad( "tuxi.ogg", -1 );

  LOG( "Tux and Title are in place now\n" );

  SDL_WM_GrabInput(SDL_GRAB_OFF);


  /****************************
  * Main Loop Starts Here ... *
  ****************************/


  menu_depth = 1;
  firstloop = 1;
  Tuxdest.y = screen->h - Tux->frame[0]->h;


  while (!done) 
  {

    start = SDL_GetTicks();

    /* ---process input queue --- */

    menu_opt = NONE; // clear the option so we don't change twice!

    old_key_menu = key_menu;

    /* Retrieve any user interface events: */
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        /* Update "selection" if mouse moves within a menu entry: */
        case SDL_MOUSEMOTION:
        {
          cursor.x = event.motion.x;
          cursor.y = event.motion.y;

	  for (j = 1; j <= TITLE_MENU_ITEMS; j++)
            if (inRect(menu_button[j], cursor.x, cursor.y))
              key_menu = j;
          break;
        }


        /* Handle mouse clicks based on mouse location: */
        case SDL_MOUSEBUTTONDOWN:
        {
          cursor.x = event.motion.x;
          cursor.y = event.motion.y;

          for (j = 1; j <= TITLE_MENU_ITEMS; j++)
          {
            if (inRect(menu_button[j], cursor.x, cursor.y))
            {
              menu_opt = menu_item[j][menu_depth];
              if (settings.menu_sound)
              {
                PlaySound(snd_select);
              }
              DEBUGCODE
              {
                fprintf(stderr, "->>BUTTON CLICK menu_opt = %d\n", menu_opt);
                fprintf(stderr, "->J = %d menu_depth=%d\n", j, menu_depth);
              }
            }
          }

          /* If mouse over speaker, toggle menu music off or on: */
          if (inRect(spkrdest, cursor.x, cursor.y))
          {
            if (settings.menu_music)
            {
              MusicUnload();
              settings.menu_music = 0;
            }
            else
            {
              settings.menu_music = 1;
              MusicLoad("tuxi.ogg", -1);
            }
            redraw = 1;
          }
          break;
        }



        case SDL_QUIT:
        {
          menu_opt = QUIT_GAME;
          break;
        }


        /* Handle key press events based on key value: */
        case SDL_KEYDOWN:
        {
          switch (event.key.keysym.sym)
          {
            case SDLK_ESCAPE:
            {
              /* Go to main menu (if in submenu) or quit: */
              if (menu_depth != 1) 
                menu_opt = MAIN;
              else
                menu_opt = QUIT_GAME;

              if (settings.menu_sound)
                PlaySound(snd_select);
              break;
            }


            /* Toggle screen mode: */
            case SDLK_F10:
            {
              SwitchScreenMode();
              recalc_rects();
              redraw = 1;
              break;
            }


            /* Toggle menu music: */
            case SDLK_F11:
            {
              if (settings.menu_music)
              {
                MusicUnload( );
                settings.menu_music = 0;
              }
              else
              {
                settings.menu_music = 1;
                MusicLoad("tuxi.ogg", -1);
              }
              redraw = 1;
              break;
            }


            /* --- reload translation/graphics/media: for themers/translaters --- */
            case SDLK_F12:
            {
              unload_media();
              LoadLang();
              load_media();
              redraw = 1;
              break;
            }


            case SDLK_UP:
	    case SDLK_k:
            {
              if (settings.menu_sound)
                PlaySound(snd_move);
              key_menu--;
              if (key_menu < 1)
                key_menu = 5;
              break;
            }


            case SDLK_DOWN:
	    case SDLK_j:
            {
              key_menu++;
              if (settings.menu_sound)
                PlaySound(snd_move);
              if (key_menu > 5)
                key_menu = 1;
              break;
            }


            case SDLK_RETURN:
            {
              if (key_menu)
              {
                menu_opt = menu_item[key_menu][menu_depth];
                if (settings.menu_sound)
                  PlaySound(snd_select);
              }
              break;
            }


            default:     /* Some other key pressed - do nothing: */
            {
              break;
            }
          }             /* End of switch(event.key.keysym.sym) statement */
        }               /* End of case: SDL_KEYDOWN: */


        default:        /* Some other type of SDL event - do nothing;    */
        {
          break;
        }
      }                 /* End of switch(event.type) statement           */
    }	              /* End of while (SDL_PollEvent(&event)) loop     */





    /* --- do menu processing --- */


    if (menu_opt == QUIT_GAME)
      done = 1;


    if (menu_opt == LASER)
    {
      menu_depth = LASER_SUBMENU;
      sub_menu = LASER;
      update_locs = 1;
      redraw = 1;
    }


    if (menu_opt == CASCADE)
    {
      menu_depth = CASCADE_SUBMENU;
      sub_menu = CASCADE;
      update_locs = 1;
      redraw=1;
    }


    if (menu_opt == OPTIONS)
    {
      menu_depth = OPTIONS_SUBMENU;
      sub_menu = OPTIONS;
      update_locs = 1;
      redraw = 1;
    }


    if (menu_opt == MAIN)
    {
      menu_depth = ROOTMENU;
      update_locs = 1;
      redraw = 1;
    }


    if (menu_opt == EDIT_WORDLIST)
    {
      ChooseListToEdit();
      redraw = 1;
    }


    if (menu_opt == PROJECT_INFO)
    {
      ProjectInfo();
      redraw = 1;
    }


    if (menu_opt == LESSONS)
    {
//      not_implemented();
      SDL_BlitSurface(CurrentBkgd(), NULL, screen, NULL);
      SDL_Flip(screen);
      unload_media();

      if (settings.menu_music)
        MusicUnload( );

      XMLLesson();

      load_media();

      redraw = 1;

      if (settings.menu_music)
        MusicLoad( "tuxi.ogg", -1 );
    }


    if (menu_opt == SET_LANGUAGE)
    {
      unload_media();
      ChooseTheme();
      LoadLang();
      LoadKeyboard();
      load_media();
      redraw = 1;

      if (settings.menu_music)
        MusicLoad( "tuxi.ogg", -1 );
    }


    if (menu_opt == LEVEL1)
    {  
      if (chooseWordlist()) 
      {
        unload_media();

        switch (sub_menu)
        {
          case CASCADE: PlayCascade( EASY ); break;
          case LASER:   PlayLaserGame(  EASY ); break;
        }
      }

      load_media();

      if (settings.menu_music)
        MusicLoad("tuxi.ogg", -1);

      redraw = 1;
    }


    if (menu_opt == LEVEL2)
    {
      if (chooseWordlist())
      {
        unload_media();

        switch (sub_menu)
        {
          case CASCADE: PlayCascade( MEDIUM ); break;
          case LASER:   PlayLaserGame(  MEDIUM ); break;
        }


        if (settings.menu_music)
          MusicLoad( "tuxi.ogg", -1 );
      }

      load_media();
      redraw = 1;
    }



    if (menu_opt == LEVEL3)
    {
      if (chooseWordlist())
      {
        unload_media();

        switch (sub_menu)
        {
          case CASCADE: PlayCascade( HARD ); break;
          case LASER:   PlayLaserGame(  HARD ); break;
        }


        if (settings.menu_music)
          MusicLoad( "tuxi.ogg", -1 );
      }

      load_media();
      redraw = 1;
    }



    if (menu_opt == LEVEL4)
    {
      if (chooseWordlist())
      {
        unload_media();

        switch (sub_menu)
        {
          case CASCADE: PlayCascade( INSANE ); break;
          case LASER:   PlayLaserGame(  INSANE ); break;
        }

        if (settings.menu_music)
          MusicLoad( "tuxi.ogg", -1 );
      }

      load_media();
      redraw = 1;
    }



    if (menu_opt == INSTRUCT)
    {
//       not_implemented();
       unload_media();

      switch (sub_menu)
      {
        case CASCADE: InstructCascade(); break;
        case LASER:   InstructLaser();   break;
      }

      load_media();

      if (settings.menu_music)
        MusicLoad( "tuxi.ogg", -1 );

      redraw = 1;
    }



    if (menu_opt == PHRASE_TYPING)
    {
//      not_implemented();

      unload_media();

      Phrases(NULL);

      load_media();

      if (settings.menu_music)
        MusicLoad( "tuxi.ogg", -1 );

      redraw = 1;
    }

    /* ------ End menu_opt processing ----------- */



    if (redraw)
    {
      LOG("TitleScreen() - redraw requested\n");
      recalc_rects();

      SDL_BlitSurface(CurrentBkgd(), NULL, screen, NULL); 
      SDL_BlitSurface(title, NULL, screen, &Titledest);

      if ( settings.menu_music )
        SDL_BlitSurface(speaker, NULL, screen, &spkrdest);
      else
        SDL_BlitSurface(speakeroff, NULL, screen, &spkrdest);

      /* Screen will be updated due to update_locs - see ~30 lines down: */
//      SDL_UpdateRect(screen, 0, 0, 0, 0);
      frame = redraw = 0;   // so we redraw tux
      update_locs = 1;      // so we redraw menu
      firstloop = 1;
    }



    /* --- create new menu screen when needed --- */

    if (update_locs)
    {
      LOG("TitleScreen() - update_locs requested\n");

      /* --- erase the last menu --- */
      for (i = 1; i <= TITLE_MENU_ITEMS; i++)
      {
        text_dst[i].x = screen->w/2 - 70;//290;
        text_dst[i].w = reg_text[i][menu_depth]->w;
        text_dst[i].h = reg_text[i][menu_depth]->h;
        SDL_BlitSurface(CurrentBkgd(), &menu_button[i], screen, &menu_button[i]);
        menu_button[i].w = menu_width[menu_depth] + 20;
      }


      update_locs = 0;

      /* --- draw the full menu --- */

      for (j = 1; j <= TITLE_MENU_ITEMS; j++)
      {
        DOUT(j);
        DrawButton(&menu_button[j], 10, REG_RGBA);
        if (reg_text[j][menu_depth] != NULL)
          SDL_BlitSurface(reg_text[j][menu_depth], NULL, screen, &text_dst[j]);
        if (menu_gfx[j][menu_depth] != NULL)
          SDL_BlitSurface(menu_gfx[j][menu_depth]->default_img, NULL, screen, &menu_gfxdest[j]);
      }

      SDL_UpdateRect(screen, 0, 0, 0, 0);

      LOG("TitleScreen() - update_locs completed\n");
    }



    /* --- make tux blink --- */

    switch (frame % TUX6)
    {
      case 0:    tux_frame = 1; break;
      case TUX1: tux_frame = 2; break;
      case TUX2: tux_frame = 3; break;
      case TUX3: tux_frame = 4; break;			
      case TUX4: tux_frame = 3; break;
      case TUX5: tux_frame = 2; break;
      default: tux_frame = 0;
    }

    if (tux_frame)
    {
      SDL_Rect blink_src, blink_dest;
      blink_src.x = 0;
      blink_src.y = 0;
      blink_src.w = Tuxdest.w;
      blink_src.h = Tuxdest.h;
      blink_dest.x = Tuxdest.x + blink_src.x;
      blink_dest.y = Tuxdest.y + blink_src.y;
      blink_dest.w = blink_src.w;
      blink_dest.h = blink_src.h;
//      SDL_BlitSurface(CurrentBkgd(), , screen, &Tuxdest);
      SDL_BlitSurface(Tux->frame[tux_frame - 1], &blink_src, screen, &blink_dest);
    }


    /* --- check if mouse is in a menu option --- */

//    key_menu = 0;
/*
    for (j = 1; j <= TITLE_MENU_ITEMS; j++)
    {
      if ((cursor.x >= menu_button[j].x && cursor.x <= (menu_button[j].x + menu_button[j].w)) &&
          (cursor.y >= menu_button[j].y && cursor.y <= (menu_button[j].y + menu_button[j].h)))
      {
        key_menu = j; // update menu to point
        break;        // Don't need to check rest of menu
      }
    }*/


    /* --- return old selection to unselected state --- */

    if (old_key_menu && (key_menu != old_key_menu))
    {
      SDL_BlitSurface(CurrentBkgd(), &menu_button[old_key_menu], screen, &menu_button[old_key_menu]);
      DrawButton(&menu_button[old_key_menu], 10, REG_RGBA);
      SDL_BlitSurface(reg_text[old_key_menu][menu_depth], NULL, screen, &text_dst[old_key_menu]);
      SDL_BlitSurface(menu_gfx[old_key_menu][menu_depth]->default_img, NULL, screen, &menu_gfxdest[old_key_menu]);
    }


    /* --- draw current selection --- */

    if ((key_menu != 0) &&
       ((old_key_menu != key_menu) || (frame % 5 == 0))) // Redraw every fifth frame?
    {
      if (key_menu != old_key_menu)
      {
        REWIND(menu_gfx[key_menu][menu_depth]);
        PlaySound(snd_move);
      }

      SDL_BlitSurface(CurrentBkgd(), &menu_button[key_menu], screen, &menu_button[key_menu]);
      DrawButton(&menu_button[key_menu], 10, SEL_RGBA);
      SDL_BlitSurface(sel_text[key_menu][menu_depth], NULL, screen, &text_dst[key_menu]);
      SDL_BlitSurface(menu_gfx[key_menu][menu_depth]->frame[menu_gfx[key_menu][menu_depth]->cur], NULL, screen, &menu_gfxdest[key_menu]);

      NEXT_FRAME(menu_gfx[key_menu][menu_depth]);
    }


    // HACK This is still more than we need to update every frame but
    // it cuts cpu on my machine %60 so it seems better...
    if ( settings.menu_music )
      SDL_BlitSurface(speaker, NULL, screen, &spkrdest);
    else
      SDL_BlitSurface(speakeroff, NULL, screen, &spkrdest);

    SDL_UpdateRect(screen, spkrdest.x, spkrdest.y, spkrdest.w, spkrdest.h);

    for (i = 1; i < 6; i++)
    {
      SDL_UpdateRect(screen, menu_button[i].x, menu_button[i].y, menu_button[i].w, menu_button[i].h);
    }

    if (tux_frame)
      SDL_UpdateRect(screen, Tuxdest.x, Tuxdest.y, Tuxdest.w, Tuxdest.h);

    if (firstloop)
      SDL_UpdateRect(screen, Tuxdest.x, Tuxdest.y, Tuxdest.w, Tuxdest.h);

    firstloop = 0;

    /* Wait so we keep frame rate constant: */
    while ((SDL_GetTicks() - start) < 33)
    {
      SDL_Delay(20);
    }

    frame++;
  } /* ----------- End of 'while(!done)' loop ------------  */