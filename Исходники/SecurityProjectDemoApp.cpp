/**********************************************************************************

Function Name = SecurityProjectDemoApp::mouseMove

Descriptive Name = Used to detect the mouseMove action and open the infected window.

Function =

    This function is used to detect the mouse move by the user and open up an infected
    window at the position where the mouse moved to. The function also
    performs additional checks to make sure that only a mousemove event is handled. 
    There are some glitches in the cinder mouse down and mouse move detection therefore
    require additional checks to make sure that it was a mouse move and not anything else.

Input =
    
    MouseEvent event - The mouse event that is detected for cinder to call the function.

Output =
   
   Creates the infected window and opens it. 
   Prints debug info also.

******************************************************************************/
void SecurityProjectDemoApp::mouseMove ( MouseEvent event )
{
    // Variable Declaration
    int mouseXDifference ;
    int mouseYDifference ;
    string messageBuffer = "" ;
    ostringstream intToStringConverter ;
    wstring stringTemp ;
    LPCWSTR debugMessage ;

    // In the case that the program has just started set the current mouse position as previous
    if ( previousMouseX == NULL && previousMouseY == NULL && startInitialized )
    {
        previousMouseX = event.getX () ;
        previousMouseY = event.getY () ;
    }
    else
    {
        // Calculate the difference between previous mouse location and current mouse location.
        mouseXDifference = abs ( previousMouseX - event.getX () ) ;
        mouseYDifference = abs ( previousMouseY - event.getY () ) ;

        // Only create the infected windows if it is initialized, the event has not already been handled, there is at least a
        // pixel difference of 5 between mouse y coordinates or mouse x coordinates, the event is not left or right click and the
        // mouseDownX and mouseDownY positions are not the same as the mouse move events.
        if ( startInitialized && event.isHandled () == false && ( mouseYDifference > 10 || mouseXDifference > 10 ) && 
             event.isLeft () == false && event.isRight () == false && mouseDownMouseX != event.getX () && mouseDownMouseY != event.getY ()
           )
        {
            // Increase the mouse move counter to show that this function was called to open up a infection window.
            // This counter will be used to allow not to open too many windows too fast or else can not actually
            // see the windows images as they open. Also the program will crash too fast as there will be a lot of
            // mouse movements. 
            mouseMoveCounter++ ;

            // ------------------------ Start of Debugging Block -----------------------------

            OutputDebugStringW ( L"\n-------------------- START Detecting the mouse moving --------------------\n" ) ;

            // Add all information that is needed into the string stream
            intToStringConverter << "Y--> " << mouseYDifference << "\n" << "X--> " << mouseXDifference << "\n" << "Mouse Move Counter--> " << mouseMoveCounter << "\n" ;

            // Fetch the string equivalence of the input (int or any other data type)
            messageBuffer = intToStringConverter.str () ;

            // Convert the messageBuffer string into wstring for later conversion
            stringTemp = wstring ( messageBuffer.begin (), messageBuffer.end () ) ;

            // Convert wstring to LPCWSTR
            debugMessage = stringTemp.c_str () ;

            OutputDebugStringW ( debugMessage ) ;
            
            OutputDebugStringW ( L"-------------------- END Detecting the mouse moving --------------------\n" );

            // ------------------------ End of Debugging Block -----------------------------

            // Only open the infection window if more then 5 mouseMoves are detected.
            if ( mouseMoveCounter > 5 )
            {
                // Create the infection window for draw function to open later
                createInfectedWindow ( loadResource ( RES_SUPPORTEDGESTURES_IMAGE ),
                                       WINDOW_X_SIZE,
                                       WINDOW_Y_SIZE,
                                       event.getX (),
                                       event.getY ()
                                     ) ;

                // Reset the mouseMove counter to 0 once a single window is opened for every 5 mouse moves.
                mouseMoveCounter = 0 ;
            }

            // Once the single event has been handled mark it as handled to make sure that
            // we avoid handling the same event multiple times.
            event.setHandled ( true );

            // Set the current mouse x and y coordinates as previous for later comparisons
            previousMouseX = event.getX ();
            previousMouseY = event.getY ();
        }
    }
}