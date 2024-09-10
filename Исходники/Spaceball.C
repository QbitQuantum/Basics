// check for an event, and queue it if found.  Return TRUE if an event
// was generated.
int Spaceball::check_event(void) {
  int tx, ty, tz, rx, ry, rz, buttons;
  int buttonchanged;
  int win_event=FALSE;
  int direct_event=FALSE;
  // for use in UserKeyEvent() calls
  DisplayDevice::EventCodes keydev=DisplayDevice::WIN_KBD;

  // explicitly initialize event state variables
  rx=ry=rz=tx=ty=tz=buttons=0;

#if defined(VMDTDCONNEXION) && defined(__APPLE__)
  if (tdx_getstatus(tx, ty, tz, rx, ry, rz, buttons))
    win_event = TRUE;
#else
  if (app->display->spaceball(&rx, &ry, &rz, &tx, &ty, &tz, &buttons)) 
    win_event = TRUE;
#endif


#if defined(VMDLIBSBALL)
  // combine direct spaceball events together with window-system events
  if (sball != NULL) {
    int rx2, ry2, rz2, tx2, ty2, tz2, buttons2;
    if (sball_getstatus(sball, &tx2, &ty2, &tz2, &rx2, &ry2, &rz2, &buttons2)) {
      direct_event = TRUE;
      rx += rx2;
      ry += ry2;
      rz += rz2;
      tx += tx2; 
      ty += ty2; 
      tz += tz2; 
      buttons |= buttons2;
    }
  }
#endif

  if (!win_event && !direct_event)
    return FALSE; // no events to report

  // find which buttons changed state
  buttonchanged = buttons ^ buttonDown; 

  // if the user presses button 1, reset the view, a very very very
  // important feature to have implemented early on... ;-)
#if defined(VMDLIBSBALL)  && !defined(VMDSPACEWARE)
  if (((buttonchanged & SBALL_BUTTON_1) && (buttons & SBALL_BUTTON_1)) ||
      ((buttonchanged & SBALL_BUTTON_LEFT) && (buttons & SBALL_BUTTON_LEFT))){
#else 
// #elif!defined(VMDLIBSBALL) && defined(VMDSPACEWARE)
  if ((buttonchanged & 2) && (buttons & 2)) {
#endif

    app->scene_resetview();
    msgInfo << "Spaceball reset view orientation" << sendmsg;
  }

  // Toggle between the different modes
#if   defined(VMDLIBSBALL)  &&  !defined(VMDSPACEWARE)
  if (((buttonchanged & SBALL_BUTTON_2) && (buttons & SBALL_BUTTON_2)) ||
      ((buttonchanged & SBALL_BUTTON_RIGHT) && (buttons & SBALL_BUTTON_RIGHT))) {
#else
//#elif !defined(VMDLIBSBALL) &&  defined(VMDSPACEWARE)
  if ((buttonchanged & 4) && (buttons & 4)) {
#endif

    switch (moveMode) {
      case NORMAL:
        move_mode(MAXAXIS);
        msgInfo << "Spaceball set to dominant axis rotation/translation mode" << sendmsg;
        break;   

      case MAXAXIS:
        move_mode(SCALING);
        msgInfo << "Spaceball set to scaling mode" << sendmsg;
        break;   

      case SCALING:
        move_mode(ANIMATE);
        msgInfo << "Spaceball set to animate mode" << sendmsg;
        break;   

      case ANIMATE:
        move_mode(TRACKER);
        msgInfo << "Spaceball set to tracker mode" << sendmsg;
        break;   

      case TRACKER:
        move_mode(USER);
        msgInfo << "Spaceball set to user mode" << sendmsg;
        break;   

      default: 
        move_mode(NORMAL);
        msgInfo << "Spaceball set to rotation/translation mode" << sendmsg;
        break;
    }
  }

  // if the user presses button 3 through N, run a User command
#if defined(VMDLIBSBALL)  &&  !defined(VMDSPACEWARE)
  if ((buttonchanged & SBALL_BUTTON_3) && (buttons & SBALL_BUTTON_3)) {
    runcommand(new UserKeyEvent(keydev, '3', (int) DisplayDevice::AUX));
  }
  if ((buttonchanged & SBALL_BUTTON_4) && (buttons & SBALL_BUTTON_4)) {
    runcommand(new UserKeyEvent(keydev, '4', (int) DisplayDevice::AUX));
  }
  if ((buttonchanged & SBALL_BUTTON_5) && (buttons & SBALL_BUTTON_5)) {
    runcommand(new UserKeyEvent(keydev, '5', (int) DisplayDevice::AUX));
  }
  if ((buttonchanged & SBALL_BUTTON_6) && (buttons & SBALL_BUTTON_6)) {
    runcommand(new UserKeyEvent(keydev, '6', (int) DisplayDevice::AUX));
  }
  if ((buttonchanged & SBALL_BUTTON_7) && (buttons & SBALL_BUTTON_7)) {
    runcommand(new UserKeyEvent(keydev, '7', (int) DisplayDevice::AUX));
  }
  if ((buttonchanged & SBALL_BUTTON_8) && (buttons & SBALL_BUTTON_8)) {
    runcommand(new UserKeyEvent(keydev, '8', (int) DisplayDevice::AUX));
  }
//#elif !defined(VMDLIBSBALL) &&  defined(VMDSPACEWARE)
#else
  if ((buttonchanged & 8) && (buttons & 8)) {
    runcommand(new UserKeyEvent(keydev, '3', (int) DisplayDevice::AUX));
  }
  if ((buttonchanged & 16) && (buttons & 16)) {
    runcommand(new UserKeyEvent(keydev, '4', (int) DisplayDevice::AUX));
  }
  if ((buttonchanged & 32) && (buttons & 32)) {
    runcommand(new UserKeyEvent(keydev, '5', (int) DisplayDevice::AUX));
  }
  if ((buttonchanged & 64) && (buttons & 64)) {
    runcommand(new UserKeyEvent(keydev, '6', (int) DisplayDevice::AUX));
  }
  if ((buttonchanged & 128) && (buttons & 128)) {
    runcommand(new UserKeyEvent(keydev, '7', (int) DisplayDevice::AUX));
  }
  if ((buttonchanged & 256) && (buttons & 256)) {
    runcommand(new UserKeyEvent(keydev, '8', (int) DisplayDevice::AUX));
  }
#endif

  // get absolute values of axis forces for use in 
  // null region processing and min/max comparison tests
  int atx, aty, atz, arx, ary, arz;
  atx = abs(tx);
  aty = abs(ty);
  atz = abs(tz);
  arx = abs(rx);
  ary = abs(ry);
  arz = abs(rz);


  // perform null region processing
  if (atx > null_region) {
    tx = ((tx > 0) ? (tx - null_region) : (tx + null_region));
  } else {
    tx = 0;
  }
  if (aty > null_region) {
    ty = ((ty > 0) ? (ty - null_region) : (ty + null_region));
  } else {
    ty = 0;
  }
  if (atz > null_region) {
    tz = ((tz > 0) ? (tz - null_region) : (tz + null_region));
  } else {
    tz = 0;
  }
  if (arx > null_region) {
    rx = ((rx > 0) ? (rx - null_region) : (rx + null_region));
  } else {
    rx = 0;
  }
  if (ary > null_region) {
    ry = ((ry > 0) ? (ry - null_region) : (ry + null_region));
  } else {
    ry = 0;
  }
  if (arz > null_region) {
    rz = ((rz > 0) ? (rz - null_region) : (rz + null_region));
  } else {
    rz = 0;
  }


  // Ignore null motion events since some versions of the Windows 
  // Spaceball driver emit a constant stream of null motion event
  // packets which would otherwise cause continuous redraws, pegging the 
  // CPU and GPU at maximum load.
  if ((arx+ary+arz+atx+aty+atz) > 0) {
    float ftx = tx * sensitivity;
    float fty = ty * sensitivity;
    float ftz = tz * sensitivity;
    float frx = rx * sensitivity;
    float fry = ry * sensitivity;
    float frz = rz * sensitivity;
    char rmaxaxis = 'x';
    float rmaxval = 0.0f;
    float tmaxval = 0.0f;
    float tmaxvec[3] = { 0.0f, 0.0f, 0.0f };
    tmaxvec[0] = tmaxvec[1] = tmaxvec[2] = 0.0f;

    switch(moveMode) {
      case NORMAL:
        // Z-axis rotation/trans have to be negated in order to please VMD...
        app->scene_rotate_by(frx * rotInc, 'x');
        app->scene_rotate_by(fry * rotInc, 'y');
        app->scene_rotate_by(-frz * rotInc, 'z');
        if (app->display_projection_is_perspective()) {
          app->scene_translate_by(ftx * transInc, fty * transInc, -ftz * transInc);
        } else {
          app->scene_scale_by((1.0f + scaleInc * -ftz > 0.0f) ? 
                               1.0f + scaleInc * -ftz : 0.0f);
          app->scene_translate_by(ftx * transInc, fty * transInc, 0);
        }
 
        break;

      case MAXAXIS:
        // Z-axis rotation/trans have to be negated in order to please VMD...
        // find dominant rotation axis
        if (arx > ary) {
          if (arx > arz) {
            rmaxaxis = 'x';
            rmaxval = frx; 
          } else {
            rmaxaxis = 'z';
            rmaxval = -frz; 
          }
        } else {     
          if (ary > arz) {
            rmaxaxis = 'y';
            rmaxval = fry; 
          } else {
            rmaxaxis = 'z';
            rmaxval = -frz; 
          }
        }

        // find dominant translation axis
        if (atx > aty) {
          if (atx > atz) {
            tmaxval = ftx;
            tmaxvec[0] = ftx; 
          } else {
            tmaxval = ftz;
            tmaxvec[2] = ftz; 
          }
        } else {     
          if (aty > atz) {
            tmaxval = fty;
            tmaxvec[1] = fty; 
          } else {
            tmaxval = ftz;
            tmaxvec[2] = ftz; 
          }
       }

       // determine whether to rotate or translate
       if (fabs(rmaxval) > fabs(tmaxval)) {
         app->scene_rotate_by(rmaxval * rotInc, rmaxaxis);
       } else {
         app->scene_translate_by(tmaxvec[0] * transInc, 
                                 tmaxvec[1] * transInc, 
                                -tmaxvec[2] * transInc);
       }
       break;

      case SCALING:
        app->scene_scale_by((1.0f + scaleInc * ftz > 0.0f) ? 
                             1.0f + scaleInc * ftz : 0.0f);
        break;

      case ANIMATE:
        // if we got a non-zero input, update the VMD animation state
        if (abs(ry) > 0) {
#if 1
          // exponential input scaling
          float speed = fabsf(expf(fabsf((fabsf(fry) * animInc) / 1.7f))) - 1.0f;
#else
          // linear input scaling
          float speed = fabsf(fry) * animInc;
#endif

          if (speed > 0) {
            if (speed < 1.0) 
              app->animation_set_speed(speed);
            else
              app->animation_set_speed(1.0f);
 
            int stride = 1;
            if (fabs(speed - 1.0) > (double) maxstride)
              stride = maxstride;
            else
              stride = 1 + (int) fabs(speed-1.0);
            if (stride < 1)
              stride = 1; 
            app->animation_set_stride(stride);
 
            // -ry is turned to the right, like a typical shuttle/jog control
            if (fry < 0) 
              app->animation_set_dir(Animation::ANIM_FORWARD1);
            else
              app->animation_set_dir(Animation::ANIM_REVERSE1);
          } else {
            app->animation_set_dir(Animation::ANIM_PAUSE);
            app->animation_set_speed(1.0f);
          }
        } else {
          app->animation_set_dir(Animation::ANIM_PAUSE);
          app->animation_set_speed(1.0f);
        }
        break;

      case TRACKER:
        trtx = ftx;
        trty = fty;
        trtz = ftz;
        trrx = frx;
        trry = fry;
        trrz = frz;
        trbuttons = buttons;
        break;

      case USER:
        // inform TCL
        app->commandQueue->runcommand(new SpaceballEvent(ftx, fty, ftz, 
                                                         frx, fry, frz, 
                                                         buttons));
        break;
    }
  }

  // update button status for next time through
  buttonDown = buttons;

  return TRUE;
}


///////////// public routines for use by text commands etc

const char* Spaceball::get_mode_str(MoveMode mm) {
  const char* modestr;

  switch (mm) {
    default:
    case NORMAL:      modestr = "rotate";     break;
    case MAXAXIS:     modestr = "maxaxis";    break;
    case SCALING:     modestr = "scale";      break;
    case ANIMATE:     modestr = "animate";    break;
    case TRACKER:     modestr = "tracker";    break;
    case USER:        modestr = "user";       break;
  }

  return modestr;
}


void Spaceball::get_tracker_status(float &tx, float &ty, float &tz,
                                   float &rx, float &ry, float &rz, 
                                   int &buttons) {
  tx =  trtx * transInc;
  ty =  trty * transInc;
  tz = -trtz * transInc;
  rx =  trrx * rotInc;
  ry =  trry * rotInc;
  rz = -trrz * rotInc;
  buttons = trbuttons;
}


// set the Spaceball move mode to the given state; return success
int Spaceball::move_mode(MoveMode mm) {
  // change the mode now
  moveMode = mm;

  /// clear out any remaining tracker event data if we're not in that mode
  if (moveMode != TRACKER) {
    trtx=trty=trtz=trrx=trry=trrz=0.0f; 
    trbuttons=0;
  }

  return TRUE; // report success
}