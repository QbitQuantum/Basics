void GetUserCmd ( 
  WORD wParam,      /* Key Code */
  BOOL ScreenOnly,  /* Send to Screen and or Command Buffer */
  int  InputSize)   /* Number of characters send to screen only */

  {
	extern int HorizScroll; /* Automatic Scrolling Enabled/Disabled */

	switch (wParam)
	  {
		extern SCREEN WinDialog;
		extern int UserInput;

		/*------------------+
		| Handle Back Space |
		+------------------*/

		case VK_BACK:
		  {
			/*-----------------------------------------------+
			| Init Values when sending to the command buffer |
			+-----------------------------------------------*/
			if (! ScreenOnly)
			  {
				HorizScroll = 1;
				if (GetCommandString() != NULL)
				  { InputSize = strlen(GetCommandString()); }
				else
				  { InputSize = 0; }
			  }

	 if (InputSize > 0 )
	 {
		 int size;

		 if (Terminal[WinDialog.LastLine] != NULL)
			{ size = strlen(Terminal[WinDialog.LastLine]); }
		 else
			{ size = 0; }

		 if (!ScreenOnly)
			 ExpandCommandString ('\b');

		 if (size > 0)
			 Terminal[WinDialog.LastLine][size - 1] = '\0';
		 else
		 {  int min, max;
			 extern int OldLine;

			 if ( Terminal[WinDialog.LastLine] != NULL )
			 {
		free(Terminal[WinDialog.LastLine]);
		Terminal[WinDialog.LastLine] = NULL;
	       }

			 WinDialog.LastLine --;
	       OldLine --;

	       if ( WinDialog.LastLine < 0 )
		  WinDialog.LastLine = DIALOG_SIZE;

	       GetScrollRange (WinDialog.hWnd, SB_VERT, &min, &max);
	       if ( WinDialog.NoLines < max && max < DIALOG_SIZE )
	       {  SetScrollRange ( WinDialog.hWnd, SB_VERT, WinDialog.NoLines, max-1, FALSE );
		  SetScrollPos   ( WinDialog.hWnd, SB_VERT, max-1, FALSE );
	       }
	       InvalidateRect ( WinDialog.hWnd, NULL, TRUE );
		 }
		 SendToScreen();
	 }
	 break;
      }

      /*--------------------------+
      | Remove Special Keys (ALT) |
      +--------------------------*/
      case '\f':
      case VK_MENU:
	 break;


      /*----------------+
      | Handle Tab Keys |
      +----------------*/
      case '\t':
		{  if ( !ScreenOnly)
	 {  if ( GetCommandString() == NULL)
	       SetCommandString("   ");
	    else
	       AppendCommandString("   ");
	 }
	 PrintCLIPS ("stdout", "   " );
	 break;
      }


      /*---------------------+
      | Return / Newline Key |
      +---------------------*/
      case '\r':
      case '\n':
      {  wParam = (int)'\n';
	 if (GetScrollPos (WinDialog.hWnd, SB_HORZ) != 0)
	 {  SetScrollPos ( WinDialog.hWnd, SB_HORZ, 0, TRUE );
	    InvalidateRect(WinDialog.hWnd, NULL, FALSE);
	    SendMessage ( WinDialog.hWnd, WM_PAINT, 0, 0 );
	 }
      }

      /*---------------------+
      | All other characters |
      +---------------------*/
      default:
      {  char text[2];

	 text[0] = (char) wParam;
	 text[1] = '\0';

	 if(isprint ( text[0]) || isspace (text[0]))
	 {  /*----------------------------+
	    | Add to CLIPS Command Buffer |
		 +----------------------------*/

	    if (!ScreenOnly)
	    {  if ( GetCommandString() == NULL)
		  SetCommandString(text);
	       else
		  AppendCommandString(text);
		 }

		 PrintCLIPS ("stdout", text );
	 }
	 break;
		}
	}
	HorizScroll = 0;
}