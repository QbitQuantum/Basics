int Game_Init(void *parms)
{
// this function is where you do all the initialization
// for your game

    int index; // looping var

// start up DirectDraw (replace the parms as you desire)
    DDraw_Init2(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BPP, WINDOWED_APP,1);

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
    Init_CAM4DV1(&cam,      // the camera object
                 CAM_MODEL_EULER, // the euler model
                 &cam_pos,  // initial camera position
                 &cam_dir,  // initial camera angles
                 &cam_target,      // no target
                 10.0,        // near and far clipping planes
                 12000.0,
                 120.0,      // field of view in degrees
                 WINDOW_WIDTH,   // size of final screen viewport
                 WINDOW_HEIGHT);

// set a scaling vector
    VECTOR4D_INITXYZ(&vscale,20.00,20.00,20.00);

// load all the objects in
    for (int index_obj=0; index_obj < NUM_OBJECTS; index_obj++)
    {
        Load_OBJECT4DV2_COB2(&obj_array[index_obj], object_filenames[index_obj],
                             &vscale, &vpos, &vrot, VERTEX_FLAGS_SWAP_YZ  |
                             VERTEX_FLAGS_TRANSFORM_LOCAL
                             /* VERTEX_FLAGS_TRANSFORM_LOCAL_WORLD*/,0 );

    } // end for index_obj

// set current object
    curr_object = 0;
    obj_work = &obj_array[curr_object];

// load in the scenery object that we will place all over the place
    Load_OBJECT4DV2_COB2(&obj_scene, "fire_cube01.cob",
                         &vscale, &vpos, &vrot, VERTEX_FLAGS_SWAP_YZ  |
                         VERTEX_FLAGS_TRANSFORM_LOCAL
                         /* VERTEX_FLAGS_TRANSFORM_LOCAL_WORLD*/, 0);

// position the scenery objects randomly
    for (index = 0; index < NUM_SCENE_OBJECTS; index++)
    {
        // randomly position object
        scene_objects[index].x = RAND_RANGE(-UNIVERSE_RADIUS, UNIVERSE_RADIUS);
        scene_objects[index].y = RAND_RANGE(-200, 200);
        scene_objects[index].z = RAND_RANGE(-UNIVERSE_RADIUS, UNIVERSE_RADIUS);
    } // end for

// set up lights
    Reset_Lights_LIGHTV2(lights2, MAX_LIGHTS);

// create some working colors
    white.rgba = _RGBA32BIT(255,255,255,0);
    gray.rgba  = _RGBA32BIT(100,100,100,0);
    black.rgba = _RGBA32BIT(0,0,0,0);
    red.rgba   = _RGBA32BIT(255,0,0,0);
    green.rgba = _RGBA32BIT(0,255,0,0);
    blue.rgba  = _RGBA32BIT(0,0,255,0);
    orange.rgba = _RGBA32BIT(255,128,0,0);
    yellow.rgba  = _RGBA32BIT(255,255,0,0);


// ambient light
    Init_Light_LIGHTV2(lights2,               // array of lights to work with
                       AMBIENT_LIGHT_INDEX,
                       LIGHTV2_STATE_ON,      // turn the light on
                       LIGHTV2_ATTR_AMBIENT,  // ambient light type
                       gray, black, black,    // color for ambient term only
                       NULL, NULL,            // no need for pos or dir
                       0,0,0,                 // no need for attenuation
                       0,0,0);                // spotlight info NA

    VECTOR4D dlight_dir = {-1,0,-1,1};

// directional light
    Init_Light_LIGHTV2(lights2,               // array of lights to work with
                       INFINITE_LIGHT_INDEX,
                       LIGHTV2_STATE_ON,      // turn the light on
                       LIGHTV2_ATTR_INFINITE, // infinite light type
                       black, gray, black,    // color for diffuse term only
                       NULL, &dlight_dir,     // need direction only
                       0,0,0,                 // no need for attenuation
                       0,0,0);                // spotlight info NA


    VECTOR4D plight_pos = {0,200,0,1};

// point light
    Init_Light_LIGHTV2(lights2,               // array of lights to work with
                       POINT_LIGHT_INDEX,
                       LIGHTV2_STATE_ON,      // turn the light on
                       LIGHTV2_ATTR_POINT,    // pointlight type
                       black, yellow, black,    // color for diffuse term only
                       &plight_pos, NULL,     // need pos only
                       0,.002,0,              // linear attenuation only
                       0,0,1);                // spotlight info NA


    VECTOR4D slight2_pos = {0,1000,0,1};
    VECTOR4D slight2_dir = {-1,0,-1,1};

// spot light2
    Init_Light_LIGHTV2(lights2,                  // array of lights to work with
                       SPOT_LIGHT2_INDEX,
                       LIGHTV2_STATE_ON,         // turn the light on
                       LIGHTV2_ATTR_SPOTLIGHT2,  // spot light type 2
                       black, red, black,        // color for diffuse term only
                       &slight2_pos, &slight2_dir, // need pos only
                       0,.001,0,                 // linear attenuation only
                       0,0,1);


// create lookup for lighting engine
    RGB_16_8_IndexedRGB_Table_Builder(DD_PIXEL_FORMAT565,  // format we want to build table for
                                      palette,             // source palette
                                      rgblookup);          // lookup table

// create the z buffer
    Create_Zbuffer(&zbuffer,
                   WINDOW_WIDTH,
                   WINDOW_HEIGHT,
                   ZBUFFER_ATTR_32BIT);

// create the alpha table
    RGB_Alpha_Table_Builder(NUM_ALPHA_LEVELS, rgb_alpha_table);

// load in the background
    Create_BOB(&background, 0,0,800,600,1, BOB_ATTR_VISIBLE | BOB_ATTR_SINGLE_FRAME, DDSCAPS_SYSTEMMEMORY, 0, 16);
    Load_Bitmap_File(&bitmap16bit, "nebred01.bmp");
    Load_Frame_BOB16(&background, &bitmap16bit,0,0,0,BITMAP_EXTRACT_MODE_ABS);
    Unload_Bitmap_File(&bitmap16bit);

// return success
    return(1);

} // end Game_Init