/******************************************************************************************
	Process real-time game lights
*******************************************************************************************/
void ProcessRTLights( void )
{
    int j;
    RT_LIGHT *light;
    XLIGHT *xlight;
    RT_FIXED_LIGHT *fixed;
    RT_PULSING_LIGHT *pulse;
    RT_FLICKERING_LIGHT *flicker;
    RT_SPOT_LIGHT *spot;
    float chance;
    MATRIX rotmat;

    for ( j = 0; j < rt_lights; j++ )
    {
        light = &rt_light[ j ];
        if ( light->xlight == (u_int16_t) -1 )
            continue; // only happens if run out of XLIGHTs
        xlight = &XLights[ light->xlight ];
        if ( light->delay > 0.0F )
        {
            light->delay -= framelag;
            if ( light->delay <= 0.0F )
            {
                light->enabled = true;
            }
        }
        if ( light->enabled )
        {
            switch ( light->type )
            {
            case LIGHT_FIXED:
                fixed = &light->fixed;
                switch ( light->state )
                {
                case STATE_OFF:
                    light->now_time = 0.0F;
                    xlight->Visible = false;
                    light->intensity = 0.0F;
                    break;
                case STATE_TURNING_ON:
                    if ( light->delay < 0.0F )
                    {
                        light->now_time += -light->delay;
                        light->delay = 0.0F;
                    }
                    else
                        light->now_time += framelag;
                    xlight->Visible = true;
                    if ( light->now_time < fixed->on_time )
                    {
                        InterpLightOn( light, light->now_time / fixed->on_time, fixed->on_type );
                    }
                    else
                    {
                        xlight->r = light->r;
                        xlight->g = light->g;
                        xlight->b = light->b;
                        xlight->Visible = true;
                        light->state = STATE_ON;
                    }
                    break;
                case STATE_ON:
                    xlight->r = light->r;
                    xlight->g = light->g;
                    xlight->b = light->b;
                    xlight->Visible = true;
                    break;
                case STATE_TURNING_OFF:
                    light->now_time += framelag;
                    xlight->Visible = true;
                    if ( light->now_time < fixed->off_time )
                    {
                        InterpLightOff( light, light->now_time / fixed->off_time, fixed->off_type );
                    }
                    else
                    {
                        light->state = STATE_OFF;
                        light->now_time = 0.0F;
                        xlight->Visible = false;
                    }
                    break;
                }
                break;
            case LIGHT_PULSING:
                pulse = &light->pulse;
                if ( light->delay < 0.0F )
                {
                    light->now_time += -light->delay;
                    light->delay = 0.0F;
                }
                else
                    light->now_time += framelag;
                if ( light->now_time > pulse->total_time )
                {
                    light->now_time = FMOD( light->now_time, pulse->total_time );
                }
                if ( light->now_time < pulse->on_time )
                {
                    // light is turning on
                    light->state = STATE_TURNING_ON;
                    InterpLightOn( light, light->now_time / pulse->on_time, pulse->type );
                    xlight->Visible = true;
                }
                else if ( light->now_time < pulse->stay_on_point )
                {
                    // light is staying on
                    light->state = STATE_ON;
                    xlight->r = light->r;
                    xlight->g = light->g;
                    xlight->b = light->b;
                    xlight->Visible = true;
                }
                else if ( light->now_time < pulse->off_point )
                {
                    // light is turning off
                    light->state = STATE_TURNING_OFF;
                    InterpLightOff( light, ( light->now_time - pulse->stay_on_point ) / pulse->off_time, pulse->type );
                    xlight->Visible = true;
                }
                else // light->now_time < pulse->total_time
                {
                    // light is staying off
                    light->state = STATE_OFF;
                    xlight->Visible = false;
                }
                break;
            case LIGHT_FLICKERING:
                flicker = &light->flicker;
                chance = RANDOM();
                if ( light->delay < 0.0F )
                {
                    light->now_time += -light->delay;
                    light->delay = 0.0F;
                }
                else
                    light->now_time += framelag;
                if ( light->state == STATE_ON )
                {
                    // check chance of switching off
                    if ( light->now_time > flicker->stay_on_time &&
                            chance > flicker->stay_on_chance )
                    {
                        light->state = STATE_OFF;
                        light->now_time = 0.0F;
                        xlight->Visible = false;
                    }
                }
                else // light is off
                {
                    // check chance of switching on
                    if ( light->now_time > flicker->stay_off_time &&
                            chance > flicker->stay_off_chance )
                    {
                        light->state = STATE_ON;
                        light->now_time = 0.0F;
                        xlight->Visible = true;
                    }
                }
                break;
            case LIGHT_SPOT:
                spot = &light->spot;
                if ( spot->rotation_speed )
                {
                    // rotate spotlight beam
                    if ( light->delay < 0.0F )
                    {
                        light->now_time += -light->delay;
                        light->delay = 0.0F;
                    }
                    else
                        light->now_time += framelag;
                    spot->angle = light->now_time * spot->rotation_speed;
                    if ( spot->angle > TWO_PI )
                        spot->angle = FMOD( spot->angle, TWO_PI );
                    MatrixFromAxisAndAngle( spot->angle, &spot->up, &rotmat );
                    ApplyMatrix( &rotmat, &spot->dir, &xlight->Dir );
                    NormaliseVector( &xlight->Dir );
                }
                light->state = STATE_ON;
                xlight->Visible = true;
                break;
            }
        }
        else
        {
            // light is disabled, check if turning off
            if ( light->state == STATE_TURNING_OFF )
            {
                switch ( light->type )
                {
                case LIGHT_FIXED:
                    fixed = &light->fixed;
                    light->now_time += framelag;
                    if ( light->now_time < fixed->off_time )
                    {
                        InterpLightOff( light, light->now_time / fixed->off_time, fixed->off_type );
                        xlight->Visible = true;
                    }
                    else
                    {
                        light->state = STATE_OFF;
                        light->now_time = 0.0F;
                        xlight->Visible = false;
                    }
                    break;
                case LIGHT_PULSING:
                    pulse = &light->pulse;
                    light->now_time += framelag;
                    if ( light->now_time < pulse->off_time )
                    {
                        InterpLightOff( light, light->now_time / pulse->off_time, pulse->type );
                        xlight->Visible = true;
                    }
                    else
                    {
                        light->state = STATE_OFF;
                        light->now_time = 0.0F;
                        xlight->Visible = false;
                    }
                    break;
                case LIGHT_FLICKERING:
                    light->state = STATE_OFF;
                    xlight->Visible = false;
                    break;
                case LIGHT_SPOT:
                    light->state = STATE_OFF;
                    xlight->Visible = false;
                    break;
                }
            }
            else if ( light->delay <= 0.0F )
            {
                light->state = STATE_OFF;
                xlight->Visible = false;
            }
        }
    }
}