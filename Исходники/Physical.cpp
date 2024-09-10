void
Physical::AeroFrame(double s)
{
	arcade_velocity = Point();

	// if this object is under direction,
	// but doesn't need subframe accuracy,
	// update the control parameters:
	if (dir && !dir->Subframe())
	dir->ExecFrame(s);

	// decrement life before destroying the frame time:
	if (life > 0)
	life -= s;

	// integrate equations
	// using slices no larger
	// than sub_frame:

	double seconds = s;

	while (s > 0.0) {
		if (s > sub_frame)
		seconds = sub_frame;
		else
		seconds = s;

		// if the director needs subframe accuracy, run it now:
		if (dir && dir->Subframe())
		dir->ExecFrame(seconds);

		AngularFrame(seconds);

		// LINEAR MOVEMENT ----------------------------
		Point pos = cam.Pos();

		// if the object is thrusting,
		// accelerate along the camera normal:
		if (thrust) {
			Point thrustvec = cam.vpn();
			thrustvec *= ((thrust/mass) * seconds);
			velocity += thrustvec;
		}

		// AERODYNAMICS ------------------------------

		if (lat_thrust)
		LinearFrame(seconds);

		// if no thrusters, do constant gravity:
		else if (g_accel > 0)
		velocity += Point(0, -g_accel, 0) * seconds;

		// compute alpha, rho, drag, and lift:

		Point  vfp     = velocity;
		double v       = vfp.Normalize();
		double v_2     = 0;
		double rho     = GetDensity();
		double lift    = 0;

		if (v > 150) {					
			v_2 = (v-150) * (v-150);

			Point  vfp1 = vfp - cam.vrt() * (vfp * cam.vrt());
			vfp1.Normalize();

			double cos_alpha = vfp1 * cam.vpn();

			if (cos_alpha >= 1) {
				alpha = 0.0f;
			}
			else {
				alpha = (float) acos(cos_alpha);
			}

			// if flight path is above nose, alpha is negative:
			if (vfp1 * cam.vup() > 0)
			alpha = -alpha;

			if (alpha <= stall) {
				lift = CL * alpha * rho * v_2;
			}
			else {
				lift = CL * (2*stall - alpha) * rho * v_2;
			}

			// add lift to velocity:
			if (_finite(lift))
			velocity += cam.vup() * lift * seconds;
			else
			lift = 0;

			// if drag applies, decellerate:
			double alpha_2 = alpha*alpha;
			double drag_eff = (drag + (CD * alpha_2)) * rho * v_2;

			Point vn = velocity;
			vn.Normalize();

			velocity += vn * -drag_eff * seconds;
		}
		else {
			velocity *= exp(-drag * seconds);
		}

		// move the position by the (time-frame scaled) velocity:
		pos += velocity * seconds;
		cam.MoveTo(pos);

		s -= seconds;
	}

	// now update the graphic rep and light sources:
	if (rep) {
		rep->MoveTo(cam.Pos());
		rep->SetOrientation(cam.Orientation());
	}

	if (light) {
		light->MoveTo(cam.Pos());
	}
}