LRESULT CALLBACK winproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
 
  switch (uMsg) {
  case WM_DESTROY:    
    PostQuitMessage(0);
    break;
  case WM_CREATE:
    break;

#ifdef OO_FULLSCREEN
  case WM_SETCURSOR: {
	  SetCursor(NULL);
  } break;
#endif

  case WM_PAINT: {
	//PAINTSTRUCT PtStr;
    //windata.desthDC = BeginPaint(hWnd,&PtStr);
    //render(&windata);
    //EndPaint(hWnd,&PtStr);
  }
    break;

	case WM_ACTIVATE:
		if(  wParam==WA_INACTIVE ) {
			windata.activeWindow = oofalse;
		}
		else {
			windata.activeWindow = ootrue;
		}
		break;

 case WM_ERASEBKGND:
	 return (LRESULT)1; // this is needed to reduce flickering

  case WM_SYSKEYDOWN:
  case WM_SYSKEYUP:
  case WM_KEYDOWN:
  case WM_KEYUP: {
	  unsigned int keyCode = (unsigned int)wParam;
	  oobool keyIsDown = ((lParam & (1 << 31)) == 0);
	  oobool keyWasDown = ((lParam & (1 << 30)) != 0);


	  if( keyCode==VK_ESCAPE && keyIsDown ) {
		  windata.running = oofalse;
	  }

	  if( keyIsDown!=keyWasDown ) {
		  if( keyCode>=0 && keyCode<OOGameInput_Keys_Max ) {
			  windata.gameinput.keyboard[keyCode] = keyIsDown;
		  }
	  }
  } break;

  default:
    return DefWindowProc (hWnd, uMsg, wParam, lParam);
    break;
  }
  return 0;
}