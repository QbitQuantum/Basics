void EDA_DRAW_PANEL::OnMouseEvent( wxMouseEvent& event )
{
    int          localrealbutt = 0, localbutt = 0;
    BASE_SCREEN* screen = GetScreen();

    if( !screen )
        return;

    /* Adjust value to filter mouse displacement before consider the drag
     * mouse is really a drag command, not just a movement while click
     */
#define MIN_DRAG_COUNT_FOR_START_BLOCK_COMMAND 5

    if( event.Leaving() )
        m_canStartBlock = -1;

    if( !IsMouseCaptured() )          // No mouse capture in progress.
        m_requestAutoPan = false;

    if( GetParent()->IsActive() )
        SetFocus();
    else
        return;

    if( !event.IsButton() && !event.Moving() && !event.Dragging() )
        return;

    if( event.RightDown() )
    {
        OnRightClick( event );
        return;
    }

    if( m_ignoreMouseEvents )
        return;

    if( event.LeftIsDown() )
        localrealbutt |= GR_M_LEFT_DOWN;

    if( event.MiddleIsDown() )
        localrealbutt |= GR_M_MIDDLE_DOWN;

    if( event.LeftDown() )
        localbutt = GR_M_LEFT_DOWN;

    if( event.ButtonDClick( 1 ) )
        localbutt = GR_M_LEFT_DOWN | GR_M_DCLICK;

    if( event.MiddleDown() )
        localbutt = GR_M_MIDDLE_DOWN;

    localrealbutt |= localbutt;     // compensation default wxGTK

    INSTALL_UNBUFFERED_DC( DC, this );
    DC.SetBackground( *wxBLACK_BRUSH );

    // Compute the cursor position in drawing (logical) units.
    GetParent()->SetMousePosition( event.GetLogicalPosition( DC ) );

    int kbstat = 0;

    if( event.ShiftDown() )
        kbstat |= GR_KB_SHIFT;

    if( event.ControlDown() )
        kbstat |= GR_KB_CTRL;

    if( event.AltDown() )
        kbstat |= GR_KB_ALT;

    // Calling Double Click and Click functions :
    if( localbutt == (int) ( GR_M_LEFT_DOWN | GR_M_DCLICK ) )
    {
        GetParent()->OnLeftDClick( &DC, GetParent()->RefPos( true ) );

        // inhibit a response to the mouse left button release,
        // because we have a double click, and we do not want a new
        // OnLeftClick command at end of this Double Click
        m_ignoreNextLeftButtonRelease = true;
    }
    else if( event.LeftUp() )
    {
        // A block command is in progress: a left up is the end of block
        // or this is the end of a double click, already seen
        // Note also m_ignoreNextLeftButtonRelease can be set by
        // the call to OnLeftClick(), so do not change it after calling OnLeftClick
        bool ignoreEvt = m_ignoreNextLeftButtonRelease;
        m_ignoreNextLeftButtonRelease = false;

        if( screen->m_BlockLocate.GetState() == STATE_NO_BLOCK && !ignoreEvt )
            GetParent()->OnLeftClick( &DC, GetParent()->RefPos( true ) );

    }
    else if( !event.LeftIsDown() )
    {
        /* be sure there is a response to a left button release command
         * even when a LeftUp event is not seen.  This happens when a
         * double click opens a dialog box, and the release mouse button
         * is made when the dialog box is opened.
         */
        m_ignoreNextLeftButtonRelease = false;
    }

    if( event.ButtonDown( wxMOUSE_BTN_MIDDLE ) && m_enableMiddleButtonPan )
    {
        if( m_panScrollbarLimits )
        {
            int ppux, ppuy;
            GetScrollPixelsPerUnit( &ppux, &ppuy );
            GetViewStart( &m_PanStartCenter.x, &m_PanStartCenter.y );
            m_PanStartCenter.x *= ppux;
            m_PanStartCenter.y *= ppuy;
        }
        else
            m_PanStartCenter = GetParent()->GetScrollCenterPosition();

        m_PanStartEventPosition = event.GetPosition();

        INSTALL_UNBUFFERED_DC( dc, this );
        CrossHairOff( &dc );
    }

    if( event.ButtonUp( wxMOUSE_BTN_MIDDLE ) && m_enableMiddleButtonPan )
    {
        INSTALL_UNBUFFERED_DC( dc, this );
        CrossHairOn( &dc );
    }

    if( event.MiddleIsDown() && m_enableMiddleButtonPan )
    {
        wxPoint currentPosition = event.GetPosition();
        if( m_panScrollbarLimits )
        {
            int x, y;
            int tmpX, tmpY;
            int ppux, ppuy;
            int maxX, maxY;
            int vsizeX, vsizeY;
            int csizeX, csizeY;

            GetViewStart( &tmpX, &tmpY );
            GetScrollPixelsPerUnit( &ppux, &ppuy );
            GetVirtualSize( &vsizeX, &vsizeY );
            GetClientSize( &csizeX, &csizeY );

            maxX = vsizeX - csizeX;
            maxY = vsizeY - csizeY;

            x = m_PanStartCenter.x + m_PanStartEventPosition.x - currentPosition.x;
            y = m_PanStartCenter.y + m_PanStartEventPosition.y - currentPosition.y;

            bool shouldMoveCursor = false;

            if( x < 0 )
            {
                currentPosition.x += x;
                x = 0;
                shouldMoveCursor = true;
            }

            if( y < 0 )
            {
                currentPosition.y += y;
                y = 0;
                shouldMoveCursor = true;
            }

            if( x > maxX )
            {
                currentPosition.x += ( x - maxX );
                x = maxX;
                shouldMoveCursor = true;
            }

            if( y > maxY )
            {
                currentPosition.y += ( y - maxY );
                y = maxY;
                shouldMoveCursor = true;
            }

            if ( shouldMoveCursor )
                WarpPointer( currentPosition.x, currentPosition.y );

            Scroll( x/ppux, y/ppuy );

            double scale = GetParent()->GetScreen()->GetScalingFactor();

            wxPoint center = GetParent()->GetScrollCenterPosition();
            center.x += KiROUND( (double) ( x - tmpX ) / scale ) / ppux;
            center.y += KiROUND( (double) ( y - tmpY ) / scale ) / ppuy;
            GetParent()->SetScrollCenterPosition( center );

            Refresh();
            Update();
        }
        else
        {
            double scale = GetParent()->GetScreen()->GetScalingFactor();
            int x = m_PanStartCenter.x +
                    KiROUND( (double) ( m_PanStartEventPosition.x - currentPosition.x ) / scale );
            int y = m_PanStartCenter.y +
                    KiROUND( (double) ( m_PanStartEventPosition.y - currentPosition.y ) / scale );

            GetParent()->RedrawScreen( wxPoint( x, y ), false );
        }
    }

    if( event.ButtonUp( wxMOUSE_BTN_MIDDLE ) && !m_enableMiddleButtonPan &&
        (screen->m_BlockLocate.GetState() == STATE_NO_BLOCK) )
    {
        // The middle button has been released, with no block command:
        // We use it for a zoom center at cursor position command
        wxCommandEvent cmd( wxEVT_COMMAND_MENU_SELECTED, ID_POPUP_ZOOM_CENTER );
        cmd.SetEventObject( this );
        GetEventHandler()->ProcessEvent( cmd );
    }

    // Calling the general function on mouse changes (and pseudo key commands)
    GetParent()->GeneralControl( &DC, event.GetLogicalPosition( DC ), 0 );

    /*******************************/
    /* Control of block commands : */
    /*******************************/

    // Command block can't start if mouse is dragging a new panel
    static EDA_DRAW_PANEL* lastPanel;
    if( lastPanel != this )
    {
        m_minDragEventCount = 0;
        m_canStartBlock   = -1;
    }

    /* A new command block can start after a release buttons
     * and if the drag is enough
     * This is to avoid a false start block when a dialog box is dismissed,
     * or when changing panels in hierarchy navigation
     * or when clicking while and moving mouse
     */
    if( !event.LeftIsDown() && !event.MiddleIsDown() )
    {
        m_minDragEventCount = 0;
        m_canStartBlock   = 0;

        /* Remember the last cursor position when a drag mouse starts
         * this is the last position ** before ** clicking a button
         * this is useful to start a block command from the point where the
         * mouse was clicked first
         * (a filter creates a delay for the real block command start, and
         * we must remember this point)
         */
        m_CursorStartPos = GetParent()->GetCrossHairPosition();
    }

    if( m_enableBlockCommands && !(localbutt & GR_M_DCLICK) )
    {
        if( !screen->IsBlockActive() )
        {
            screen->m_BlockLocate.SetOrigin( m_CursorStartPos );
        }

        if( event.LeftDown() || ( !m_enableMiddleButtonPan && event.MiddleDown() ) )
        {
            if( screen->m_BlockLocate.GetState() == STATE_BLOCK_MOVE )
            {
                m_requestAutoPan = false;
                GetParent()->HandleBlockPlace( &DC );
                m_ignoreNextLeftButtonRelease = true;
            }
        }
        else if( ( m_canStartBlock >= 0 )
                && ( event.LeftIsDown() || ( !m_enableMiddleButtonPan && event.MiddleIsDown() ) )
                && !IsMouseCaptured() )
        {
            // Mouse is dragging: if no block in progress,  start a block command.
            if( screen->m_BlockLocate.GetState() == STATE_NO_BLOCK )
            {
                //  Start a block command
                int cmd_type = kbstat;

                if( !m_enableMiddleButtonPan && event.MiddleIsDown() )
                    cmd_type |= MOUSE_MIDDLE;

                // A block command is started if the drag is enough.  A small
                // drag is ignored (it is certainly a little mouse move when
                // clicking) not really a drag mouse
                if( m_minDragEventCount < MIN_DRAG_COUNT_FOR_START_BLOCK_COMMAND )
                    m_minDragEventCount++;
                else
                {
                    if( !GetParent()->HandleBlockBegin( &DC, cmd_type, m_CursorStartPos ) )
                    {
                        // should not occur: error
                        GetParent()->DisplayToolMsg(
                            wxT( "EDA_DRAW_PANEL::OnMouseEvent() Block Error" ) );
                    }
                    else
                    {
                        m_requestAutoPan = true;
                        SetCursor( wxCURSOR_SIZING );
                    }
                }
            }
        }

        if( event.ButtonUp( wxMOUSE_BTN_LEFT ) ||
            ( !m_enableMiddleButtonPan && event.ButtonUp( wxMOUSE_BTN_MIDDLE ) ) )
        {
            /* Release the mouse button: end of block.
             * The command can finish (DELETE) or have a next command (MOVE,
             * COPY).  However the block command is canceled if the block
             * size is small because a block command filtering is already
             * made, this case happens, but only when the on grid cursor has
             * not moved.
             */
            #define BLOCK_MINSIZE_LIMIT 1
            bool BlockIsSmall =
                ( std::abs( screen->m_BlockLocate.GetWidth() ) < BLOCK_MINSIZE_LIMIT )
                && ( std::abs( screen->m_BlockLocate.GetHeight() ) < BLOCK_MINSIZE_LIMIT );

            if( (screen->m_BlockLocate.GetState() != STATE_NO_BLOCK) && BlockIsSmall )
            {
                if( m_endMouseCaptureCallback )
                {
                    m_endMouseCaptureCallback( this, &DC );
                    m_requestAutoPan = false;
                }

                SetCursor( (wxStockCursor) m_currentCursor );
           }
            else if( screen->m_BlockLocate.GetState() == STATE_BLOCK_END )
            {
                m_requestAutoPan = false;
                GetParent()->HandleBlockEnd( &DC );
                SetCursor( (wxStockCursor) m_currentCursor );
                if( screen->m_BlockLocate.GetState() == STATE_BLOCK_MOVE )
                {
                    m_requestAutoPan = true;
                    SetCursor( wxCURSOR_HAND );
                }
           }
        }
    }

    // End of block command on a double click
    // To avoid an unwanted block move command if the mouse is moved while double clicking
    if( localbutt == (int) ( GR_M_LEFT_DOWN | GR_M_DCLICK ) )
    {
        if( !screen->IsBlockActive() && IsMouseCaptured() )
        {
            m_endMouseCaptureCallback( this, &DC );
        }
    }

#if 0
    wxString msg_debug;
    msg_debug.Printf( " block state %d, cmd %d",
                      screen->m_BlockLocate.GetState(),
                      screen->m_BlockLocate.GetCommand() );
    GetParent()->PrintMsg( msg_debug );
#endif

    lastPanel = this;
}