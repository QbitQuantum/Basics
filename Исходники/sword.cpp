SDL_Rect sword :: get_position(Dot myDot, Setup foo)
{
    if(look_up)
    {
        box.x = myDot.box.x;
        box.y = (myDot.box.y - le) + properHeight;
        weaponsT.loadFromFile( "first_test12.bmp" );

    }

    else if(look_down && !myDot.is_onGround())                      ///very much so temp--- this should be its own move, once i get moves sorted :D
    {
        box.x = myDot.box.x;
        box.y = myDot.box.y + myDot.box.h;
        weaponsT.loadFromFile( "first_test11.bmp" );
    }

    else
    {

         if(!direction)
         {
             box.x = myDot.box.x +  trueWidth;
             weaponsT.loadFromFile( "first_test10.bmp" );
         }
         else
         {
             box.x = (myDot.box.x - 128) + (128 - trueWidth);
             weaponsT.loadFromFile( "first_test9.bmp" );
         }
         box.y = myDot.box.y + trueHeight/2;
         return box;
    }
}