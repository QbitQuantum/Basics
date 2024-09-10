/* render_proc:
 *  Timer proc that updates the window.
 */
static void render_proc(void)
{
   int top_line, bottom_line;
   HDC hdc = NULL;
   HWND allegro_wnd = win_get_window();

   /* to prevent reentrant calls */
   if (render_semaphore)
      return;

   render_semaphore = TRUE;

   /* to prevent the drawing threads and the rendering proc
    * from concurrently accessing the dirty lines array.
    */
   _enter_gfx_critical();

   if (!gdi_screen) {
      _exit_gfx_critical();
      render_semaphore = FALSE;
      return;
   }

   /* pseudo dirty rectangles mechanism:
    *  at most only one GDI call is performed for each frame,
    *  a true dirty rectangles mechanism makes the demo game
    *  unplayable in 640x480 on my system.
    */

   /* find the first dirty line */
   top_line = 0;

   while (!gdi_dirty_lines[top_line])
      top_line++;

   if (top_line < gfx_gdi.h) {
      /* find the last dirty line */
      bottom_line = gfx_gdi.h-1;

      while (!gdi_dirty_lines[bottom_line])
         bottom_line--;

      hdc = GetDC(allegro_wnd);

      if (_color_depth == 8)
         set_palette_to_hdc(hdc, palette);

      blit_to_hdc(gdi_screen, hdc, 0, top_line, 0, top_line,
                  gfx_gdi.w, bottom_line - top_line + 1);

      /* update mouse pointer if needed */
      if (mouse_on) {
         if ((mouse_ypos+wgdi_mouse_sprite->h > top_line) && (mouse_ypos <= bottom_line)) {
            blit(gdi_screen, mouse_backbuffer, mouse_xpos, mouse_ypos, 0, 0,
                 mouse_backbuffer->w, mouse_backbuffer->h);

            update_mouse_pointer(mouse_xpos, mouse_ypos, TRUE);
         }
      }
      
      /* clean up the dirty lines */
      while (top_line <= bottom_line)
         gdi_dirty_lines[top_line++] = 0;

      ReleaseDC(allegro_wnd, hdc);
   }

   _exit_gfx_critical();

   /* simulate vertical retrace */
   PulseEvent(vsync_event);

   render_semaphore = FALSE;
}