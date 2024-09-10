LRESULT CALLBACK HostWndProcW (HWND hwnd,
                              UINT message,
                              WPARAM wParam,
                              LPARAM lParam) {
  RECT boundingRect;

 switch(message){
  /*  mousing */

  case WM_MOUSEMOVE:
      recordMouseEvent(lastMessage);
      break;

  case WM_LBUTTONDOWN:
  case WM_RBUTTONDOWN:
  case WM_MBUTTONDOWN:
    if(GetFocus() != hwnd) SetFocus(hwnd);
    SetCapture(hwnd); /* capture mouse input */
      recordMouseEvent(lastMessage);
      break;

  case WM_LBUTTONUP:
  case WM_RBUTTONUP:
  case WM_MBUTTONUP:
    if(GetFocus() != hwnd) SetFocus(hwnd);
    ReleaseCapture(); /* release mouse capture */
      recordMouseEvent(lastMessage);
      break;


  /*keyboard events*/
  case WM_KEYDOWN:
  case WM_SYSKEYDOWN:
  case WM_KEYUP:
  case WM_SYSKEYUP:
  case WM_CHAR:
  case WM_SYSCHAR:
   recordKeyboardEvent(lastMessage);
   break;


  /*window events*/
  case WM_MOVE:
  case WM_SIZE:
    if ((GetWindowRect(hwnd, &boundingRect)) != 0){

	sqWindowEvent *windowevent = (sqWindowEvent*) sqNextEventPut();
	windowevent->type = EventTypeWindow;
	windowevent->timeStamp = lastMessage ? lastMessage->time : GetTickCount();
	windowevent->action = WindowEventMetricChange;
	windowevent->value1 = boundingRect.left ;
	windowevent->value2 = boundingRect.top;
	windowevent->value3 = boundingRect.right;
	windowevent->value4 = boundingRect.bottom;
	windowevent->windowIndex =(int) hwnd;
    }
    break;
	
  case WM_PAINT:	
    if ((GetWindowRect(hwnd, &boundingRect)) != 0){

	sqWindowEvent *windowevent = (sqWindowEvent*) sqNextEventPut();
	windowevent->type = EventTypeWindow;
	windowevent->timeStamp = lastMessage ? lastMessage->time : GetTickCount();
	windowevent->action = WindowEventPaint;
	windowevent->value1 = boundingRect.left ;
	windowevent->value2 = boundingRect.top;
	windowevent->value3 = boundingRect.right;
	windowevent->value4 = boundingRect.bottom;
	windowevent->windowIndex =(int) hwnd;
    }
    break;


  case WM_CLOSE:
    {
	sqWindowEvent *windowevent = (sqWindowEvent*) sqNextEventPut();
	windowevent->type = EventTypeWindow;
	windowevent->timeStamp = lastMessage ? lastMessage->time : GetTickCount();
	windowevent->action = WindowEventClose;
	windowevent->windowIndex =(int) hwnd;
    }
    break;
	
  case WM_ACTIVATE:
    {
        sqWindowEvent *windowevent = (sqWindowEvent*) sqNextEventPut();
        windowevent->type = EventTypeWindow;
        windowevent->timeStamp = lastMessage ? lastMessage->time : GetTickCount();
        if (wParam == WA_INACTIVE) windowevent->action = WindowEventIconise;
        else windowevent->action = WindowEventActivated;
       	windowevent->windowIndex =(int) hwnd;      
    }
    break; 
    	
  case WM_GETMINMAXINFO:
    {
        sqWindowEvent *windowevent = (sqWindowEvent*) sqNextEventPut();
        windowevent->type = EventTypeWindow;
        windowevent->timeStamp = lastMessage ? lastMessage->time : GetTickCount();
        if (IsIconic(hwnd) != 0)windowevent->action = WindowEventIconise;
        else windowevent->action = WindowEventActivated;
       	windowevent->windowIndex =(int) hwnd;      
    }
    break;   
 }
 return DefWindowProcW(hwnd,message,wParam,lParam);
}