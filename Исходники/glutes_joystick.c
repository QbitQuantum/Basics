/*
 * Read the raw joystick data
 */
static void fghJoystickRawRead( SFG_Joystick* joy, int* buttons, float* axes )
{
#ifdef WIN32
    MMRESULT status;
#else
    int status;
#endif

    int i;

    if( joy->error )
    {
        if( buttons )
            *buttons = 0;

        if( axes )
            for( i=0; i<joy->num_axes; i++ )
                axes[ i ] = 1500.0f;

        return;
    }

#ifdef WIN32
    status = joyGetPosEx( joy->js_id, &joy->js );

    if( status != JOYERR_NOERROR )
    {
        joy->error = GL_TRUE;
        return;
    }

    if( buttons )
        *buttons = joy->js.dwButtons;

    if( axes )
    {
        /*
         * WARNING - Fall through case clauses!!
         */
        switch( joy->num_axes )
        {
        case 6: axes[5] = (float) joy->js.dwVpos;
        case 5: axes[4] = (float) joy->js.dwUpos;
        case 4: axes[3] = (float) joy->js.dwRpos;
        case 3: axes[2] = (float) joy->js.dwZpos;
        case 2: axes[1] = (float) joy->js.dwYpos;
        case 1: axes[0] = (float) joy->js.dwXpos;
        }
    }
#else
#   ifdef JS_NEW

    while( 1 )
    {
        status = read( joy->fd, &joy->js, sizeof(struct js_event) );

        if( status != sizeof( struct js_event ) )
        {
            if( errno == EAGAIN )
            {
                /*
                 * Use the old values
                 */
                if( buttons )
                    *buttons = joy->tmp_buttons;
                if( axes )
                    memcpy( axes, joy->tmp_axes,
                            sizeof( float ) * joy->num_axes );
                return;
            }

            fgWarning( "%s", joy->fname );
            joy->error = GL_TRUE;
            return;
        }

        switch( joy->js.type & ~JS_EVENT_INIT )
        {
        case JS_EVENT_BUTTON:
            if( joy->js.value == 0 ) /* clear the flag */
                joy->tmp_buttons &= ~( 1 << joy->js.number );
            else
                joy->tmp_buttons |= ( 1 << joy->js.number );
            break;

        case JS_EVENT_AXIS:
            joy->tmp_axes[ joy->js.number ] = ( float )joy->js.value;
            
            if( axes )
                memcpy( axes, joy->tmp_axes, sizeof(float) * joy->num_axes );
            break;
        }

        if( buttons )
            *buttons = joy->tmp_buttons;
    }
#   else

    status = read( joy->fd, &joy->js, JS_RETURN );

    if( status != JS_RETURN )
    {
        fgWarning( "%s", joy->fname );
        joy->error = GL_TRUE;
        return;
    }

    if( buttons )
#       if defined( __FreeBSD__ ) || defined( __NetBSD__ )
        *buttons = ( joy->js.b1 ? 1 : 0 ) | ( joy->js.b2 ? 2 : 0 );
#       else
        *buttons = joy->js.buttons;
#       endif

    if( axes )
    {
        axes[ 0 ] = (float) joy->js.x;
        axes[ 1 ] = (float) joy->js.y;
    }
#   endif
#endif
}