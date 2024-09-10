void Atmosphere::compute_color(double JD, Vec3d sunPos, Vec3d moonPos, float moon_phase,
                               ToneReproductor * eye, Projector* prj,
                               float latitude, float altitude, float temperature, float relative_humidity)
{

	float min_mw_lum = 0.13;

	// no need to calculate if not visible
	if (!fader.getInterstate()) {
		atm_intensity = 0;
		world_adaptation_luminance = 3.75f + lightPollutionLuminance;
		milkyway_adaptation_luminance = min_mw_lum;  // brighter than without atm, since no drawing addition of atm brightness
		return;
	} else {
		atm_intensity = fader.getInterstate();
	}


	//Vec3d obj;
	skylight_struct2 b2;

	// these are for radii
	double sun_angular_size = atan(696000./AU/sunPos.length());
	double moon_angular_size = atan(1738./AU/moonPos.length());

	double touch_angle = sun_angular_size + moon_angular_size;
	double dark_angle = moon_angular_size - sun_angular_size;

	sunPos.normalize();
	moonPos.normalize();

	// determine luminance falloff during solar eclipses
	double separation_angle = acos( sunPos.dot( moonPos ));  // angle between them

	//	printf("touch at %f\tnow at %f (%f)\n", touch_angle, separation_angle, separation_angle/touch_angle);

	// bright stars should be visible at total eclipse
	// TODO: correct for atmospheric diffusion
	// TODO: use better coverage function (non-linear)
	// because of above issues, this algorithm darkens more quickly than reality
	if ( separation_angle < touch_angle) {
		float min;
		if (dark_angle < 0) {
			// annular eclipse
			float asun = sun_angular_size*sun_angular_size;
			min = (asun - moon_angular_size*moon_angular_size)/asun;  // minimum proportion of sun uncovered
			dark_angle *= -1;
		}
		//		else min = 0.004;  // so bright stars show up at total eclipse
		else min = 0.001;  // so bright stars show up at total eclipse

		if (separation_angle < dark_angle) atm_intensity = min;
		else atm_intensity *= min + (1.-min)*(separation_angle-dark_angle)/(touch_angle-dark_angle);

		//		printf("atm int %f (min %f)\n", atm_intensity, min);
	}

	float sun_pos[3];
	sun_pos[0] = sunPos[0];
	sun_pos[1] = sunPos[1];
	sun_pos[2] = sunPos[2];

	float moon_pos[3];
	moon_pos[0] = moonPos[0];
	moon_pos[1] = moonPos[1];
	moon_pos[2] = moonPos[2];

	sky.set_paramsv(sun_pos, 5.f);

	skyb.set_loc(latitude * M_PI/180., altitude, temperature, relative_humidity);
	skyb.set_sun_moon(moon_pos[2], sun_pos[2]);

	// Calculate the date from the julian day.
	ln_date date;
	NShadeDateTime::JulianToDate(JD, &date);

	skyb.set_date(date.years, date.months, moon_phase);

	float stepX = (float)prj->getViewportWidth() / sky_resolution;
	float stepY = (float)prj->getViewportHeight() / sky_resolution;
	float viewport_left = (float)prj->getViewportPosX();
	float viewport_bottom = (float)prj->getViewportPosY();

	Vec3d point(1., 0., 0.);

	// Variables used to compute the average sky luminance
	double sum_lum = 0.;
	unsigned int nb_lum = 0;

	// Compute the sky color for every point above the ground
	for (int x=0; x<=sky_resolution; ++x) {
		for (int y=0; y<=sky_resolution; ++y) {
			prj->unproject_local((double)viewport_left+x*stepX, (double)viewport_bottom+y*stepY,point);
			point.normalize();

			if (point[2]<=0) {
				point[2] = -point[2];
				// The sky below the ground is the symetric of the one above :
				// it looks nice and gives proper values for brightness estimation
			}

			b2.pos[0] = point[0];
			b2.pos[1] = point[1];
			b2.pos[2] = point[2];

			// Use the Skylight model for the color
			sky.get_xyY_valuev(b2);

			// Use the Skybright.cpp 's models for brightness which gives better results.
			b2.color[2] = skyb.get_luminance(moon_pos[0]*b2.pos[0]+moon_pos[1]*b2.pos[1]+
			                                 moon_pos[2]*b2.pos[2], sun_pos[0]*b2.pos[0]+sun_pos[1]*b2.pos[1]+
			                                 sun_pos[2]*b2.pos[2], b2.pos[2]);


			sum_lum+=b2.color[2];
			++nb_lum;
			eye->xyY_to_RGB(b2.color);
			tab_sky[x][y].set(atm_intensity*b2.color[0],atm_intensity*b2.color[1],atm_intensity*b2.color[2]);
		}
	}

	world_adaptation_luminance = 3.75f + lightPollutionLuminance + 3.5*sum_lum/nb_lum*atm_intensity;
	milkyway_adaptation_luminance = min_mw_lum*(1-atm_intensity) + 30*sum_lum/nb_lum*atm_intensity;

	sum_lum = 0.f;
	nb_lum = 0;
}