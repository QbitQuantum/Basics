static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message){
	    case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	    case WM_CLOSE:
			mplayer_put_key(KEY_CLOSE_WIN);
			break;
		case WM_WINDOWPOSCHANGED:
           {
                int tmpheight=0;
                /*calculate new window rect*/       
                 if(!vo_fs){
                 RECT rd;
                 POINT point_window;
                 if(!hWnd)hWnd=hwnd;  
                 ShowCursor(TRUE);              
                 point_window.x = 0;
                 point_window.y = 0;
                 ClientToScreen(hWnd,&point_window);  
                 GetClientRect(hWnd,&rd);
                      
                 vo_dwidth=rd.right - rd.left;
                 vo_dheight=rd.bottom - rd.top;                       
                 vo_dx =point_window.x;
                 vo_dy =point_window.y;
          //       aspect(&vo_dwidth, &vo_dheight, A_NOZOOM);

                 /* keep aspect on resize, borrowed from vo_directx.c */
                 tmpheight = ((float)vo_dwidth/window_aspect);
                 tmpheight += tmpheight % 2;
                 if(tmpheight > vo_dheight)
                 {
                     vo_dwidth = ((float)vo_dheight*window_aspect);
                     vo_dwidth += vo_dwidth % 2;
                 }
                 else vo_dheight = tmpheight;
                 rd.right = rd.left + vo_dwidth;
                 rd.bottom = rd.top + vo_dheight;

                 if(rd.left < 0) rd.left = 0;
                 if(rd.right > vo_screenwidth) rd.right = vo_screenwidth;
                 if(rd.top < 0) rd.top = 0;
                 if(rd.bottom > vo_screenheight) rd.bottom = vo_screenheight;

                 AdjustWindowRect(&rd, WS_OVERLAPPEDWINDOW | WS_SIZEBOX, 0);
                 SetWindowPos(hWnd, HWND_TOPMOST, vo_dx+rd.left, vo_dy+rd.top, rd.right-rd.left, rd.bottom-rd.top, SWP_NOOWNERZORDER); 
               }
               else {
                 if(ShowCursor(FALSE)>=0)while(ShowCursor(FALSE)>=0){}       
                 aspect(&vo_dwidth, &vo_dheight, A_ZOOM);
                 vo_dx = (vo_screenwidth - vo_dwidth)/2;
                 vo_dy = (vo_screenheight - vo_dheight)/2;           
               }                 
               /*update vidix*/
               /* FIXME: implement runtime resize/move if possible, this way is very ugly! */
	           vidix_stop();
	           if(vidix_init(image_width, image_height, vo_dx, vo_dy, vo_dwidth, vo_dheight, image_format, vo_depthonscreen, vo_screenwidth, vo_screenheight) != 0)
	               mp_msg(MSGT_VO, MSGL_FATAL, "Can't initialize VIDIX driver: %s\n", strerror(errno));
               /*set colorkey*/       
               vidix_start();
               mp_msg(MSGT_VO, MSGL_V, "[winvidix] window properties: pos: %dx%d, size: %dx%d\n",vo_dx, vo_dy, vo_dwidth, vo_dheight);
               if(vidix_grkey_support()){
                 vidix_grkey_get(&gr_key);
	             gr_key.key_op = KEYS_PUT;
	             gr_key.ckey.op = CKEY_TRUE;
	             if(vo_fs)gr_key.ckey.red = gr_key.ckey.green = gr_key.ckey.blue = 0;
                 else {
                   gr_key.ckey.red = gr_key.ckey.blue = 255;
                   gr_key.ckey.green = 0;
	             }              
                 vidix_grkey_set(&gr_key);
               }         
    
           }
           break;
        case WM_SYSCOMMAND:
	        switch (wParam){
                case SC_SCREENSAVE:                
		        case SC_MONITORPOWER:
                    return 0;                      
			 }
             break;       
        case WM_KEYDOWN:
			switch (wParam){
				case VK_LEFT:
					{mplayer_put_key(KEY_LEFT);break;}      
                case VK_UP:
					{mplayer_put_key(KEY_UP);break;} 
                case VK_RIGHT:
					{mplayer_put_key(KEY_RIGHT);break;} 
	            case VK_DOWN:
					{mplayer_put_key(KEY_DOWN);break;} 
	            case VK_TAB:
					{mplayer_put_key(KEY_TAB);break;}
		        case VK_CONTROL:
					{mplayer_put_key(KEY_CTRL);break;}
		        case VK_DELETE:
					{mplayer_put_key(KEY_DELETE);break;}
		        case VK_INSERT:
					{mplayer_put_key(KEY_INSERT);break;}
		        case VK_HOME:
					{mplayer_put_key(KEY_HOME);break;}
		        case VK_END:
					{mplayer_put_key(KEY_END);break;}
		        case VK_PRIOR:
			        {mplayer_put_key(KEY_PAGE_UP);break;}
		        case VK_NEXT:
			        {mplayer_put_key(KEY_PAGE_DOWN);break;}
		        case VK_ESCAPE:
					{mplayer_put_key(KEY_ESC);break;}
			}
            break;
        case WM_CHAR:
			mplayer_put_key(wParam);
			break;
    }
	return DefWindowProc(hwnd, message, wParam, lParam);
}