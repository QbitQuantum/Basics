id0_int_t DebugKeys (void)
{
    id0_boolean_t esc;
    id0_int_t level,i;

#if 0
    if (Keyboard[sc_A])
    {
        id0_char_t levelstr[50];
        id0_unsigned_t org_tile,org_mapon,msgnum;
        id0_boolean_t newmsg=true,newlevel=false;

        VW_FixRefreshBuffer ();
        CenterWindow (16,3);
        US_Print("\n");
        US_CPrint("Message Test");
        VW_UpdateScreen();

        org_mapon = mapon;
        msgnum = (org_tile = *(mapsegs[0]+farmapylookup[player->tiley]+player->tilex))-NAMESTART;
        while (1)
        {
            // Get outta' here
            //
            if (Keyboard[sc_Escape])
            {
                while (Keyboard[sc_Escape])
                {
                    BE_ST_ShortSleep();
                }
                break;
            }

            // Move to previous message
            //
            if (Keyboard[sc_UpArrow])
            {
                if (msgnum)
                {
                    msgnum--;
                    newmsg = true;
                }
            }

            // Move to next message
            //
            if (Keyboard[sc_DownArrow])
            {
                if (msgnum < 24)
                {
                    msgnum++;
                    newmsg = true;
                }
            }

            // Move to previous level
            //
            if (Keyboard[sc_LeftArrow])
            {
                if (mapon)
                {
                    MM_SetPurge(&grsegs[LEVEL1TEXT+mapon],3);
                    mapon--;
                    newlevel = true;
                }
            }

            // Move to next level
            //
            if (Keyboard[sc_RightArrow])
            {
                if (mapon < LASTMAP-2)
                {
                    MM_SetPurge(&grsegs[LEVEL1TEXT+mapon],3);
                    mapon++;
                    newlevel = true;
                }
            }

            // Load new level text
            //
            if (newlevel)
            {
                CA_CacheGrChunk(LEVEL1TEXT+mapon);
                ScanText();
                newmsg = true;
                newlevel=false;
            }

            // Display new message text
            //
            if (newmsg)
            {
                *(mapsegs[0]+farmapylookup[player->tiley]+player->tilex) = msgnum+NAMESTART;
                DrawText(true);
                strcpy(levelstr,"Level: ");
                itoa(mapon,levelstr+strlen(levelstr),10);
                strcat(levelstr,"  Msg: ");
                itoa(msgnum,levelstr+strlen(levelstr),10);
                DisplaySMsg(levelstr,NULL);
                newmsg = false;

                if (Keyboard[sc_UpArrow] || Keyboard[sc_DownArrow] || Keyboard[sc_LeftArrow] || Keyboard[sc_RightArrow])
                    VW_WaitVBL(6);
            }

            BE_ST_ShortSleep();
        }
// Restore game
//
        MM_SetPurge(&grsegs[LEVEL1TEXT+mapon],3);
        mapon = org_mapon;
        CA_CacheGrChunk(LEVEL1TEXT+mapon);
        ScanText();
        *(mapsegs[0]+farmapylookup[player->tiley]+player->tilex) = org_tile;
        DrawText(true);
        status_flag = 0;
    }
#endif

    if (Keyboard[sc_T])
    {
        VW_FixRefreshBuffer ();
        CenterWindow (16,4);

        US_Print("Tics      :");
        US_PrintUnsigned (tics);
        US_Print("\nReal Tics :");
        US_PrintUnsigned(realtics);
        VW_UpdateScreen();
        IN_Ack ();
    }

    if (Keyboard[sc_V])
    {
        displayofs = bufferofs = screenloc[screenpage];
        CenterWindow (20,5);
        US_CPrint(refkeen_compat_gelib_c4_debug_str_with_gamename);
        //US_CPrint("\n"GAMENAME);
        US_CPrint(VERSION);
        US_CPrint(REVISION);
        VW_UpdateScreen();
        IN_Ack ();
    }

    if (Keyboard[sc_Q])			// Q = Insta-Quit!
        Quit("Insta-Quit!");

    if (Keyboard[sc_Z])		// Z = freeze Time
    {
        if (FreezeTime)
            FreezeTime = 1;		// Allow refresh to dec to zero..
        else
            StopTime();

        IN_Ack();
        return 1;
    }

//	if (Keyboard[sc_E])
//		FaceDoor((player->x>>16l)+1,(player->y>>16l));
//		FaceAngle(90);

#if 0
    if (Keyboard[sc_B])		// B = border color
    {
        CenterWindow(24,3);
        PrintY+=6;
        US_Print(" Border color (0-15):");
        VW_UpdateScreen();
        esc = !US_LineInput (px,py,str,NULL,true,2,0);
        if (!esc)
        {
            level = atoi (str);
            if (level>=0 && level<=15)
                VW_ColorBorder (level);
        }
        return 1;
    }
#endif

#if 0
    if (Keyboard[sc_C])		// C = count objects
    {
        CountObjects();
        return 1;
    }


    if (Keyboard[sc_D])		// D = start / end demo record
    {
        if (DemoMode == demo_Off)
            StartDemoRecord ();
        else if (DemoMode == demo_Record)
        {
            EndDemoRecord ();
            playstate = ex_completed;
        }
        return 1;
    }
#endif

#if 0
    if (Keyboard[sc_E])		// E = quit level
    {
        if (tedlevel)
            TEDDeath();
        playstate = ex_warped;
        gamestate.mapon++;
    }
#endif

#if 0
    if (Keyboard[sc_F])		// F = facing spot
    {
        CenterWindow (12,4);
        US_Print ("X:");
        US_PrintUnsigned (player->x);
        US_Print ("Y:");
        US_PrintUnsigned (player->y);
        US_Print ("A:");
        US_PrintUnsigned (player->angle);
        VW_UpdateScreen();
        IN_Ack();
        return 1;
    }
#endif

    if (Keyboard[sc_G])		// G = god mode
    {
        CenterWindow (12,2);
        if (godmode)
            US_PrintCentered ("God mode OFF");
        else
            US_PrintCentered ("God mode ON");
        VW_UpdateScreen();
        IN_Ack();
        godmode ^= 1;
        return 1;
    }

#if 0
    if (Keyboard[sc_H])		// H = hurt self
    {
        TakeDamage (5);
    }
#endif

    if (Keyboard[sc_I])			// I = item cheat
    {
        extern id0_boolean_t redraw_gems;

        CenterWindow (12,3);
        US_PrintCentered ("Free items!");
        VW_UpdateScreen();
        for (i=0; i<4; i++)
        {
            GiveBolt ();
            GiveNuke ();
            GivePotion ();
//			if (!gamestate.keys[i])
            GiveKey (i);
            gamestate.gems[i] = GEM_DELAY_TIME;
        }
        gamestate.gems[4] = GEM_DELAY_TIME;
        redraw_gems = true;
        for (i=0; i<8; i++)
            GiveScroll (i,false);

        IN_Ack ();
        return 1;
    }

    if (Keyboard[sc_M])			// M = memory info
    {
        DebugMemory();
        return 1;
    }

#if DEBUG_OVERHEAD
    if (Keyboard[sc_O])			// O = overhead
    {
        ViewMap();
        return 1;
    }
#endif

#if 0
    if (Keyboard[sc_P])			// P = pause with no screen disruptioon
    {
        PicturePause ();
        return 1;
    }
#endif

#if 0
    if (Keyboard[sc_S])	// S = slow motion
    {
        singlestep^=1;
        CenterWindow (18,3);
        if (singlestep)
            US_PrintCentered ("Slow motion ON");
        else
            US_PrintCentered ("Slow motion OFF");
        VW_UpdateScreen();
        IN_Ack ();
        return 1;
    }
#endif

#if 0
    if (Keyboard[sc_V])			// V = extra VBLs
    {
        CenterWindow(30,3);
        PrintY+=6;
        US_Print("  Add how many extra VBLs(0-8):");
        VW_UpdateScreen();
        esc = !US_LineInput (px,py,str,NULL,true,2,0);
        if (!esc)
        {
            level = atoi (str);
            if (level>=0 && level<=8)
                extravbls = level;
        }
        return 1;
    }
#endif

    if (Keyboard[sc_W])	// W = warp to level
    {
        CenterWindow(26,3);
        PrintY+=6;
        US_Print("  Warp to which level(0-18):");
        VW_UpdateScreen();
        esc = !US_LineInput (px,py,str,NULL,true,2,0);
        if (!esc)
        {
            level = atoi (str);
            if (level>=0 && level<=LASTMAP-1)
            {
                gamestate.mapon = level;
                playstate = ex_warped;
                lasttext = -1;
            }
        }
        return 1;
    }

#if 0
    if (Keyboard[sc_X])			// X = item cheat
    {
        CenterWindow (12,3);
        US_PrintCentered ("Extra stuff!");
        VW_UpdateScreen();
        for (i=0; i<4; i++)
        {
            GiveBolt ();
            GiveNuke ();
            GivePotion ();
        }
        IN_Ack ();
        return 1;
    }
#endif

    if (LastScan >= sc_1 && LastScan <= sc_8)	// free scrolls
    {
        GiveScroll (LastScan-sc_1,false);
        IN_ClearKeysDown ();
    }

    return 0;
}