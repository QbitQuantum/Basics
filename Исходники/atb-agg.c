// Main
int main(int argc, char *argv[])
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize( 800, 600 );
    glutCreateWindow( "Font rendering advanced tweaking" );
    glutCreateMenu( NULL );

#ifndef __APPLE__
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf( stderr, "Error: %s\n", glewGetErrorString(err) );
        exit( EXIT_FAILURE );
    }
    fprintf( stderr, "Using GLEW %s\n", glewGetString(GLEW_VERSION) );
#endif

    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    atexit( terminate );
    TwInit( TW_OPENGL, NULL );
    glutMouseFunc( (GLUTmousebuttonfun)TwEventMouseButtonGLUT );
    glutMotionFunc( (GLUTmousemotionfun)TwEventMouseMotionGLUT );
    glutPassiveMotionFunc( (GLUTmousemotionfun)TwEventMouseMotionGLUT );
    glutKeyboardFunc( (GLUTkeyboardfun)TwEventKeyboardGLUT );
    glutSpecialFunc( (GLUTspecialfun)TwEventSpecialGLUT );
    TwGLUTModifiersFunc( glutGetModifiers );

    // Create a new tweak bar
    bar = TwNewBar("TweakBar");
    TwDefine("GLOBAL "
             "help = 'This example shows how to tune all font parameters.' ");
    TwDefine("TweakBar                      "
             "size          = '280 400'     "
             "position      = '500 20'      "
             "color         = '127 127 127' "
             "alpha         = 240           "
             "label         = 'Parameters'  "
             "resizable     = True          "
             "fontresizable = True          "
             "iconifiable   = True          ");

    {
        TwEnumVal familyEV[NUM_FONTS] = {
            {VERA,         "Vera"},
            {VERA_MONO,    "Vera Mono"},
            {LUCKIEST_GUY, "Luckiest Guy"},
            {SOURCE_SANS,  "Source Sans Pro"},
            {SOURCE_CODE,  "Source Code Pro"},
            {OLD_STANDARD, "Old Standard TT"},
            {LOBSTER,      "Lobster"} };
        TwType family_type = TwDefineEnum("Family", familyEV, NUM_FONTS);
        TwAddVarCB(bar, "Family", family_type, set_family, get_family, NULL, 
                   "label = 'Family'      "
                   "group = 'Font'        "
                   "help  = ' '           ");
    }
    TwAddVarCB(bar, "Size", TW_TYPE_FLOAT, set_size, get_size, NULL, 
               "label = 'Size' "
               "group = 'Font' "
               "min   = 6.0    "
               "max   = 24.0   "
               "step  = 0.05   "
               "help  = ' '    ");
    TwAddVarCB(bar, "LCD filtering", TW_TYPE_BOOL32, set_lcd_filtering, get_lcd_filtering, NULL, 
               "label = 'LCD filtering' "
              "group = 'Font'        "
               "help  = ' '             ");


    // Rendering
    TwAddVarCB(bar, "Kerning", TW_TYPE_BOOL32, set_kerning, get_kerning, NULL, 
               "label = 'Kerning'   "
               "group = 'Rendering' "
               "help  = ' '         ");
    TwAddVarCB(bar, "Hinting", TW_TYPE_BOOL32, set_hinting, get_hinting, NULL, 
               "label = 'Hinting'   "
               "group = 'Rendering' "
               "help  = ' '         ");

    // Color
    TwAddVarCB(bar, "Invert", TW_TYPE_BOOL32, set_invert, get_invert, NULL, 
               "label = 'Invert' "
               "group = 'Color'  "
               "help  = ' '      ");
    
    // Glyph
    TwAddVarCB(bar, "Width", TW_TYPE_FLOAT, set_width, get_width, NULL, 
               "label = 'Width' "
               "group = 'Glyph' "
               "min   = 0.75    "
               "max   = 1.25    " 
               "step  = 0.01    "
               "help  = ' '     ");

    TwAddVarCB(bar, "Interval", TW_TYPE_FLOAT, set_interval, get_interval, NULL, 
               "label = 'Spacing' "
               "group = 'Glyph'   "
               "min   = -0.2      "
               "max   = 0.2       "
               "step  = 0.01      "
               "help  = ' '       " );

    TwAddVarCB(bar, "Faux italic", TW_TYPE_FLOAT, set_faux_italic, get_faux_italic, NULL, 
               "label = 'Faux italic' "
               "group = 'Glyph'       "
               "min   = -30.0         "
               "max   =  30.0         "
               "step  = 0.1           "
               "help  = ' '           ");

    // Energy distribution
    TwAddVarCB(bar, "Primary", TW_TYPE_FLOAT, set_primary, get_primary, NULL,
               "label = 'Primary weight'      "
               "group = 'Energy distribution' "
               "min   = 0                     "
               "max   = 1                     "
               "step  = 0.01                  "
               "help  = ' '                   " );

    TwAddVarCB(bar, "Secondary", TW_TYPE_FLOAT, set_secondary, get_secondary, NULL,
               "label = 'Secondy weight'      "
               "group = 'Energy distribution' "
               "min   = 0                     "
               "max   = 1                     "
               "step  = 0.01                  "
               "help  = ' '                   " );

    TwAddVarCB(bar, "Tertiary", TW_TYPE_FLOAT, set_tertiary, get_tertiary, NULL,
               "label = 'Tertiary weight'      "
               "group = 'Energy distribution' "
               "min   = 0                     "
               "max   = 1                     "
               "step  = 0.01                  "
               "help  = ' '                   " );

    TwAddSeparator(bar, "",
                   "group = 'Energy distribution' " );

    TwAddVarCB(bar, "Gamma", TW_TYPE_FLOAT, set_gamma, get_gamma, NULL, 
               "label = 'Gamma correction'    "
               "group = 'Energy distribution' "
               "min   = 0.50                  "
               "max   = 2.5                   "
               "step  = 0.01                  "
               "help  = ' '                   ");

    TwAddSeparator(bar, "", "");
    TwAddButton(bar, "Reset", (TwButtonCallback) reset, NULL,
                "help='Reset all parameters to default values.'");
    TwAddSeparator(bar, "", "");
    TwAddButton(bar, "Quit", (TwButtonCallback) quit, NULL,
                "help='Quit.'");

    buffer_a = text_buffer_new( 1 ); 
    buffer_rgb = text_buffer_new( 3 ); 
    buffer = buffer_rgb;
    reset();

    glutTimerFunc( 1000.0/60.0, timer, 60 );

    mat4_set_identity( &projection );
    mat4_set_identity( &model );
    mat4_set_identity( &view );

    glutMainLoop();
    return EXIT_SUCCESS;
}