int Game_Init(void *parms,  int num_parms)
{
// this function is where you do all the initialization 
// for your game

int index;         // looping var
char filename[80]; // used to build up files names

// start up DirectDraw (replace the parms as you desire)
DDraw_Init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BPP, WINDOWED_APP);

// joystick creation section ////////////////////////////////

// first create the direct input object
if (DirectInput8Create(main_instance,DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&lpdi,NULL)!=DI_OK)
   return(0);

// first find the f*****g GUID of your particular joystick
lpdi->EnumDevices(DI8DEVCLASS_GAMECTRL, 
                  DI_Enum_Joysticks, 
                  &joystickGUID, 
                  DIEDFL_ATTACHEDONLY | DIEDFL_FORCEFEEDBACK); 

if (lpdi->CreateDevice(joystickGUID, &lpdijoy, NULL)!=DI_OK)
   return(0);

// set cooperation level
if (lpdijoy->SetCooperativeLevel(main_window_handle, 
	                 DISCL_EXCLUSIVE | DISCL_BACKGROUND)!=DI_OK)
   return(0);

// set data format
if (lpdijoy->SetDataFormat(&c_dfDIJoystick2)!=DI_OK)
   return(0);

// set the range of the joystick
DIPROPRANGE joy_axis_range;

// first x axis
joy_axis_range.lMin = -32;
joy_axis_range.lMax = 32;

joy_axis_range.diph.dwSize       = sizeof(DIPROPRANGE); 
joy_axis_range.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
joy_axis_range.diph.dwObj        = DIJOFS_X;
joy_axis_range.diph.dwHow        = DIPH_BYOFFSET;

lpdijoy->SetProperty(DIPROP_RANGE,&joy_axis_range.diph);

// now y-axis
joy_axis_range.lMin = -32;
joy_axis_range.lMax = 32;

joy_axis_range.diph.dwSize       = sizeof(DIPROPRANGE); 
joy_axis_range.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
joy_axis_range.diph.dwObj        = DIJOFS_Y;
joy_axis_range.diph.dwHow        = DIPH_BYOFFSET;

lpdijoy->SetProperty(DIPROP_RANGE,&joy_axis_range.diph);

// and now the dead band

DIPROPDWORD dead_band; // here's our property word

dead_band.diph.dwSize       = sizeof(dead_band);
dead_band.diph.dwHeaderSize = sizeof(dead_band.diph);
dead_band.diph.dwObj        = DIJOFS_X;
dead_band.diph.dwHow        = DIPH_BYOFFSET;

// 4 will be used on both sides of the range +/-
dead_band.dwData            = 1000;

// finally set the property
lpdijoy->SetProperty(DIPROP_DEADZONE,&dead_band.diph);

dead_band.diph.dwSize       = sizeof(dead_band);
dead_band.diph.dwHeaderSize = sizeof(dead_band.diph);
dead_band.diph.dwObj        = DIJOFS_Y;
dead_band.diph.dwHow        = DIPH_BYOFFSET;

// 4 will be used on both sides of the range +/-
dead_band.dwData            = 1000;

// finally set the property
lpdijoy->SetProperty(DIPROP_DEADZONE,&dead_band.diph);


// acquire the joystick
if (lpdijoy->Acquire()!=DI_OK)
   return(0);


// force feedback setup
DWORD      dwAxes[2] = { DIJOFS_X, DIJOFS_Y };
LONG       lDirection[2] = { 0, 0 };


DIPERIODIC diPeriodic;      // type-specific parameters
DIENVELOPE diEnvelope;      // envelope
DIEFFECT   diEffect;        // general parameters

// setup the periodic structure
diPeriodic.dwMagnitude = DI_FFNOMINALMAX; 
diPeriodic.lOffset = 0; 
diPeriodic.dwPhase = 0; 
diPeriodic.dwPeriod = (DWORD) (0.05 * DI_SECONDS); 

// set the modulation envelope 
diEnvelope.dwSize = sizeof(DIENVELOPE);
diEnvelope.dwAttackLevel = 0; 
diEnvelope.dwAttackTime = (DWORD) (0.01 * DI_SECONDS); 
diEnvelope.dwFadeLevel = 0; 
diEnvelope.dwFadeTime = (DWORD) (3.0 * DI_SECONDS); 
 
// set up the effect structure itself
diEffect.dwSize = sizeof(DIEFFECT); 
diEffect.dwFlags = DIEFF_POLAR | DIEFF_OBJECTOFFSETS; 
diEffect.dwDuration = (DWORD) INFINITE; // (1 * DI_SECONDS);
 
// set up details of effect
diEffect.dwSamplePeriod = 0;               // = default 
diEffect.dwGain = DI_FFNOMINALMAX;         // no scaling
diEffect.dwTriggerButton = DIJOFS_BUTTON0; // connect effect to trigger button
diEffect.dwTriggerRepeatInterval = 0;      
diEffect.cAxes = 2; 
diEffect.rgdwAxes = dwAxes; 
diEffect.rglDirection = &lDirection[0]; 
diEffect.lpEnvelope = &diEnvelope; 
diEffect.cbTypeSpecificParams = sizeof(diPeriodic);
diEffect.lpvTypeSpecificParams = &diPeriodic;  
 
// create the effect and get the interface to it 
lpdijoy->CreateEffect(GUID_Square,  // standard GUID 
                     &diEffect,      // where the data is
                     &lpdieffect,    // where to put interface pointer
                     NULL);          // no aggregation


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
for (index=0; index<3; index++)
     Load_Frame_BOB16(&blaster,&bitmap16bit,index,index,1,BITMAP_EXTRACT_MODE_CELL);  

// unload the bitmap file
Unload_Bitmap_File(&bitmap16bit);

// set the animation sequences for bug blaster
Load_Animation_BOB(&blaster,0,5,blaster_anim);

// set up stating state of bug blaster
Set_Pos_BOB(&blaster,320, 400);
Set_Anim_Speed_BOB(&blaster,3);

// create mushroom playfield bitmap
Create_Bitmap(&playfield,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,16);
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