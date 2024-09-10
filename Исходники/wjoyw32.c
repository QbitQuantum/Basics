/* joystick_win32_init:
 *  Initialises the Win32 joystick driver.
 */
static int joystick_win32_init(void)
{
   JOYCAPS caps;
   JOYINFOEX js;
   int n_joyat, n_joy, n_axis;

   win32_joy_num = joyGetNumDevs();

   if (win32_joy_num > MAX_JOYSTICKS)
      _TRACE(PREFIX_W "The system supports more than %d joysticks\n", MAX_JOYSTICKS);

   /* retrieve joystick infos */
   n_joy = 0;
   for (n_joyat = 0; n_joyat < win32_joy_num; n_joyat++) {
      if (n_joy == MAX_JOYSTICKS)
         break;

      if (joyGetDevCaps(n_joyat, &caps, sizeof(caps)) == JOYERR_NOERROR) {
         /* is the joystick physically attached? */
         js.dwSize = sizeof(js);
         js.dwFlags = JOY_RETURNALL;
         if (joyGetPosEx(n_joyat, &js) == JOYERR_UNPLUGGED)
            continue;

         memset(&win32_joystick[n_joy], 0, sizeof(struct WIN32_JOYSTICK_INFO));

         /* set global properties */
	 win32_joystick[n_joy].device = n_joyat;
	 win32_joystick[n_joy].caps = caps.wCaps;
	 win32_joystick[n_joy].num_buttons = MIN(caps.wNumButtons, MAX_JOYSTICK_BUTTONS);
	 win32_joystick[n_joy].num_axes = MIN(caps.wNumAxes, WINDOWS_MAX_AXES);

	 /* fill in ranges of axes */
	 win32_joystick[n_joy].axis_min[0] = caps.wXmin;
	 win32_joystick[n_joy].axis_max[0] = caps.wXmax;
	 win32_joystick[n_joy].axis_min[1] = caps.wYmin;
	 win32_joystick[n_joy].axis_max[1] = caps.wYmax;
	 n_axis = 2;

	 if (caps.wCaps & JOYCAPS_HASZ)	{
	    win32_joystick[n_joy].axis_min[2] = caps.wZmin;
	    win32_joystick[n_joy].axis_max[2] = caps.wZmax;
	    n_axis++;
	 }

	 if (caps.wCaps & JOYCAPS_HASR)	{
	    win32_joystick[n_joy].axis_min[n_axis] = caps.wRmin;
	    win32_joystick[n_joy].axis_max[n_axis] = caps.wRmax;
	    n_axis++;
	 }

	 if (caps.wCaps & JOYCAPS_HASU)	{
	    win32_joystick[n_joy].axis_min[n_axis] = caps.wUmin;
	    win32_joystick[n_joy].axis_max[n_axis] = caps.wUmax;
	    n_axis++;
	 }

	 if (caps.wCaps & JOYCAPS_HASV)	{
	    win32_joystick[n_joy].axis_min[n_axis] = caps.wVmin;
	    win32_joystick[n_joy].axis_max[n_axis] = caps.wVmax;
	    n_axis++;
	 }

         /* register this joystick */
         if (win_add_joystick((WINDOWS_JOYSTICK_INFO *)&win32_joystick[n_joy]) != 0)
            break;

         n_joy++;
      }
   }

   win32_joy_num = n_joy;

   return (win32_joy_num == 0);
}