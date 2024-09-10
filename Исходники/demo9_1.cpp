int Game_Init(void *parms,  int num_parms)
{
// this function is where you do all the initialization 
// for your game

int index;         // looping var
char filename[80]; // used to build up files names

// initialize directdraw
DDraw_Init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP);


#if 0 // directinput7 method

// first create the direct input object
if (DirectInputCreateEx(main_instance,DIRECTINPUT_VERSION,IID_IDirectInput7, (void **)&lpdi,NULL)!=DI_OK)
   return(0);

// create a keyboard device  //////////////////////////////////
if (lpdi->CreateDeviceEx(GUID_SysKeyboard, IID_IDirectInputDevice7, (void **)&lpdikey, NULL)!=DI_OK)
   return(0);

#endif


// first create the direct input object
if (DirectInput8Create(main_instance,DIRECTINPUT_VERSION,IID_IDirectInput8, (void **)&lpdi,NULL)!=DI_OK)
   return(0);

// create a keyboard device  //////////////////////////////////
if (lpdi->CreateDevice(GUID_SysKeyboard, &lpdikey, NULL)!=DI_OK)
   return(0);


// set cooperation level
if (lpdikey->SetCooperativeLevel(main_window_handle, 
                 DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)!=DI_OK)
    return(0);

// set data format
if (lpdikey->SetDataFormat(&c_dfDIKeyboard)!=DI_OK)
   return(0);

// acquire the keyboard
if (lpdikey->Acquire()!=DI_OK)
   return(0);

///////////////////////////////////////////////////////////

// load the background
Load_Bitmap_File(&bitmap8bit, "REACTOR.BMP");

// set the palette to background image palette
Set_Palette(bitmap8bit.palette);

// create and load the reactor bitmap image
Create_Bitmap(&reactor, 0,0, 640, 480);
Load_Image_Bitmap(&reactor,&bitmap8bit,0,0,BITMAP_EXTRACT_MODE_ABS);
Unload_Bitmap_File(&bitmap8bit);

// now let's load in all the frames for the skelaton!!!

// create skelaton bob
if (!Create_BOB(&skelaton,0,0,56,72,32,
           BOB_ATTR_VISIBLE | BOB_ATTR_MULTI_ANIM,DDSCAPS_SYSTEMMEMORY))
   return(0);

// load the frames in 8 directions, 4 frames each
// each set of frames has a walk and a fire, frame sets
// are loaded in counter clockwise order looking down
// from a birds eys view or the x-z plane
for (int direction = 0; direction < 8; direction++)
    { 
    // build up file name
    sprintf(filename,"SKELSP%d.BMP",direction);

    // load in new bitmap file
    Load_Bitmap_File(&bitmap8bit,filename);
 
    Load_Frame_BOB(&skelaton,&bitmap8bit,0+direction*4,0,0,BITMAP_EXTRACT_MODE_CELL);  
    Load_Frame_BOB(&skelaton,&bitmap8bit,1+direction*4,1,0,BITMAP_EXTRACT_MODE_CELL);  
    Load_Frame_BOB(&skelaton,&bitmap8bit,2+direction*4,2,0,BITMAP_EXTRACT_MODE_CELL);  
    Load_Frame_BOB(&skelaton,&bitmap8bit,3+direction*4,0,1,BITMAP_EXTRACT_MODE_CELL);  

    // unload the bitmap file
    Unload_Bitmap_File(&bitmap8bit);

    // set the animation sequences for skelaton
    Load_Animation_BOB(&skelaton,direction,4,skelaton_anims[direction]);

    } // end for direction

// set up stating state of skelaton
Set_Animation_BOB(&skelaton, 0);
Set_Anim_Speed_BOB(&skelaton, 4);
Set_Vel_BOB(&skelaton, 0,0);
Set_Pos_BOB(&skelaton, 0, 128);

// set clipping rectangle to screen extents so mouse cursor
// doens't mess up at edges
RECT screen_rect = {0,0,screen_width,screen_height};
lpddclipper = DDraw_Attach_Clipper(lpddsback,1,&screen_rect);

// hide the mouse
ShowCursor(FALSE);

// return success
return(1);

} // end Game_Init