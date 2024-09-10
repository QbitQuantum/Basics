//if the player pushes against a movable tile then that tile will move
void mTile:: moveTile(Dot myDot , Tile *tiles[], mTile *mtiles[], turret *turrets[] ){
    Uint8 *keystates = SDL_GetKeyState( NULL );
    
    //if both the player and the block is on the ground
    if(myDot.touches_ground(myDot.box ,tiles, mtiles, turrets) == true && wall2ground(tiles, mtiles)== true)
    {
        //if the player presses x then the movement of the mtile is mapped to the player
        if(left_collision2(myDot.box, box)== true && get_type() == Push_Tile && keystates[ SDLK_x ])
        {   
             box.x = myDot.box.x + 50;
             pull = -1;
        }
        //this applies to both right and left collision
        else if(right_collision2(myDot.box, box)== true && get_type() == Push_Tile && keystates[ SDLK_x ])
        {  
             box.x = myDot.box.x - 80;
             pull = 1;
        }
    }
    // the break-away tile
    if( get_type() == break_Tile )
    {
        if(wall2ground(tiles, mtiles)== false && ground_collision(myDot.box, box))
        {
            trap = true;
        }
        //checks if the tile is not toucing the ground and the player colliding with it
        if(trap && wall2ground(tiles, mtiles)== false)
        {
            //if the so the tile falls until it hits the ground
            box.y += 10;    
        }
    }
    //if there is nothing under a mtile it will fall
    else if(wall2ground(tiles, mtiles)== false)
    {
        box.y += 10;
    }

}