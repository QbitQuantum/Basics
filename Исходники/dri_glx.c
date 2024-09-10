/*
 * Given a display pointer and screen number, return a __DRIdriver handle.
 * Return NULL if anything goes wrong.
 */
__DRIdriver *driGetDriver(Display *dpy, int scrNum)
{
   char *driverName;
   if (GetDriverName(dpy, scrNum, &driverName)) {
      __DRIdriver *ret;
      ret = OpenDriver(driverName);
      if (driverName)
     	 Xfree(driverName);
      return ret;
   }
   return NULL;
}