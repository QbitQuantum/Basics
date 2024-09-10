int PASCAL WinMain( HINSTANCE instance,
                    HINSTANCE previous_instance,
                    LPSTR cmd_line,
                    int cmd_show )
{
  //
  // Win32 locals.
  //

  HWND window = 0;
  MSG msg;

  //
  // Try to create our window.
  //

  window = Build_window_handle( instance,
                                previous_instance );
  if ( !window )
  {
    MessageBox( 0,
                "Error creating window.",
                "Windows",
                MB_OK | MB_ICONSTOP );
    return( 1 );
  }

  //
  // Tell Bink to use DirectSound (must be before BinkOpen)!
  //

  BinkSoundUseDirectSound( 0 );

  //
  // Try to open the Bink file.
  //
  
  Bink = BinkOpen( cmd_line, 0 );
  if ( !Bink )
  {
    MessageBox( window,
                BinkGetError( ),
                "Bink Error",
                MB_OK | MB_ICONSTOP );

    DestroyWindow( window );
    return( 3 );
  }

  //
  // Try to open the Bink buffer.
  //

  Bink_buffer = BinkBufferOpen( window, Bink->Width, Bink->Height, 0 );
  if ( !Bink_buffer )
  {
    MessageBox( window,
                BinkBufferGetError( ),
                "Bink Error",
                MB_OK | MB_ICONSTOP );

    DestroyWindow( window );
    BinkClose( Bink );

    return( 4 );
  }

  //
  // Size the window such that its client area exactly fits our Bink movie.
  //

  SetWindowPos( window, 0,
                0, 0,
                Bink_buffer->WindowWidth,
                Bink_buffer->WindowHeight,
                SWP_NOMOVE );

  //
  // Now display the window and start the message loop.
  //

  ShowWindow( window, cmd_show );

  for ( ; ; )
  {
    //
    // Are there any messages to handle?
    //

    if ( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )
    {
      //
      // Yup, handle them.
      //

      if ( msg.message == WM_QUIT )
        break;

      TranslateMessage( &msg );
      DispatchMessage( &msg );
    }
    else
    {
      //
      // Is it time for a new Bink frame?
      //

      if ( !BinkWait( Bink ) )
      {
        //
        // Yup, draw the next frame.
        //

        Show_next_frame( Bink,
                         Bink_buffer,
                         window );
      }
      else
      {
        //
        // Nope, give the rest of the system a chance to run (500 MICROseconds).
        //

        Good_sleep_us( 500 );
      }

    }
  }

  //
  // Close the Bink file.
  //

  if ( Bink )
  {
    BinkClose( Bink );
    Bink = 0;
  }

  //
  // Close the Bink buffer.
  //

  if ( Bink_buffer )
  {
    BinkBufferClose( Bink_buffer );
    Bink_buffer = 0;
  }

  //
  // And exit.
  //

  return( 0 );
}