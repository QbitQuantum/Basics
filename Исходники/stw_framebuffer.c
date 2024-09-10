/**
 * Given an hdc, return the corresponding stw_framebuffer.
 * The returned stw_framebuffer will have its mutex locked.
 */
static struct stw_framebuffer *
stw_framebuffer_from_hdc_locked(HDC hdc)
{
   HWND hwnd;

   hwnd = WindowFromDC(hdc);
   if (!hwnd) {
      return NULL;
   }

   return stw_framebuffer_from_hwnd_locked(hwnd);
}