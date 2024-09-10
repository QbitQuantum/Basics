//------------------------------------------------------------
void ofAppNoWindow::runAppViaInfiniteLoop(ofBaseApp * appPtr) {
    static ofEventArgs voidEventArgs;

    ofAppPtr = appPtr;

    if(ofAppPtr) {
        ofAppPtr->setup();
        ofAppPtr->update();
    }

#if defined TARGET_OSX || defined TARGET_LINUX
    // for keyboard
    set_conio_terminal_mode();
#endif

#ifdef OF_USING_POCO
    ofNotifyEvent( ofEvents().setup, voidEventArgs );
    ofNotifyEvent( ofEvents().update, voidEventArgs );
#endif

    ofLogNotice()<<	"***\n***\n*** ofAppNoWindow running a headerless openFrameworks app\n"
                 "***\n*** keyboard input works here\n"
                 "***\n*** press Esc or Ctrl-C to quit\n"
                 "***\n";

    // Register signal handler to handle kill signal
    signalHandler.setupSignalHandlers();

    while (true)
    {
        if (nFrameCount != 0 && bFrameRateSet == true) {
            diffMillis = ofGetElapsedTimeMillis() - prevMillis;
            if (diffMillis > millisForFrame) {
                ; // we do nothing, we are already slower than target frame
            } else {
                int waitMillis = millisForFrame - diffMillis;
#ifdef TARGET_WIN32
                Sleep(waitMillis);         //windows sleep in milliseconds
#else
                usleep(waitMillis * 1000);   //mac sleep in microseconds - cooler :)
#endif
            }
        }
        prevMillis = ofGetElapsedTimeMillis(); // you have to measure here


        /// listen for escape
#ifdef TARGET_WIN32
        if (GetAsyncKeyState(VK_ESCAPE))
            OF_EXIT_APP(0);
#endif

#if defined TARGET_OSX || defined TARGET_LINUX
        while ( kbhit() )
        {
            int key = getch();
            if ( key == 27 )
            {
                if(ofAppPtr) {
                    ofAppPtr->exit();
                }
                exitApp();
            }
            if (key == 'q' || key == 'Q')
            {
                if(ofAppPtr) {
                    ofAppPtr->exit();
                }
                exitApp();
            }
            else if ( key == /* ctrl-c */ 3 )
            {
                if(ofAppPtr) {
                    ofAppPtr->exit();
                }
                ofLogNotice()<<	"Ctrl-C pressed\n";
                exitApp();
            }
            else
            {
                ofAppPtr->keyPressed( key );
            }
        }
#endif


        /// update
        if (ofAppPtr)
            ofAppPtr->update();

#ifdef OF_USING_POCO
        ofNotifyEvent( ofEvents().update, voidEventArgs);
#endif

        // Check for exit signal
        if (signalHandler.gotExitSignal()) {
            if(ofAppPtr) {
                ofAppPtr->exit();
            }
            exitApp();
        }


        // -------------- fps calculation:
        timeNow = ofGetElapsedTimef();
        double diff = timeNow-timeThen;
        if( diff  > 0.00001 ) {
            fps			= 1.0 / diff;
            frameRate	*= 0.9f;
            frameRate	+= 0.1f*fps;
        }
        lastFrameTime	= diff;
        timeThen		= timeNow;
        // --------------

        nFrameCount++;		// increase the overall frame count

    }
}