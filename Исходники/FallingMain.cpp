int WINAPI WinMain(	HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int ncmdshow)
{

	WNDCLASS winclass;	// this will hold the class created
	HWND	 hwnd;		// generic window handle
	MSG		 msg;		// generic message
	HDC      hdc;       // generic dc
	RECT rect;
	float velocity[15];
	int ball_y[15],
		ball_x[15],
		iEndPos[15],
		index=0;
	LARGE_INTEGER a;
	__int64 b=0,c=0, diffrenceC_B=0;

	//fill in the window class stucture
	winclass.style			= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc	= WindowProc;
	winclass.cbClsExtra		= 0;
	winclass.cbWndExtra		= 0;
	winclass.hInstance		= hinstance;
	winclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground	= (HBRUSH) GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName	= NULL; //MAKEINTRESOURCE(IDR_MENU1);
	winclass.lpszClassName	= WINDOW_CLASS_NAME;

	// register the window class
	if (!RegisterClass(&winclass))
		return(0);

	// create the window
	if (!(hwnd = CreateWindow(WINDOW_CLASS_NAME, // class
							  "Bouncing on the desktop",	 // title
							  WS_OVERLAPPEDWINDOW | WS_VISIBLE,
						 	  0,600,	   // x,y
							  WINDOW_WIDTH,  // width
						      WINDOW_HEIGHT, // height
							  NULL,	   // handle to parent 
							  NULL,	   // handle to menu
							  hinstance,// instance
							  NULL)))	// creation parms
	{
		MessageBox(hwnd, "Window Could not be Created", NULL, MB_OK); //NULL is default for Error
		return(0);
	}

	// save the window handle and instance in a global
	main_window_handle = hwnd;
	main_instance      = hinstance;

	for(index=0; index<=14; index++) //start balls at random positions, set velocity = 0
	{
		ball_y[index]= -10;
		ball_x[index]= rand()%1000;
		iEndPos[index]= rand()%900;
		velocity[index]= 0;
	}
	
	index=0; //reset index

	// enter main event loop
	while(1)
	{
		//check messages
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{ 
			// test if this is a quit message
			if (msg.message == WM_QUIT)
				break;
	
			// translate any accelerator keys
			TranslateMessage(&msg);

			// send the message to the window proc
			DispatchMessage(&msg);
		} // end if
		if(KEY_DOWN(VK_ESCAPE)) //if hit the Esc key quit the program
			PostQuitMessage(0);
		
		if(!QueryPerformanceCounter(&a))
		{
			MessageBox(hwnd, "Error on QueryPerformanceCounter()", NULL, MB_OK); //NULL is default for Error
			return(0);
		}
		else
		{
			b = c = a.QuadPart;
		}	

	   	hdc= GetDC(hwnd);
		
		//--------Begin Text Info---------------------
		SetBkMode(hdc, TRANSPARENT); //set background color
		//first create the eraser string for variable text
		SetTextColor(hdc,RGB(0,255,0)); //set text color black
		TextOut(hdc, 30, 60, buffer, strlen(buffer)); //print text
		TextOut(hdc, 30, 75, buffer2, strlen(buffer2)); //print text
		
		//unvarieing text
		SetTextColor(hdc,RGB(0,255,0)); //set text color black
		TextOut(hdc, 30, 15,"Keys 0-6 set the delay time", strlen("Keys 0-6 set the delay time")); //print text
		TextOut(hdc, 30, 30,"Left and right arrows change gravity", strlen("Left and right arrows change gravity")); //print text
		TextOut(hdc, 30, 45,"Up and down arrows change friction", strlen("Up and down arrows change friction")); //print text
		TextOut(hdc, 30, 90,"S key starts over", strlen("S key starts over")); //print text
		
		//variable text
		sprintf(buffer,"Friction= ", friction);
		sprintf(buffer2,"Gravity= ", gravity);
		TextOut(hdc, 30, 60, buffer, strlen(buffer)); //print text
		TextOut(hdc, 30, 75, buffer2, strlen(buffer2)); //print text
		//--------End Text Info-------------------------

		ReleaseDC(hwnd, hdc);
		
		
		hdc= GetWindowDC(GetDesktopWindow());
		
		//-------------Erasing ball----------------
		//fill in rect struct for erasing ball
		rect.left = ball_x[index] - BALL_RADIUS5;
		rect.right = ball_x[index] + BALL_RADIUS5;
		rect.top = ball_y[index] - BALL_RADIUS5;
		rect.bottom = ball_y[index] + BALL_RADIUS5;
		
		//Draw erasing ball in the old position
		SelectObject(hdc, red_pen5);
		SelectObject(hdc, red_brush5);
		Ellipse(hdc,rect.left, rect.top, rect.right, rect.bottom);
		
		//------------End Erasing ball----------------

		//-------------Test to see whats going on-----------
		//if the ball hits the ground, bounce back. The reason its here is because the erasing ball
		//needs the old position to erase the drawing ball.
		if(ball_y[index] >= iEndPos[index]) 
		{
			//velocity[index] = -velocity[index];
			ball_y[index] = iEndPos[index]; //need to rest the y position because of >=, the y could be > 370
		}
		
		//allows user to restart balls in a new possition if they want to
		//the reason its put here is so that if the user decides to restart, the erasing ball
		//will erase the drawing ball, and won't leave ball marks all over.
		if(startOver) 
		{
			for(index=0; index<=14; index++) //start balls at random positions, set velocity = 0
			{
				ball_y[index]= -10;
				ball_x[index]= rand()%2000;
				iEndPos[index]= rand()%900;
				velocity[index]= 0;
			}//end for loop on index
			
			startOver= false; //reset startOver back to false 
		}//end if on startOver

		//--------------End Test to see whats going on
		
		//-------------- Move the ball--------------
		velocity[index]+= gravity* ( (diffrenceC_B*0.0009)*0.02);
		velocity[index]*= friction;
		ball_y[index]+= (int) velocity[index];
		//-------------End Move the ball------------

		//---------------Draw the Ball------------------
		//Redraw the ball in its new position
	
		//fill in rect struct for drawing ball
		//ball 5
		rect.left = ball_x[index] - BALL_RADIUS5;
		rect.right = ball_x[index] + BALL_RADIUS5;
		rect.top = ball_y [index] - BALL_RADIUS5;
		rect.bottom = ball_y[index] + BALL_RADIUS5;
		
		//Draw the ball in its new spot
		SelectObject(hdc, red_pen5);
		SelectObject(hdc, red_brush5);
		Ellipse(hdc,rect.left, rect.top, rect.right, rect.bottom);
		//end ball 5

		//ball 4
		rect.left = ball_x[index] - BALL_RADIUS4;
		rect.right = ball_x[index] + BALL_RADIUS4;
		rect.top = ball_y [index] - BALL_RADIUS4;
		rect.bottom = ball_y[index] + BALL_RADIUS4;
		
		//Draw the ball in its new spot
		SelectObject(hdc, red_pen4);
		SelectObject(hdc, red_brush4);
		Ellipse(hdc,rect.left, rect.top, rect.right, rect.bottom);
		//end ball 4

		//ball 3
		rect.left = ball_x[index] - BALL_RADIUS3;
		rect.right = ball_x[index] + BALL_RADIUS3;
		rect.top = ball_y [index] - BALL_RADIUS3;
		rect.bottom = ball_y[index] + BALL_RADIUS3;
		
		//Draw the ball in its new spot
		SelectObject(hdc, red_pen3);
		SelectObject(hdc, red_brush3);
		Ellipse(hdc,rect.left, rect.top, rect.right, rect.bottom);
		//end ball 3

		//ball 2
		rect.left = ball_x[index] - BALL_RADIUS2;
		rect.right = ball_x[index] + BALL_RADIUS2;
		rect.top = ball_y [index] - BALL_RADIUS2;
		rect.bottom = ball_y[index] + BALL_RADIUS2;
		
		//Draw the ball in its new spot
		SelectObject(hdc, red_pen2);
		SelectObject(hdc, red_brush2);
		Ellipse(hdc,rect.left, rect.top, rect.right, rect.bottom);
		//end ball 2

		//ball 1
		rect.left = ball_x[index] - BALL_RADIUS1;
		rect.right = ball_x[index] + BALL_RADIUS1;
		rect.top = ball_y [index] - BALL_RADIUS1;
		rect.bottom = ball_y[index] + BALL_RADIUS1;
		
		//Draw the ball in its new spot
		SelectObject(hdc, red_pen1);
		SelectObject(hdc, red_brush1);
		Ellipse(hdc,rect.left, rect.top, rect.right, rect.bottom);
		//end ball 1
		//----------------End draw the ball---------------s

		//if index increments to 14 (or last ball) start drawing from the
		//begining again over again (meaning draw ball b0, b1,...b14 start back at b1)
		index++;
		if(index >=14)
			index=0;
		
		if(!QueryPerformanceCounter(&a))
		{
			MessageBox(hwnd, "Error on QueryPerformanceCounter()", NULL, MB_OK); //NULL is default for Error
			return(0);
		}
		else
		{
			c = a.QuadPart;
			diffrenceC_B= c-b;
		}	
		
		//slow things down a bit
		//Sleep(delay);
				
		//Release device context
		ReleaseDC(GetDesktopWindow(), hdc);
		
	} // end while

	

	// return to Windows like this
	return(msg.wParam);

} // end WinMain