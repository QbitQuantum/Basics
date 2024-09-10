/* adjust_window:
 *  Moves and resizes the window if we have full control over it.
 */
int adjust_window(int w, int h)
{
   RECT working_area, win_size;
   TITLEBARINFO tb_info;
   HMODULE user32_handle;
   typedef BOOL (WINAPI *func)(HWND, PTITLEBARINFO);
   func get_title_bar_info = NULL;
   int tb_height = 0;
   static int last_w=-1, last_h=-1;

   if (!user_wnd) {
      SystemParametersInfo(SPI_GETWORKAREA, 0, &working_area, 0);

      if ((last_w == -1) && (last_h == -1)) {
         /* first window placement: try to center it */
         last_wnd_x = (working_area.left + working_area.right - w)/2;
         last_wnd_y = (working_area.top + working_area.bottom - h)/2;
      }
      else {
         /* try to get the height of the window's title bar */
         user32_handle = GetModuleHandle("user32");
         if (user32_handle) {
            get_title_bar_info
               = (func)GetProcAddress(user32_handle, "GetTitleBarInfo");
            if (get_title_bar_info) {
               tb_info.cbSize = sizeof(TITLEBARINFO);
               if (get_title_bar_info(allegro_wnd, &tb_info))
                  tb_height
                     = tb_info.rcTitleBar.bottom - tb_info.rcTitleBar.top;
            }
         }
         if (!user32_handle || !get_title_bar_info)
            tb_height = GetSystemMetrics(SM_CYSIZE);
         
	 /* try to center the window relative to its last position */
	 last_wnd_x += (last_w - w)/2;
	 last_wnd_y += (last_h - h)/2;
	 
	 if (last_wnd_x + w >= working_area.right)
	    last_wnd_x = working_area.right - w;
	 if (last_wnd_y + h >= working_area.bottom)
	    last_wnd_y = working_area.bottom - h;
	 if (last_wnd_x < working_area.left)
	    last_wnd_x = working_area.left;
	 if (last_wnd_y - tb_height < working_area.top)
	    last_wnd_y = working_area.top + tb_height;
      }

#ifdef ALLEGRO_COLORCONV_ALIGNED_WIDTH
      last_wnd_x &= 0xfffffffc;
#endif

      win_size.left = last_wnd_x;
      win_size.top = last_wnd_y;
      win_size.right = last_wnd_x+w;
      win_size.bottom = last_wnd_y+h;

      last_w = w;
      last_h = h;

      /* retrieve the size of the decorated window */
      AdjustWindowRect(&win_size, GetWindowLong(allegro_wnd, GWL_STYLE), FALSE);
   
      /* display the window */
      MoveWindow(allegro_wnd, win_size.left, win_size.top,
                 win_size.right - win_size.left, win_size.bottom - win_size.top, TRUE);

      /* check that the actual window size is the one requested */
      GetClientRect(allegro_wnd, &win_size);
      if (((win_size.right - win_size.left) != w) || ((win_size.bottom - win_size.top) != h))
         return -1;

      wnd_x = last_wnd_x;
      wnd_y = last_wnd_y;
      wnd_width = w;
      wnd_height = h;
   }

   return 0;
}