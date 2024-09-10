int main(int argc, char* argv[])
{
        int nRetVal;
	XnStatus rc;
	EnumerationErrors errors;

        // get playback file if using 
        if (argc > 2 && strcmp(argv[2], "true") == 0) {
            rc = g_context.Init();

            rc = g_context.OpenFileRecording(RECORDING_PATH, g_player);
            CHECK_RC(rc, "Opening file");

            rc = g_player.SetRepeat(TRUE);
	    CHECK_RC(rc, "Turn repeat off");
        } else {
            // get context from xml
	    rc = g_context.InitFromXmlFile(SAMPLE_XML_PATH, g_scriptNode, &errors);
        }

        // error checking
	if (rc == XN_STATUS_NO_NODE_PRESENT)
	{
		XnChar strError[1024];
		errors.ToString(strError, 1024);
		printf("%s\n", strError);
		return (rc);
	}
	CHECK_RC(rc, "Context initialization");        

        // get hand and image generator from context, check errors
	rc = g_context.FindExistingNode(XN_NODE_TYPE_IMAGE, g_image);
	CHECK_RC(rc, "Get image generator");

        rc = g_context.FindExistingNode(XN_NODE_TYPE_HANDS, g_hands);
	CHECK_RC(rc, "Get hand generator");       
       
        rc = g_context.FindExistingNode(XN_NODE_TYPE_GESTURE, g_gesture);
        CHECK_RC(rc, "Get gesture generator");

        // create and register callbacks
        XnCallbackHandle h1, h2;
        g_gesture.RegisterGestureCallbacks(Gesture_Recognized,
                                              Gesture_Process,
                                              NULL, h1);
        CHECK_RC(rc, "Get register gesture callback");     
  
        g_hands.RegisterHandCallbacks(Hand_Create, Hand_Update,
                                           Hand_Destroy, NULL, h2);
        CHECK_RC(rc, "Get hand callback");

        // add gestures to the generator
        rc = g_gesture.AddGesture("Click", NULL);
        CHECK_RC(rc, " add click gesture");
        rc = g_gesture.AddGesture("RaiseHand", NULL);
        CHECK_RC(rc, "add raise gesture");
        rc = g_gesture.AddGesture("Wave", NULL);
        CHECK_RC(rc, "add wave gesture");

        
	g_image.GetMetaData(g_imageMD);

	// RGB is the only image format supported.
	if (g_imageMD.PixelFormat() != XN_PIXEL_FORMAT_RGB24)
	{
		printf("The device image format must be RGB24\n");
		return 1;
	}

        // if argument is set true, then record the session
        if (argc > 1 && strcmp(argv[1], "true") == 0) {
            std::cout << "recording to " << RECORDING_PATH << std::endl;
            // Create Recorder
            rc = recorder.Create(g_context);
            CHECK_RC(rc, "create recorder");

            // Init it
            rc = recorder.SetDestination(XN_RECORD_MEDIUM_FILE, RECORDING_PATH);
            CHECK_RC(rc, "init recorder");

            // Add nodes to recording
            rc = recorder.AddNodeToRecording(g_image);
            CHECK_RC(rc, "add image node");
            
            rc = recorder.AddNodeToRecording(g_hands);
            CHECK_RC(rc, "add hands node");
        }

        // initialize and run program
	glutInit(&argc, argv);                                      // GLUT initialization
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );  // Display Mode
	glutInitWindowSize(WIDTH, HEIGHT);	// set window size
        glutInitWindowPosition(GL_WIN_POSITION_X, GL_WIN_POSITION_Y);
	glutCreateWindow(TITLE);	        // create Window
	glutDisplayFunc(glutDisplay);		// register Display Function
	glutIdleFunc(glutDisplay);		// register Idle Function
        glutKeyboardFunc(glutKeyboard );	// register Keyboard Handler
	initialize();
	glutMainLoop();	

        CleanUpExit();
	return 0;
}