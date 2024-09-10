int Game_Init(void *parms)
{
// this function is where you do all the initialization 
// for your game

int index; // looping var

// start up DirectDraw (replace the parms as you desire)
DDraw_Init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BPP, WINDOWED_APP);

// initialize directinput
DInput_Init();

// acquire the keyboard 
DInput_Init_Keyboard();

// add calls to acquire other directinput devices here...

// initialize directsound and directmusic
DSound_Init();
DMusic_Init();

// hide the mouse
if (!WINDOWED_APP)
    ShowCursor(FALSE);

// seed random number generator
srand(Start_Clock()); 

Open_Error_File("ERROR.TXT");

// initialize math engine
Build_Sin_Cos_Tables();

// initialize the camera with 90 FOV, normalized coordinates
Init_CAM4DV1(&cam,            // the camera object
             CAM_MODEL_EULER, // the euler model
             &cam_pos,        // initial camera position
             &cam_dir,        // initial camera angles
             &cam_target,     // no target
             40.0,            // near and far clipping planes
             12000.0,
             90.0,            // field of view in degrees
             WINDOW_WIDTH,    // size of final screen viewport
             WINDOW_HEIGHT);

VECTOR4D terrain_pos = {0,0,0,0};

Generate_Terrain_OBJECT4DV2(&obj_terrain,            // pointer to object
                            TERRAIN_WIDTH,           // width in world coords on x-axis
                            TERRAIN_HEIGHT,          // height (length) in world coords on z-axis
                            TERRAIN_SCALE,           // vertical scale of terrain
                            "checkerheight01.bmp",  // filename of height bitmap encoded in 256 colors
                            "checker256256.bmp",   // filename of texture map
                             RGB16Bit(255,255,255),  // color of terrain if no texture        
                             &terrain_pos,           // initial position
                             NULL,                   // initial rotations
                             POLY4DV2_ATTR_RGB16  
                             | POLY4DV2_ATTR_SHADE_MODE_FLAT 
                             // | POLY4DV2_ATTR_SHADE_MODE_GOURAUD
                             | POLY4DV2_ATTR_SHADE_MODE_TEXTURE);

// the shading attributes we would like


// set up lights
Reset_Lights_LIGHTV2(lights2, MAX_LIGHTS);

// create some working colors
white.rgba = _RGBA32BIT(255,255,255,0);
gray.rgba  = _RGBA32BIT(100,100,100,0);
black.rgba = _RGBA32BIT(0,0,0,0);
red.rgba   = _RGBA32BIT(255,0,0,0);
green.rgba = _RGBA32BIT(0,255,0,0);
blue.rgba  = _RGBA32BIT(0,0,255,0);

// ambient light
Init_Light_LIGHTV2(lights2,
                   AMBIENT_LIGHT_INDEX,   
                   LIGHTV2_STATE_ON,      // turn the light on
                   LIGHTV2_ATTR_AMBIENT,  // ambient light type
                   gray, black, black,    // color for ambient term only
                   NULL, NULL,            // no need for pos or dir
                   0,0,0,                 // no need for attenuation
                   0,0,0);                // spotlight info NA

VECTOR4D dlight_dir = {-1,1,-1,1};

// directional light
Init_Light_LIGHTV2(lights2,
                   INFINITE_LIGHT_INDEX,  
                   LIGHTV2_STATE_ON,      // turn the light on
                   LIGHTV2_ATTR_INFINITE, // infinite light type
                   black, gray, black,    // color for diffuse term only
                   NULL, &dlight_dir,     // need direction only
                   0,0,0,                 // no need for attenuation
                   0,0,0);                // spotlight info NA


VECTOR4D plight_pos = {0,200,0,1};

// point light
Init_Light_LIGHTV2(lights2,
                   POINT_LIGHT_INDEX,
                   LIGHTV2_STATE_ON,      // turn the light on
                   LIGHTV2_ATTR_POINT,    // pointlight type
                   black, green, black,   // color for diffuse term only
                   &plight_pos, NULL,     // need pos only
                   0,.001,0,              // linear attenuation only
                   0,0,1);                // spotlight info NA


// point light
Init_Light_LIGHTV2(lights2,
                   POINT_LIGHT2_INDEX,
                   LIGHTV2_STATE_ON,     // turn the light on
                   LIGHTV2_ATTR_POINT,   // pointlight type
                   black, blue, black,   // color for diffuse term only
                   &plight_pos, NULL,    // need pos only
                   0,.002,0,            // linear attenuation only
                   0,0,1);               // spotlight info NA

VECTOR4D slight2_pos = {0,200,0,1};
VECTOR4D slight2_dir = {-1,1,-1,1};


// create lookup for lighting engine
RGB_16_8_IndexedRGB_Table_Builder(DD_PIXEL_FORMAT565,  // format we want to build table for
                                  palette,             // source palette
                                  rgblookup);          // lookup table

// create the z buffer
Create_Zbuffer(&zbuffer,
               WINDOW_WIDTH,
               WINDOW_HEIGHT,
               ZBUFFER_ATTR_32BIT);


// load background sounds
wind_sound_id = DSound_Load_WAV("WIND.WAV");

// start the sounds
DSound_Play(wind_sound_id, DSBPLAY_LOOPING);
DSound_Set_Volume(wind_sound_id, 100);

#if 0
// load in the cockpit image
Load_Bitmap_File(&bitmap16bit, "lego01.BMP");
Create_BOB(&cockpit, 0,0,800,600,1, BOB_ATTR_VISIBLE | BOB_ATTR_SINGLE_FRAME, DDSCAPS_SYSTEMMEMORY, 0, 16); 
Load_Frame_BOB16(&cockpit, &bitmap16bit,0,0,0,BITMAP_EXTRACT_MODE_ABS);
Unload_Bitmap_File(&bitmap16bit);
#endif

// set single precission
//_control87( _PC_24, MCW_PC );

// return success
return(1);

} // end Game_Init