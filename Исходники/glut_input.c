static int
__glutProcessDeviceEvents(XEvent * event)
{
#if !defined(_WIN32)
  GLUTwindow *window;

  /* XXX Ugly code fan out. */

  /* Can't use switch/case since X Input event types are
     dynamic. */

  if (__glutDeviceMotionNotify && event->type == __glutDeviceMotionNotify) {
    XDeviceMotionEvent *devmot = (XDeviceMotionEvent *) event;

    window = __glutGetWindow(devmot->window);
    if (window) {
      if (__glutTablet
        && devmot->deviceid == __glutTablet->device_id
        && window->tabletMotion) {
        tabletPosChange(window, devmot->first_axis, devmot->axes_count,
          devmot->axis_data);
      } else if (__glutDials
          && devmot->deviceid == __glutDials->device_id
        && window->dials) {
        int i, first = devmot->first_axis, count = devmot->axes_count;

        for (i = first; i < first + count; i++)
          window->dials(i + 1,
            normalizeDialAngle(i, devmot->axis_data[i - first]));
      } else if (__glutSpaceball
        && devmot->deviceid == __glutSpaceball->device_id) {
        /* XXX Assume that space ball motion events come in as
           all the first 6 axes.  Assume first 3 axes are XYZ
           translations; second 3 axes are XYZ rotations. */
        if (devmot->first_axis == 0 && devmot->axes_count == 6) {
          if (window->spaceMotion)
            window->spaceMotion(
              normalizeSpaceballDelta(0, devmot->axis_data[0]),
              normalizeSpaceballDelta(1, devmot->axis_data[1]),
              normalizeSpaceballDelta(2, devmot->axis_data[2]));
          if (window->spaceRotate)
            window->spaceRotate(
              normalizeSpaceballAngle(3, devmot->axis_data[3]),
              normalizeSpaceballAngle(4, devmot->axis_data[4]),
              normalizeSpaceballAngle(5, devmot->axis_data[5]));
        }
      }
      return 1;
    }
  } else if (__glutDeviceButtonPress
    && event->type == __glutDeviceButtonPress) {
    XDeviceButtonEvent *devbtn = (XDeviceButtonEvent *) event;

    window = __glutGetWindow(devbtn->window);
    if (window) {
      if (__glutTablet
        && devbtn->deviceid == __glutTablet->device_id
        && window->tabletButton
        && devbtn->first_axis == 0
        && devbtn->axes_count == 2) {
        tabletPosChange(window, devbtn->first_axis, devbtn->axes_count,
          devbtn->axis_data);
        window->tabletButton(devbtn->button, GLUT_DOWN,
          window->tabletPos[0], window->tabletPos[1]);
      } else if (__glutDials
          && devbtn->deviceid == __glutDials->device_id
        && window->buttonBox) {
        window->buttonBox(devbtn->button, GLUT_DOWN);
      } else if (__glutSpaceball
          && devbtn->deviceid == __glutSpaceball->device_id
        && window->spaceButton) {
        window->spaceButton(devbtn->button, GLUT_DOWN);
      }
      return 1;
    }
  } else if (__glutDeviceButtonRelease
    && event->type == __glutDeviceButtonRelease) {
    XDeviceButtonEvent *devbtn = (XDeviceButtonEvent *) event;

    window = __glutGetWindow(devbtn->window);
    if (window) {
      if (__glutTablet
        && devbtn->deviceid == __glutTablet->device_id
        && window->tabletButton
        && devbtn->first_axis == 0
        && devbtn->axes_count == 2) {
        tabletPosChange(window, devbtn->first_axis, devbtn->axes_count,
          devbtn->axis_data);
        window->tabletButton(devbtn->button, GLUT_UP,
          window->tabletPos[0], window->tabletPos[1]);
      } else if (__glutDials
          && devbtn->deviceid == __glutDials->device_id
        && window->buttonBox) {
        window->buttonBox(devbtn->button, GLUT_UP);
      } else if (__glutSpaceball
          && devbtn->deviceid == __glutSpaceball->device_id
        && window->spaceButton) {
        window->spaceButton(devbtn->button, GLUT_UP);
      }
      return 1;
    }
  }
#else
  {
    JOYINFOEX info;
    JOYCAPS joyCaps;

    memset(&info, 0, sizeof(JOYINFOEX)); 
    info.dwSize = sizeof(JOYINFOEX); 
    info.dwFlags = JOY_RETURNALL;

    if (joyGetPosEx(JOYSTICKID1,&info) != JOYERR_NOERROR) {
      __glutHasJoystick = 1;
      joyGetDevCaps(JOYSTICKID1, &joyCaps, sizeof(joyCaps));
      __glutNumJoystickButtons = joyCaps.wNumButtons;
      __glutNumJoystickAxes = joyCaps.wNumAxes;
    } else {
      __glutHasJoystick = 0;
      __glutNumJoystickButtons = 0;
      __glutNumJoystickAxes = 0;
    }
  }
#endif /* !_WIN32 */
  return 0;
}