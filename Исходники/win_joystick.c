//-----------------------------------------------------------------------------
// Function: IN_StartupJoystick
// Parameters: Nothing
// Returns:     Nothing
// Notes: Pause CD audio
//-----------------------------------------------------------------------------
void IN_StartupJoystick( void )
{
        int                     numdevs;
        JOYCAPS         jc;
        MMRESULT        mmr;
        cvar_t          *cv;

        // joystick variables
        in_joystick				= Cvar_Get( "in_joystick",                              "0",            CVAR_ARCHIVE);
        joy_name				= Cvar_Get( "joy_name",                                 "joystick",     0                       );
        joy_advanced			= Cvar_Get( "joy_advanced",                             "0",            0                       );
        joy_advaxisx			= Cvar_Get( "joy_advaxisx",                             "0",            0                       );
        joy_advaxisy			= Cvar_Get( "joy_advaxisy",                             "0",            0                       );
        joy_advaxisz			= Cvar_Get( "joy_advaxisz",                             "0",            0                       );
        joy_advaxisr			= Cvar_Get( "joy_advaxisr",                             "0",            0                       );
        joy_advaxisu			= Cvar_Get( "joy_advaxisu",                             "0",            0                       );
        joy_advaxisv			= Cvar_Get( "joy_advaxisv",                             "0",            0                       );
        joy_forwardthreshold	= Cvar_Get( "joy_forwardthreshold",             "0.15",         0                       );
        joy_sidethreshold		= Cvar_Get( "joy_sidethreshold",                "0.15",         0                       );
        joy_upthreshold			= Cvar_Get( "joy_upthreshold",                  "0.15",         0                       );
        joy_pitchthreshold		= Cvar_Get( "joy_pitchthreshold",               "0.15",         0                       );
        joy_yawthreshold		= Cvar_Get( "joy_yawthreshold",                 "0.15",         0                       );
        joy_forwardsensitivity	= Cvar_Get( "joy_forwardsensitivity",   "-1",           0                       );
        joy_sidesensitivity		= Cvar_Get( "joy_sidesensitivity",              "-1",           0                       );
        joy_upsensitivity		= Cvar_Get( "joy_upsensitivity",                "-1",           0                       );
        joy_pitchsensitivity	= Cvar_Get( "joy_pitchsensitivity",             "1",            0                       );
        joy_yawsensitivity		= Cvar_Get( "joy_yawsensitivity",               "-1",           0                       );


        Cmd_AddCommand( "joy_advancedupdate", Joy_AdvancedUpdate_f );

        // assume no joystick
        joy_avail = false;

        // abort startup if user requests no joystick
        cv = Cvar_Get( "in_initjoy", "1", CVAR_ROM );
        if( ! cv->value )
                return;

        // verify joystick driver is present
        if( ( numdevs = joyGetNumDevs() ) == 0 )
        {
                return;
        }

        // cycle through the joystick ids for the first valid one
        for( joy_id = 0; joy_id < numdevs; ++joy_id )
        {
                memset( &ji, 0, sizeof( ji ) );
                ji.dwSize = sizeof( ji );
                ji.dwFlags = JOY_RETURNCENTERED;

                if( ( mmr = joyGetPosEx( joy_id, &ji ) ) == JOYERR_NOERROR )
                        break;
        }

        // abort startup if we didn't find a valid joystick
        if( mmr != JOYERR_NOERROR )
        {
                Com_Printf( "\njoystick not found -- no valid joysticks (%x)\n\n", mmr );
                return;
        }

        // get the capabilities of the selected joystick
        // abort startup if command fails
        memset( &jc, 0, sizeof( jc ) );
        if( ( mmr = joyGetDevCaps( joy_id, &jc, sizeof( jc ) ) ) != JOYERR_NOERROR )
        {
                Com_Printf( "\njoystick not found -- invalid joystick capabilities (%x)\n\n", mmr );
                return;
        }

        // save the joystick's number of buttons and POV status
        joy_numbuttons = jc.wNumButtons;
        joy_haspov = jc.wCaps & JOYCAPS_HASPOV;

        // old button and POV states default to no buttons pressed
        joy_oldbuttonstate = joy_oldpovstate = 0;

        // mark the joystick as available and advanced initialization not completed
        // this is needed as cvars are not available during initialization

        joy_avail = true;
        joy_advancedinit = false;

        Com_Printf( "\njoystick detected\n\n" );
}