void MoviePlayerView::UpdateUI( const VrFrame & vrFrame )
{
	// only show cursor when uiActive
	if ( uiActive )
	{
		const Matrix4f screenModel = Cinema.app->GetActivityPanel().Matrix;

		// -1 to 1 range on panelMatrix, returns -2,-2 if looking away from the panel
		const Vector2f cursor = GazeCoordinatesOnPanel( Cinema.SceneMgr.Scene.CenterViewMatrix(), screenModel, Cinema.app->GetActivityPanel().AlternateGazeCheck );

		const bool press = ( vrFrame.Input.buttonPressed & ( BUTTON_A | BUTTON_TOUCH ) ) != 0;
		const bool release = ( ( vrFrame.Input.buttonReleased & ( BUTTON_A | BUTTON_TOUCH ) ) != 0 );

		ePlaybackControlsEvent uiButtonPressed = ( ePlaybackControlsEvent )Native::GazeCursor( Cinema.app, (cursor.x * 0.5 + 0.5) * Cinema.app->GetActivityPanel().Width,
			(0.5 - cursor.y * 0.5) * Cinema.app->GetActivityPanel().Height, press, release, SeekSpeed );

		// don't register a button press if we just finished a swipe
		if ( !( vrFrame.Input.buttonState & BUTTON_TOUCH_WAS_SWIPE ) )
		{
			switch( uiButtonPressed )
			{
			case UI_RW_PRESSED :
				// rewind
				Cinema.app->PlaySound( "touch_up" );
				if ( SeekSpeed == 0 )
				{
					Native::PauseMovie( Cinema.app );
					PlaybackPos = Native::GetPosition( Cinema.app );
				}

				SeekSpeed--;
				if ( ( SeekSpeed == 0 ) || ( SeekSpeed < -MaxSeekSpeed ) )
				{
					SeekSpeed = 0;
					Native::ResumeMovie( Cinema.app );
				}
				break;

			case UI_PLAY_PRESSED :
				// play/pause
				Cinema.app->PlaySound( "touch_up" );
				Native::TogglePlaying( Cinema.app );
				SeekSpeed = 0;
				break;

			case UI_FF_PRESSED :
				// fast forward
				Cinema.app->PlaySound( "touch_up" );
				if ( SeekSpeed == 0 )
				{
					Native::PauseMovie( Cinema.app );
					PlaybackPos = Native::GetPosition( Cinema.app );
				}

				SeekSpeed++;
				if ( ( SeekSpeed == 0 ) || ( SeekSpeed > MaxSeekSpeed ) )
				{
					SeekSpeed = 0;
					Native::ResumeMovie( Cinema.app );
				}
				break;

			case UI_CAROUSEL_PRESSED :
				// movie select
				Cinema.app->PlaySound( "touch_up" );
				Cinema.MovieSelection( false );
				break;

			case UI_CLOSE_UI_PRESSED :
				Cinema.app->PlaySound( "touch_up" );
				HideUI();
				Native::ResumeMovie( Cinema.app );
				break;

			case UI_USER_TIMEOUT :
				HideUI();
				Native::ResumeMovie( Cinema.app );
				break;

			case UI_SEEK_PRESSED :
				PlaybackPos = Native::GetPosition( Cinema.app );
				NextSeekTime = TimeInSeconds() + 0.25;
				break;

			default:
			case UI_NO_EVENT :
				break;
			}
		}

		float cursorDistance = FLT_MAX;
		eGazeCursorStateType cursorState = CURSOR_STATE_NORMAL;

		if ( InsideUnit( cursor ) )
		{
			// FIXME: Project onto Free Screen
			const Vector3f pos = screenModel.Transform( Vector3f( cursor.x, cursor.y, 0.0f ) );
			cursorDistance = ( pos - Cinema.SceneMgr.Scene.CenterViewMatrix().GetTranslation() ).Length();
		}
		Cinema.app->GetGazeCursor().UpdateForUser( GazeUserId, cursorDistance, cursorState );
	}
}