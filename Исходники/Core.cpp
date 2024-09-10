    /**
     * Parses the input necessary to control the camera and sets the
     * appropriate internal variables.
     */
    void CoreCamera::step(){
      int mouse_x, mouse_y;
      int mdx, mdy;
      int window_width, window_height, window_mid_x, window_mid_y;
      GLfloat dx, dy, dz, dalpha, dbeta, dgamma;
      dx = 0;
      dy = 0;
      dz = 0;
      dalpha = 0;
      dbeta = 0;
      dgamma = 0;
      
      if (!modeEnabled(LOCK_ALL)){
	Mouse->coordinates(mouse_x, mouse_y);
	Engine->windowDimensions(window_width, window_height);
		
	mdx = mouse_x - prev_mouse_x;
	mdy = mouse_y - prev_mouse_y;
		
	window_mid_x = (int)round(window_width / 2);
	window_mid_y = (int)round(window_height / 2);
		
		
	if ((Mouse->down(BUTTON_RIGHT) || (Mouse->down(BUTTON_LEFT) && Keyboard->down(zoom_camera_button_code))) && Mouse->down(BUTTON_LEFT)){	  
	  if (modeEnabled(ZOOM_SCALES)){
	    float d_scale = mdy / 25.0f;
	    scale_x -= d_scale;
	    scale_y -= d_scale;
	    scale_x = (scale_x < 0.1 ? 0.1 : scale_x);
	    scale_y = (scale_y < 0.1 ? 0.1 : scale_y);
	  }
	  else{
	    dz += (mdx + mdy) / 20.0f;
	  }
	}
	else if (Mouse->down(BUTTON_RIGHT) || (Mouse->down(BUTTON_LEFT) && Keyboard->down(rotate_camera_button_code))){
	  if (modeEnabled(RMB_CYLINDRICAL_ROTATE)){
	    // If the mouse is to the left of the center of the screen, we have a problem b/c atan2 
	    // is discontinuous there whenever y crosses the real line. The solution: if we're on the left, 
	    // reflect the x coordinate, then reflect the resulting angle
	    int reflection = ((mouse_x - window_mid_x) > 0 ? 1 : -1);
	    dgamma = reflection *(atan2(mouse_y-window_mid_y + mdy, reflection * (mouse_x-window_mid_x + mdx)) - atan2(mouse_y - window_mid_y, reflection*(mouse_x-window_mid_x)))*100;
	  }
	  else{
	    dalpha -= (mdx * 180.0f) / 500.0f;
	    dbeta -= (mdy * 180.0f) / 500.0f;	    
	  }
	}
	else if (Mouse->down(BUTTON_LEFT)){
	  float scale = (modeEnabled(RMB_CYLINDRICAL_ROTATE) ? 1.0f : 50.0f) * ((scale_x + scale_y)/2.0f);
	  dx -= (mdx/scale);
	  dy += (mdy/scale);
	}
		
	dalpha = (modeEnabled(LOCK_ALPHA) ? 0 : dalpha);
	dbeta = (modeEnabled(LOCK_BETA) ? 0 : dbeta);
	dgamma = (modeEnabled(LOCK_GAMMA) ? 0 : dgamma);
	dx = (modeEnabled(LOCK_PAN) ? 0 : dx);
	dy = (modeEnabled(LOCK_PAN) ? 0 : dy);
	dz = (modeEnabled(LOCK_DISTANCE) ? 0 : dz);
		
		
	if (modeEnabled(RMB_CYLINDRICAL_ROTATE) || modeEnabled(LMB_DRAG_FOCUS)){
	  Vector vdx, vdy;
	  Matrix rotation = focus_frame->rotationToParent();
	  vdx = rotation.transform(Vector(dx, 0, 0));
	  vdy = rotation.transform(Vector(0, dy, 0));
	  focus_frame->translate(vdx);
	  focus_frame->translate(vdy);
	  translate(0, 0, dz);
	}
	else{
	  translate(dx, dy, dz);
	}

	focus_frame->rotate(dalpha, dbeta, dgamma);
			
	prev_mouse_x = mouse_x;
	prev_mouse_y = mouse_y;
      }
		      
    }