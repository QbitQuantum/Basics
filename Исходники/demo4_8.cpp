// FUNCTIONS //////////////////////////////////////////////
LRESULT CALLBACK WindowProc(HWND hwnd, 
						    UINT msg, 
                            WPARAM wparam, 
                            LPARAM lparam)
{
// this is the main message handler of the system
PAINTSTRUCT		ps;		// used in WM_PAINT
HDC				hdc;	// handle to a device context
char buffer[80];        // used to print strings

// what is the message 
switch(msg)
	{	
	case WM_CREATE: 
        {
		// do initialization stuff here
        // return success
		return(0);
		} break;

    case WM_COMMAND: // all buttons come thru here
         {
         // get the dc
         hdc = GetDC(hwnd);

         // set background mode
         SetBkMode(hdc,OPAQUE);

         // select a random text and background color
         SetTextColor(hdc,RGB(0,255,0));
         SetBkColor(hdc,RGB(128,128,128));

         // print out the wparam an lparam
         sprintf(buffer, "LOWORD(wparam) = %d, HIWORD(wparam) = %d                    ", 
                 LOWORD(wparam), HIWORD(wparam));

         // print text at a random location
         TextOut(hdc,220,100,buffer,strlen(buffer));           

         sprintf(buffer, "LOWORD(lparam) = 0X%X, HIWORD(lparam) = 0X%X                     ", 
                 LOWORD(lparam), HIWORD(lparam));

         // print text at a random location
         TextOut(hdc,220,140,buffer,strlen(buffer));      

         // release the dc
         ReleaseDC(hwnd, hdc);

         } break;
   
	case WM_PAINT: 
		{
		// simply validate the window 
   	    hdc = BeginPaint(hwnd,&ps);	 
        
        // end painting
        EndPaint(hwnd,&ps);

        // return success
		return(0);
   		} break;

	case WM_DESTROY: 
		{

		// kill the application, this sends a WM_QUIT message 
		PostQuitMessage(0);

        // return success
		return(0);
		} break;

	default:break;

    } // end switch

// process any messages that we didn't take care of 
return (DefWindowProc(hwnd, msg, wparam, lparam));

} // end WinProc