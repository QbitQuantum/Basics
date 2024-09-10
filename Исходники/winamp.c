static int
winamp(const char *const word[], const char *const word_eol[], void *userdata)
{

char current_play[2048], *p;
char p_esc[2048];
char cur_esc[2048];
char truc[2048];
HWND hwndWinamp = FindWindowW(L"Winamp v1.x",NULL);

    if (hwndWinamp)
	{
	    {
	        if (!stricmp("PAUSE", word[2]))
			{
			   if (SendMessageW(hwndWinamp,WM_USER, 0, 104))
				{
			   	   SendMessageW(hwndWinamp, WM_COMMAND, 40046, 0);
			
			       if (SendMessageW(hwndWinamp, WM_USER, 0, 104) == PLAYING)
			   	       hexchat_print(ph, "Winamp: playing");
			       else
                       hexchat_print(ph, "Winamp: paused");
				}
            }
			else
		        if (!stricmp("STOP", word[2]))
			    {
			       SendMessageW(hwndWinamp, WM_COMMAND, 40047, 0);
			       hexchat_print(ph, "Winamp: stopped");
			    }
			else
			    if (!stricmp("PLAY", word[2]))
			    {
			         SendMessageW(hwndWinamp, WM_COMMAND, 40045, 0);
			         hexchat_print(ph, "Winamp: playing");
			    }
        	else

			    if (!stricmp("NEXT", word[2]))
			    {
			         SendMessageW(hwndWinamp, WM_COMMAND, 40048, 0);
			         hexchat_print(ph, "Winamp: next playlist entry");
			    }
			else

                if (!stricmp("PREV", word[2]))
			    {
			         SendMessageW(hwndWinamp, WM_COMMAND, 40044, 0);
			         hexchat_print(ph, "Winamp: previous playlist entry");
			    }
		    else

                if (!stricmp("START", word[2]))
			    {
			         SendMessageW(hwndWinamp, WM_COMMAND, 40154, 0);
			         hexchat_print(ph, "Winamp: playlist start");
			    }

		    else

                if (!word_eol[2][0])
			    {
					GetWindowText(hwndWinamp, current_play, sizeof(current_play));

					if (strchr(current_play, '-'))
					{
	
					p = current_play + strlen(current_play) - 8;
					while (p >= current_play)
					{
						if (!strnicmp(p, "- Winamp", 8)) break;
							p--;
					}

					if (p >= current_play) p--;
	
					while (p >= current_play && *p == ' ') p--;
						*++p=0;
	
	
					p = strchr(current_play, '.') + 1;

 					song_strcpy(p_esc, p);
 					song_strcpy(cur_esc, current_play);
	
					if (p)
					{
						sprintf(truc, "me is now playing:%s", p_esc);
					}
					else
					{
						sprintf(truc, "me is now playing:%s", cur_esc);
					}
	
	   				hexchat_commandf(ph, truc);
	
				}
				else hexchat_print(ph, "Winamp: Nothing being played.");
			}
		    else
                hexchat_printf(ph, "Usage: /WINAMP [PAUSE|PLAY|STOP|NEXT|PREV|START]\n");
         }

	}
	else
	{
       hexchat_print(ph, "Winamp not found.\n");
	}
	return HEXCHAT_EAT_ALL;
}