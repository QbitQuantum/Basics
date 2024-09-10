/**
 * \brief	This checks if some event was triggered to get the new input command
 * \param	device		input of which we are trying to read the event
 * \param	command		command for which we want to assign the event
 * \return 	returns true, if an event was triggered, or false if not.
 */
void CInput::readNewEvent()
{
	stInputCommand &lokalInput = InputCommand[remapper.mapDevice][remapper.mapPosition];

	// This function is used to configure new input keys.
	// For iPhone, we have emulation via touchpad and we don't want to have custom keys.
	// We should fix the menu for iPhone so that this function doesn't get called.
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
	printf("WARNING: called readNewEvent on iphone\n");
	return;
#endif

	memset(&lokalInput, 0, sizeof(stInputCommand));
	if(!m_EventList.empty())
		m_EventList.clear();

	while( SDL_PollEvent( &Event ) )
	{
		switch ( Event.type )
		{
			case SDL_QUIT:
				gLogging.textOut("SDL: Got quit event in readNewEvent!");
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
				// on iPhone, we just want to quit in this case
				exit(0);
#endif
                break;

			case SDL_KEYDOWN:
				lokalInput.joyeventtype = ETYPE_KEYBOARD;
				lokalInput.keysym = Event.key.keysym.sym;
				remapper.mappingInput = false;
				break;

			case SDL_JOYBUTTONDOWN:
#if defined(CAANOO) || defined(WIZ) || defined(GP2X)
				WIZ_EmuKeyboard( Event.jbutton.button, 1 );
				return false;
#else
				lokalInput.joyeventtype = ETYPE_JOYBUTTON;
				lokalInput.joybutton = Event.jbutton.button;
				lokalInput.which = Event.jbutton.which;
				remapper.mappingInput = false;
#endif
				break;

			case SDL_JOYAXISMOTION:

				// Deadzone check. Double, because being a
				// new event to be read it should make better to configure
				if( (Event.jaxis.value > 2*m_joydeadzone ) ||
				    (Event.jaxis.value < -2*m_joydeadzone ) )
				{
					lokalInput.joyeventtype = ETYPE_JOYAXIS;
					lokalInput.joyaxis = Event.jaxis.axis;
					lokalInput.which = Event.jaxis.which;
					lokalInput.joyvalue = (Event.jaxis.value>0) ? 32767 : -32767;
					remapper.mappingInput = false;
				}

				break;

			case SDL_JOYHATMOTION:
				lokalInput.joyeventtype = ETYPE_JOYHAT;
				lokalInput.joyhatval = Event.jhat.value;
				lokalInput.which = Event.jhat.which;
				remapper.mappingInput = false;
				break;
		}

        flushAll();
    }
}