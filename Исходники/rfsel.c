/* drive_exists:
 *  Checks whether the specified drive is valid.
 */
static int drive_exists(int x)
{
   #ifdef ALLEGRO_DOS

      /* DOS implementation */
      unsigned int old;
      int ret = FALSE;
      __dpmi_regs r;

      /* get actual drive */
      r.h.ah = 0x19;
      __dpmi_int(0x21, &r);
      old = r.h.al;

      /* see if drive x is assigned as a valid drive */
      r.h.ah = 0x0E;
      r.h.dl = x;
      __dpmi_int(0x21, &r);

      r.h.ah = 0x19;
      __dpmi_int(0x21, &r);

      if (r.h.al == x) {
	 /* ok, now check if it is a logical drive or not... */
	 r.x.ax = 0x440E;
	 r.h.bl = x+1;
	 __dpmi_int(0x21, &r);

	 if ((r.x.flags & 1) ||        /* call failed */
	     (r.h.al == 0) ||          /* has no logical drives */
	     (r.h.al == (x+1)))        /* not a logical drive */
	    ret = TRUE;
      }

      /* now we set the old drive */
      r.h.ah = 0x0E;
      r.h.dl = old;
      __dpmi_int(0x21, &r);

      return ret;

   #elif defined ALLEGRO_WINDOWS

      /* Windows implementation */
      return GetLogicalDrives() & (1 << x);

   #elif defined ALLEGRO_MPW

      /* MacOs implementation */
      return GetLogicalDrives() & (1 << x);

   #else

      /* unknown platform */
      return TRUE;

   #endif
}