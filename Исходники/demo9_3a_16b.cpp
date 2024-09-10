int Game_Init(void *parms,  int num_parms)
{
// this function is where you do all the initialization 
// for your game

int index;         // looping var
char filename[80]; // used to build up files names

// start up DirectDraw (replace the parms as you desire)
DDraw_Init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BPP, WINDOWED_APP);

// joystick creation section ////////////////////////////////

/// start up DirectInput
DInput_Init();

// initialize the joystick
DInput_Init_Joystick(-24,24,-24,24);

///////////////////////////////////////////////////////////

// load the background
Load_Bitmap_File(&bitmap16bit, "MUSH_24.BMP");

// load in the four frames of the mushroom
for (index=0; index<4; index++)
    {
    // create mushroom bitmaps
    Create_Bitmap(&mushrooms[index],0,0,32,32,16);
    Load_Image_Bitmap16(&mushrooms[index],&bitmap16bit,index,0,BITMAP_EXTRACT_MODE_CELL);  
    } // end for index

// now create the bug blaster bob
Create_BOB(&blaster,0,0,32,32,3,
           BOB_ATTR_VISIBLE | BOB_ATTR_MULTI_ANIM | BOB_ATTR_ANIM_ONE_SHOT,
           DDSCAPS_SYSTEMMEMORY,0,16);

// load in the four frames of the mushroom
for (index=0; index < 3; index++)
     Load_Frame_BOB16(&blaster,&bitmap16bit,index,index,1,BITMAP_EXTRACT_MODE_CELL);  

// unload the bitmap file
Unload_Bitmap_File(&bitmap16bit);

// set the animation sequences for bug blaster
Load_Animation_BOB(&blaster,0,5,blaster_anim);

// set up stating state of bug blaster
Set_Pos_BOB(&blaster,320, 400);
Set_Anim_Speed_BOB(&blaster,3);

// create mushroom playfield bitmap
Create_Bitmap(&playfield,0,0,SCREEN_WIDTH,SCREEN_HEIGHT, 16);
playfield.attr |= BITMAP_ATTR_LOADED;

// fill in the background
Load_Bitmap_File(&bitmap16bit, "GRASS_24.BMP");

// load the grass bitmap image
Load_Image_Bitmap16(&playfield,&bitmap16bit,0,0,BITMAP_EXTRACT_MODE_ABS);
Unload_Bitmap_File(&bitmap16bit);

// seed random number generator
srand(Start_Clock());

// create the random mushroom patch
for (index=0; index<50; index++)
    {
    // select a mushroom
    int mush = rand()%4;

    // set mushroom to random position
    mushrooms[mush].x = rand()%(SCREEN_WIDTH-32);
    mushrooms[mush].y = rand()%(SCREEN_HEIGHT-128);

    // now draw the mushroom into playfield
    Draw_Bitmap16(&mushrooms[mush], playfield.buffer, playfield.width*2,1);

    } // end for

// hide the mouse
if (!WINDOWED_APP)
    ShowCursor(FALSE);

// return success
return(1);

} // end Game_Init