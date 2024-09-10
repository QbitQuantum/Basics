void vsx_widget_desktop::draw() {
  if (!init_run) return;
  // this is designed to be root, so set up things

  // Deal with movement around the desktop

	#define SGN(N) (N >= 0 ? 1 : -1)
	#define MAX(N, M) ((N) >= (M) ? (N) : (M))
	#define MIN(N, M) ((N) <= (M) ? (N) : (M))
	#define CLAMP(N, L, U) (MAX(MIN((N), (U)), (L)))
	//if (logo_time > animlen) {
	if (!interpolating) {
		double acc = 4, dec = 3, spd = global_key_speed;
		// interpolation falloff control
		float tt = dtime*interpolation_speed*global_interpolation_speed;
		if (tt > 1) { tt = 1; }

		if(zpd != 0.0) {
			double sgn = SGN(zpd);
			zps += dtime * acc * sgn * global_interpolation_speed;
			zps = CLAMP(zps, -1.2f, 1.2f);
		}
		if(zpd == 0.0) {
			double sgn = SGN(zps);
			zps -= dtime * dec * sgn * global_interpolation_speed;
			zps = MAX(zps * sgn, 0) * sgn;
		}

		zp += zps * fabs(zp - 1.1)* spd * dtime + zpp*(zp - 1.0f);
		zpp = zpp*(1-tt);

		if (zp > 100) {zp = 100; zps = 0;}
		if (zp < 1.2) {zp = 1.2; zps = 0;}

		if(xpd != 0.0) {
			double sgn = SGN(xpd);
			xps += dtime * acc * sgn * global_interpolation_speed;
			xps = CLAMP(xps, -1, 1);
		}
		if(xpd == 0.0) {
			double sgn = SGN(xps);
			xps -= dtime * dec * sgn * global_interpolation_speed;
			xps = MAX(xps * sgn, 0) * sgn;
		}
		xp += xps * fabs(zp - 1.1)* spd * dtime*0.6 + xpp*(zp-1.0f);
		xpp = xpp*(1-tt);

		if (xp > 10) {xp = 10; xps = 0;}
		if (xp < -10) {xp = -10; xps = 0;}

		if(ypd != 0.0) {
			double sgn = SGN(ypd);
			yps += dtime * acc * sgn * global_interpolation_speed;
			yps = CLAMP(yps, -1, 1);
		}
		if(ypd == 0.0) {
			double sgn = SGN(yps);
			yps -= dtime * dec * sgn * global_interpolation_speed;
			yps = MAX(yps * sgn, 0) * sgn;
		}
		yp += yps * fabs(zp - 1.1)* spd * dtime*0.6 + ypp*(zp-1.0f);
		ypp = ypp*(1-tt);

		if (yp > 10) {yp = 10; yps = 0;}
		if (yp < -10) {yp = -10; yps = 0;}
//    			printf("xp: %f xps: %f xpd %f dt %f::",xp,xps,xpd,tt);

	}
	else {
		float tt = dtime*10.0f*global_interpolation_speed;
		if (tt > 1) { tt = 1; interpolating = false;}
		xp = xp*(1-tt)+camera_target.x*tt;
		yp = yp*(1-tt)+camera_target.y*tt;
		zp = zp*(1-tt)+camera_target.z*tt;
		if (
			(round(xp*2000) == round(camera_target.x*2000)) &&
			(round(yp*2000) == round(camera_target.y*2000)) &&
			(round(zp*2000) == round(camera_target.z*2000))
		) interpolating = false;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,screen_x/screen_y,0.001,120.0);

	gluLookAt(xp,yp,zp-1.1f,xp,yp,-1.1f,0.0,1.0,0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// PERFORMANCE_MODE_CHANGE
	// if (performance_mode)
	//  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//else
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//
	//return;
	glEnable(GL_BLEND);
	//glClear(GL_COLOR_BUFFER_BIT);
	if (!performance_mode)
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//glEnable(GL_LINE_SMOOTH);
	if (!performance_mode)
	{
		glDisable(GL_DEPTH_TEST);
		glDepthMask(GL_FALSE);
		glColor4f(1,1,1,1);
		#ifndef VSXU_PLAYER
    if (!mtex.bind())
		#endif
    glColor4f(skin_color[13].r,skin_color[13].g,skin_color[13].b,skin_color[13].a);
    //else
     	glBegin(GL_QUADS);
      	glTexCoord2f(0, 0);
        glVertex3f(pos.x-size.x/2,pos.y-size.y/2,-10.0f);
      	glTexCoord2f(0, 1);
        glVertex3f(pos.x-size.x/2,pos.y+size.y/2,-10.0f);
      	glTexCoord2f(1, 1);
        glVertex3f(pos.x+size.x/2,pos.y+size.y/2,-10.0f);
      	glTexCoord2f(1, 0);
        glVertex3f(pos.x+size.x/2,pos.y-size.y/2,-10.0f);
      glEnd();
		#ifndef VSXU_PLAYER
    mtex._bind();
		#endif
	}
  draw_children();
}