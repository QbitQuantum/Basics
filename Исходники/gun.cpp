void gun:: weaponControl(Dot myDot)
{
 // Uint8 *keystates = SDL_GetKeyState( NULL );
    Mix_PlayChannel( -1, gunSound, 0 );
    if(!direction)
    {
        right = true;
        left = false;
    }
    else
    {
        left = true;
        right = false;
    }

    if(up)
    {
         look_up = true;
         right = false;
         left = false;
    }

    else
    {
         look_up = false;
    }

    if(down && !myDot.is_onGround())
    {
         look_down = true;
    }

    else
    {
         look_down = false;
    }

    for( int p = 0; p < 20; p++ )
    {
        particles[ p ] = new Particle( box.x, box.y, 4);
    }

}