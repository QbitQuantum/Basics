MRESULT Window::stdWndProc( HWND hWnd, ULONG iMessage, MPARAM mParam1,
                            MPARAM mParam2, BOOL *returned )
{
  switch( iMessage )
  {
//    case WM_FOCUSCHANGE :
    case WM_SETSELECTION :
    case WM_ACTIVATE :
    {
      if( type != Window::LISTBOX &&
          type != Window::COMBOLISTBOX )
      {
        focus( (BOOL)mParam1 );//SHORT1FROMMP( mParam2 ) );
      }
      break;
    }
    case WM_SETFOCUS :
    {
      if( type != Window::LISTBOX &&
          type != Window::COMBOLISTBOX )
        focusSet( (BOOL)mParam2 );
      break;
    }
    case WM_BUTTON1DOWN :
    {
      if( type == SCROLLBAR )
        setFocus();
      HWND hwnd = WinQueryFocus( HWND_DESKTOP );
      if( mouseListener.getSize() != 0 )
      {
        mouseButtonDown = TRUE;
        WinSetCapture( HWND_DESKTOP, hWnd );
	  		WinStartTimer( Application::hab, hWndClient, 1, 50 );
        Point pos( SHORT1FROMMP(mParam1), SHORT2FROMMP(mParam1) );
        performMouseEvent( &pos, AMouseEvent::LEFT, AMouseEvent::DOWN );
      }
      if( hwnd != WinQueryFocus( HWND_DESKTOP ) ) return (MRESULT)TRUE;
      break;
    }
    case WM_BUTTON1UP :
    {
      if( type == LISTBOX ||
          type == COMBOLISTBOX )
      {
        performFocusEvent(
          (int)WinSendMsg( (HWND)mParam2, LM_QUERYSELECTION, MPARAM(0), MPARAM(NULL) ) );
      }
      else
      if( mouseListener.getSize() != 0 )
      {
        mouseButtonDown = FALSE;
        WinStopTimer( Application::hab, hWndClient, 1 );
        WinSetCapture( HWND_DESKTOP, NULLHANDLE );
        Point pos( SHORT1FROMMP(mParam1), SHORT2FROMMP(mParam1) );
        performMouseEvent( &pos, AMouseEvent::LEFT, AMouseEvent::RELEASE );
//        return (MPARAM)TRUE;
      }
      break;
    }
    case WM_BUTTON2DOWN :
    {
      if( mouseListener.getSize() != 0 )
      {
        WinSetCapture( HWND_DESKTOP, hWnd );
	  		WinStartTimer( Application::hab, hWndClient, 1, 50 );
        Point pos( SHORT1FROMMP(mParam1), SHORT2FROMMP(mParam1) );
        performMouseEvent( &pos, AMouseEvent::RIGHT, AMouseEvent::DOWN );
      }
      break;
    }
    case WM_BUTTON2UP :
    {
      if( mouseListener.getSize() != 0 )
      {
        WinStopTimer( Application::hab, hWndClient, 1 );
        WinSetCapture( HWND_DESKTOP, NULLHANDLE );
        Point pos( SHORT1FROMMP(mParam1), SHORT2FROMMP(mParam1) );
        performMouseEvent( &pos, AMouseEvent::RIGHT, AMouseEvent::RELEASE );
      }
      break;
    }
    case WM_BUTTON1CLICK :
    {
      if( mouseListener.getSize() != 0 )
      {
				// Check if triple click

				int newTick = WinGetCurrentTime( Application::hab );
				if( newTick - lastTick <= 
            WinQuerySysValue( HWND_DESKTOP, SV_DBLCLKTIME ) )
				{
	        Point pos( SHORT1FROMMP(mParam1), SHORT2FROMMP(mParam1) );
		      performMouseEvent( &pos, AMouseEvent::LEFT, AMouseEvent::TRIPLECLICK );
				}
				else
        {
        	Point pos( SHORT1FROMMP(mParam1), SHORT2FROMMP(mParam1) );
        	performMouseEvent( &pos, AMouseEvent::LEFT, AMouseEvent::CLICK );
				}
      }
      break;
    }
    case WM_BUTTON2CLICK :
    {
      if( mouseListener.getSize() != 0 )
      {
        Point pos( SHORT1FROMMP(mParam1), SHORT2FROMMP(mParam1) );
        performMouseEvent( &pos, AMouseEvent::RIGHT, AMouseEvent::CLICK );
      }
      break;
    }
    case WM_BUTTON1DBLCLK :
    {
      if( mouseListener.getSize() != 0 )
      {
        Point pos( SHORT1FROMMP(mParam1), SHORT2FROMMP(mParam1) );
        performMouseEvent( &pos, AMouseEvent::LEFT, AMouseEvent::DOUBLECLICK );
      }
			lastTick = WinGetCurrentTime( Application::hab );
      break;
    }
    case WM_BUTTON2DBLCLK :
    {
      if( mouseListener.getSize() != 0 )
      {
        Point pos( SHORT1FROMMP(mParam1), SHORT2FROMMP(mParam1) );
        performMouseEvent( &pos, AMouseEvent::RIGHT, AMouseEvent::DOUBLECLICK );
      }
      break;
    }
    case WM_MOUSEMOVE :
    {
      if( currentPointer != NULLHANDLE )
        WinSetPointer( HWND_DESKTOP, currentPointer );
      if( mouseListener.getSize() != 0 )
      {
        Point pos( (SHORT)SHORT1FROMMP(mParam1), (SHORT)SHORT2FROMMP(mParam1) );
        performMouseEvent( &pos, 0, AMouseEvent::MOVE );
      }
      if( currentPointer != NULLHANDLE )
       	return (MPARAM)TRUE;
      break;
    }
    case WM_TIMER :
    {
      if( mouseButtonDown )
      {
        POINTL ptl;
        WinQueryPointerPos( HWND_DESKTOP, &ptl );
        WinMapWindowPoints( HWND_DESKTOP, hWnd, &ptl, 1 );

        if( ptl.y < 0 || ptl.y > height )
        {
          Point pos( ptl.x, ptl.y );
          performMouseEvent( &pos, 0, AMouseEvent::MOVE );
        }
      }
      break;
    }
    case WM_SIZE :
    {
      int oldWidth = width, oldHeight = height;
      SWP swp;

      WinQueryWindowPos( hWndFrame, &swp );

      width = swp.cx;
      height = swp.cy;
      size( oldWidth, oldHeight );
      break;
    }
    case WM_HSCROLL :
    {
      int pos = SHORT1FROMMP( mParam2 ), id = SHORT1FROMMP( mParam1 );
      switch( SHORT2FROMMP( mParam2 ) )
      {
        case SB_PAGERIGHT :
        {
          performScrollbarEvent( id, Scrollbar::PAGERIGHT, pos );
          break;
        }
        case SB_PAGELEFT :
        {
          performScrollbarEvent( id, Scrollbar::PAGELEFT, pos );
          break;
        }
        case SB_LINERIGHT :
        {
          performScrollbarEvent( id, Scrollbar::LINERIGHT, pos );
          break;
        }
        case SB_LINELEFT :
        {
          performScrollbarEvent( id, Scrollbar::LINELEFT, pos );
          break;
        }
        case SB_SLIDERTRACK :
        {
          performScrollbarEvent( id, Scrollbar::HORZTRACK, pos );
          break;
        }
        case SB_SLIDERPOSITION :
        {
          performScrollbarEvent( id, Scrollbar::HORZRELEASED, pos );
          break;
        }
      }
      break;
    }
    case WM_SYSCOMMAND :
    {
      // Check if the parent is a dialog, then chain the WM_SYSCOMMAND

      if( parent->getType() == DIALOG )
        WinSendMsg( ((Window *)parent)->getHWND(), WM_SYSCOMMAND, mParam1, mParam2 );
      break;
    }
    case WM_VSCROLL :
    {
      int id = SHORT1FROMMP( mParam1 );
      Scrollbar *scrollbar = (Scrollbar *)getControl( id );
      int pos;
      if( scrollbar )
        pos = scrollbar->convertScrollPosToReal( SHORT1FROMMP( mParam2 ) );
      else
        pos = SHORT1FROMMP( mParam2 );

      switch( SHORT2FROMMP( mParam2 ) )
      {
        case SB_PAGEDOWN :
        {
          performScrollbarEvent( id, Scrollbar::PAGEDOWN, pos );
          break;
        }
        case SB_PAGEUP :
        {
          performScrollbarEvent( id, Scrollbar::PAGEUP, pos );
          break;
        }
        case SB_LINEDOWN :
        {
          performScrollbarEvent( id, Scrollbar::LINEDOWN, pos );
          break;
        }
        case SB_LINEUP :
        {
          performScrollbarEvent( id, Scrollbar::LINEUP, pos );
          break;
        }
        case SB_SLIDERTRACK :
        {
          performScrollbarEvent( id, Scrollbar::VERTTRACK, pos );
          break;
        }
        case SB_SLIDERPOSITION :
        {
          performScrollbarEvent( id, Scrollbar::VERTRELEASED, pos );
          break;
        }
      }
      break;
    }
    case WM_MOVE :
    {
      SWP swp;

      WinQueryWindowPos( hWndFrame, &swp );

      x = swp.x;
      y = swp.y;
      move();
      break;
    }
    case WM_CLOSE :
    {
      if( close() )
        break;
      else
        return (MPARAM)FALSE;
    }
    case WM_COMMAND :
    {
      if( SHORT1FROMMP( mParam2 ) == CMDSRC_PUSHBUTTON )
      {
        Window *control = (Window *)getControl( SHORT1FROMMP(mParam1));
        if( control != NULL )
        {
          if( control->type == PUSHBUTTON )
          {
            control->performButtonEvent( control, control->id );
            return FALSE;
          }
        }
        else
          return FALSE; // In case ESC would close the dialog
      }
      break;
    }
    case WM_CHAR :
    {
      if( type == LISTBOX )
      {
        performFocusEvent(
          (int)WinSendMsg( (HWND)mParam2, LM_QUERYSELECTION, MPARAM(0), MPARAM(NULL) ) );
      }

      if( (SHORT1FROMMP( mParam1 ) & KC_KEYUP) ||
          (SHORT1FROMMP( mParam1 ) & KC_DEADKEY) ||
          (SHORT1FROMMP( mParam1 ) & KC_INVALIDCOMP) )
        break;

/*			if( SHORT1FROMMP( mParam1 ) & KC_COMPOSITE )
				mParam1 = MPFROM2SHORT( SHORT1FROMMP( mParam1 ) & ~KC_VIRTUALKEY,
																SHORT2FROMMP( mParam1 ) );*/

      int modifiers = 0;

      if( SHORT1FROMMP( mParam1 ) & KC_SHIFT )
        modifiers |= KeyDef::SHIFT;

      if( SHORT1FROMMP( mParam1 ) & KC_ALT )
        modifiers |= KeyDef::kALT;

      if( SHORT1FROMMP( mParam1 ) & KC_CTRL)
        modifiers |= KeyDef::CTRL;

      if( SHORT1FROMMP( mParam1 ) & KC_VIRTUALKEY )
      {
        int key = 0, vKey = SHORT2FROMMP( mParam2 );

       // Maybe NumLock is on

        if( SHORT1FROMMP(mParam1) & KC_CHAR &&
            !(vKey == VK_ENTER || vKey == VK_NEWLINE || vKey == VK_TAB ||
              vKey == VK_BACKSPACE ))
          key = SHORT1FROMMP( mParam2 );
        else
        if( vKey == VK_UP )
          key = KeyDef::UP;
        else
        if( vKey == VK_DOWN )
          key = KeyDef::DOWN;
        else
        if( vKey == VK_LEFT )
          key = KeyDef::LEFT;
        else
        if( vKey == VK_RIGHT )
          key = KeyDef::RIGHT;
        else
        if( vKey == VK_PAGEUP )
          key = KeyDef::PAGEUP;
        else
        if( vKey == VK_PAGEDOWN )
          key = KeyDef::PAGEDOWN;
        else
        if( vKey == VK_INSERT )
          key = KeyDef::INSERT;
        else
        if( vKey == VK_DELETE )
          key = KeyDef::kDELETE;
        else
        if( vKey == VK_HOME )
          key = KeyDef::HOME;
        else
        if( vKey == VK_END )
          key = KeyDef::END;
        else
        if( vKey == VK_ESC )
          key = KeyDef::ESCAPE;
        else
        if( vKey == VK_F1 )
          key = KeyDef::F1;
        else
        if( vKey == VK_F2 )
          key = KeyDef::F2;
        else
        if( vKey == VK_F3 )
          key = KeyDef::F3;
        else
        if( vKey == VK_F4 )
          key = KeyDef::F4;
        else
        if( vKey == VK_F5 )
          key = KeyDef::F5;
        else
        if( vKey == VK_F6 )
          key = KeyDef::F6;
        else
        if( vKey == VK_F7 )
          key = KeyDef::F7;
        else
        if( vKey == VK_F8 )
          key = KeyDef::F8;
        else
        if( vKey == VK_F9 )
          key = KeyDef::F9;
        else
        if( vKey == VK_F10 )
          key = KeyDef::F10;
        else
        if( vKey == VK_F11 )
          key = KeyDef::F11;
        else
        if( vKey == VK_F12 )
          key = KeyDef::F12;
        else
        if( vKey == VK_ENTER )
          key = KeyDef::ENTER;
        else
        if( vKey == VK_NEWLINE )
          key = KeyDef::RETURN;
        else
        if( vKey == VK_BACKSPACE )
          key = KeyDef::BACKSPACE;
        else
        if( vKey == VK_TAB )
          key = KeyDef::TAB;
        else
        if( vKey == VK_BACKTAB )
        {
          key = KeyDef::TAB;
          modifiers |= KeyDef::SHIFT;
        }
        else
        if( vKey == VK_SPACE )
          key = KeyDef::SPACE;

	      if( parent->getType() == DIALOG )
  	    	((Dialog *)parent)->focusHotkey( key );

        if( key != 0 )
          if( performKeyEvent( this, modifiers, key ) ) return MPARAM(TRUE);

        // Do not pass up and down key to dialog if this is a combobox (would
        // move focus)

/*        if( getFilterDialogArrows() &&
            (vKey == VK_UP || vKey == VK_DOWN) )
          return (MPARAM)TRUE;*/
      }
      else
      {
        int key = SHORT1FROMMP( mParam2 );
        if( performKeyEvent( this, modifiers, key ) ) return MPARAM(TRUE);
      }
      break;
    }
    case WM_CONTROL :
    {
      Window *control = (Window *)getControl( SHORT1FROMMP(mParam1));
      if( control != NULL )
      {
        if( control->type == Window::LISTBOX ||
            control->type == Window::COMBOLISTBOX )
        {
          switch( SHORT2FROMMP(mParam1) )
          {
            case LN_KILLFOCUS : control->focus( FALSE ); break;
            case LN_SETFOCUS : control->focus( TRUE );break;
            case LN_ENTER :
              control->performSelectionEvent(
                (int)WinSendMsg( (HWND)mParam2, LM_QUERYSELECTION, MPARAM(0), MPARAM(NULL) ) );
              break;
          }
        }
        else
        if( control->type == Window::SCROLLBAR )
        {
          switch( SHORT2FROMMP(mParam1) )
          {
            case SLN_KILLFOCUS : control->focus( FALSE ); break;
            case SLN_SETFOCUS : control->setFocus(); break;
          }
        }
        else
        if( control->type == Window::RADIOBUTTON ||
            control->type == Window::CHECKBOX )
        {
          switch( SHORT2FROMMP( mParam1) )
          {
            case BN_CLICKED :
            case BN_DBLCLICKED :
              control->performButtonEvent( control, control->id );
              break;
          }
        }
      }
      break;
    }
		case DM_DRAGOVER:
		{
			PDRAGINFO pDInfo;
			PDRAGITEM pDItem;
  
	  	if( !acceptDropFiles )
				return MRFROM2SHORT(DOR_NODROPOP, 0);

			pDInfo = (PDRAGINFO)mParam1;
			DrgAccessDraginfo(pDInfo);
			pDItem = DrgQueryDragitemPtr(pDInfo, 0);
			USHORT   usOp = 0, usDrop = DOR_NEVERDROP;

			/* Inspect each item to see if it is acceptable */
			ULONG  ulItems = DrgQueryDragitemCount (pDInfo);
      for (INT i = 0; i < ulItems; i++)
			{
				pDItem = DrgQueryDragitemPtr(pDInfo, i);

				/* The item is acceptable only if it is copyable and the     */
				/* operation is a copy, or it is moveable and the operation  */
				/* is a move, and it can render <DRM_OS2FILE, NULL>          */
				if (pDItem->fsSupportedOps & DO_COPYABLE)
				{
					usOp = DO_COPY;
					/* Only check files, all types */
					if (DrgVerifyRMF(pDItem, "DRM_OS2FILE", 0))
						usDrop = DOR_DROP;
					else
					{
						usDrop = DOR_NEVERDROP;
						break;
					}
				}
				else
				{
					/* Must be a file but not droppable in type op */
					usDrop = DOR_NODROPOP;
          usOp = 0;
					break;
				}
			} /* end for all items dragged  */

			DrgFreeDraginfo(pDInfo);

			return MRFROM2SHORT(usDrop, usOp);
		}
		case DM_DROP:
		{
			PDRAGINFO pDInfo;
			PDRAGITEM pDItem;
			pDInfo = (PDRAGINFO)mParam1;
			DrgAccessDraginfo(pDInfo);
			pDItem = DrgQueryDragitemPtr(pDInfo, 0);
			ULONG  ulItems = DrgQueryDragitemCount (pDInfo);
			ULONG  p;
			char **files;

			files = (char **)malloc( sizeof( char * ) * ulItems );

			for (INT i=0; i < ulItems; i++)
			{
				CHAR    DragSrcPath[CCHMAXPATH], DragSrcName[CCHMAXPATH];
				pDItem = DrgQueryDragitemPtr(pDInfo, i);
				DrgQueryStrName(pDItem->hstrContainerName, sizeof(DragSrcPath), (PSZ)DragSrcPath);
				if (!(PSZ)DragSrcPath)
					break;
				if (DragSrcPath[(strlen(DragSrcPath)-1)] != '\\')
					strcat((PSZ)DragSrcPath, "\\");

				/* Use the dragitem source name, it's the real name */
				DrgQueryStrName(pDItem->hstrSourceName, sizeof(DragSrcName),
																									(PSZ)DragSrcName);
				if (!((PSZ)DragSrcName))
					break;
				strcat((PSZ)DragSrcPath, (PSZ)DragSrcName);
				FILESTATUS3  fsFile;
				DosError(FERR_DISABLEHARDERR);
				APIRET rc = DosQueryPathInfo(DragSrcPath, FIL_STANDARD, &fsFile,
																									sizeof(FILESTATUS3));
				DosError(FERR_ENABLEHARDERR);

				if (!rc && !(fsFile.attrFile & FILE_DIRECTORY))
				{
					files[i] = (char *)malloc( strlen(DragSrcPath) + 1 );
          strcpy( files[i], DragSrcPath );
					DrgSendTransferMsg(pDItem->hwndItem, DM_ENDCONVERSATION,
																			MPFROMLONG(pDItem->ulItemID),
																			MPFROMLONG(DMFL_TARGETSUCCESSFUL));
				}
				else
				{
					DosBeep(100,10);
//					EditorDisplay[BufNum]->DisplayMessage( pszDropNoFile );
				}
			}

			filesDropped( files, ulItems );

			for( i = 0; i < ulItems; i++ )
	      free( (void *)files[i] );

      free( (void *)files );

			DrgFreeDraginfo(pDInfo);
			break;
		}
    case WM_USER + 1 :
    {
      return (MPARAM)execFromMainThread( (int)mParam1, (void *)mParam2 );
    }
    case WM_USER + 2 :
    {
      setFocus();
      break;
    }
  }
  *returned = FALSE;
  return (MRESULT)NULL;
}