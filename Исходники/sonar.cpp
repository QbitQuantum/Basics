// translated from python script, refine later
double compute_signal_strength_GHG(angle signal_angle, double frequency, angle apparatus_angle)
{
#if 1
	double cosang = std::max(0.0, (signal_angle - apparatus_angle).cos());
//	printf("siga=%f appa=%f diff=%f cos=%f\n",signal_angle.value(), apparatus_angle.value(), (signal_angle -apparatus_angle).value(), cosang);
	// use 280 as exponent for 7kHz, so f * 0.04 = exponent.
	return pow(cosang, frequency * 0.04);
#else
	// global constants
	static const double speed_of_sound_in_water = 1465.0;	// m/s

	// GHG constants
	static const double strip_delay = 0.000017;		// 17µs
	static const angle hydrophone_fov = 180.0; // 180.0;		// degrees
	static const unsigned nr_hydrophones = 24; // 12;
	static const double distance_hydro = 0.2;		// m
	static const angle hydrophone_fov_center_first = 21.0; // 24.0;	// degrees
	static const angle hydrophone_fov_center_delta = 6.0; // 12.0;	// degrees
	static const unsigned nr_of_strips = 99;	// use an odd number here!

	/* note! the constants depend on each other.
	   total delay is strip_delay * nr_of_strips = 1.683ms
	   the hydrophones must be arranged on a line NOT LONGER than the range
	   the sound travels in that time. So 1465m/s * 1.683ms = 2.465595m.
	   This number must be greater than (nr_hydrophones-1) * distance_hydro,
	   which it is here (0.2m * (12-1) = 2.2m)
	*/

	static const double delta_t = distance_hydro / speed_of_sound_in_water;
	static const double distance_contact = delta_t / strip_delay;
	static const double height_of_all_contacts = distance_contact * (nr_hydrophones - 1);

	//printf("comp sign str signang=%f freq=%f appang=%f\n", signal_angle.value(), frequency, apparatus_angle.value());
	bool app_on_port = (apparatus_angle.value() >= 180.0);

	double time_scale_fac = 2*M_PI*frequency;
	double delta_t_signal = signal_angle.cos() * delta_t;
	double sum_cos = 0.0, sum_sin = 0.0;
	double amplitude[nr_hydrophones];
	double phase_shift[nr_hydrophones];
	double max_strength = 0.0;
	for (unsigned i = 0; i < nr_hydrophones; ++i) {
		// hydrophones are numbered from bow to stern,
		// where strip lines and y-coordinates of contacts on them
		// go from "stern" to "bow", that is bottom to top.
		angle fov_center = hydrophone_fov_center_first + hydrophone_fov_center_delta * double(i);
		if (app_on_port) fov_center = -fov_center;
		angle rel_angle = signal_angle - fov_center;
		amplitude[i] = rel_angle.cos();
 		if (fabs(rel_angle.value_pm180()) > hydrophone_fov.value()*0.5)
 			amplitude[i] = 0;
		max_strength += amplitude[i];
		double y = (height_of_all_contacts*0.5 - distance_contact*i) * apparatus_angle.cos();
		int y_line = int(floor(y + nr_of_strips*0.5));
		//printf("y=%f yp=%f ryp=%f y_line=%i\n", y, y + nr_of_strips*0.5, floor(y + nr_of_strips*0.5), y_line);
		double delay_i = strip_delay * y_line;
		// note that delay_i is the full delay to the output to the headphones.
		// if the first strip line with a contact has number N and not 0,
		// all signals are shifted by N * strip_delay. This doesn't change
		// the computation result though. In fact it is like the GHG worked.
		//printf("delay_i=%f delta_t_signal=%f i=%u tsf=%f sum=%f\n",
		//       delay_i, delta_t_signal, i, time_scale_fac, (delay_i + delta_t_signal * i));
		phase_shift[i] = (delay_i + delta_t_signal * i) * time_scale_fac;
		sum_cos += amplitude[i] * cos(phase_shift[i]);
		sum_sin += amplitude[i] * sin(phase_shift[i]);
		//printf("i=%u ampl=%f phs=%f\n",i,amplitude[i],phase_shift[i]);
	}
	double x_extr = atan(sum_cos / sum_sin);
	// Note: the output of this function seems to contain a bit jitter,
	// the computed strength oscillates a bit around the exact value.
	// This effect seems to be amplified by the snapping to integer strip line
	// numbers, but can be seen also with infinite small strips. A rounding error?
	// a result of the sidelobe phenomenon?! ghg phenomenon, disappears with smaller strip lines.

	// Note2: a signal seems to cause a second signal with 90° offset... sidelobe?!
	// ghsot signal. appears only with higher frequencies, ghg phenomenon.
	// maybe the arrangement of the hydrophones, their fov and listening direction is
	// not fully correct, causing or amplifying these phenomenons, fixme!
	// each hydrophone must listen to a certain direction, if all listen to 90°
	// then the output is unusable, showing peaks in direction of each hydrophone.
	// If each hydrophone has a fov < 180° the output is also much worse, causing
	// many ghost signals and so on. The same is true for fov > 180°.

	//printf("max_strength=%f sum_cos=%f sum_sin=%f, x_extr=%f\n",max_strength,sum_cos,sum_sin,x_extr);
	//std::ostringstream oss; oss << "plot [x=" << -0.5*M_PI << ":" << 0.5*M_PI << "] ";
	// now the signal has an extreme value for x = x_extr, compute signal strength
	double signalstrength = 0.0;
	for (unsigned i = 0; i < nr_hydrophones; ++i) {
		signalstrength += amplitude[i] * sin(x_extr + phase_shift[i]);
		//oss << amplitude[i] << "*sin(x+" << phase_shift[i] << ")+";
	}
	//oss << "0\n";
	//printf(oss.str().c_str());
	signalstrength = fabs(signalstrength);

	//printf("result: signstr=%f perc=%f appang=%f\n", signalstrength, signalstrength/max_strength, apparatus_angle.value());
	// now compute percentage of max. strength
	//fixme: try this: don't divide here!!! doesn't help much, but a bit though, seems to lessen jitter...
	return signalstrength; //  / max_strength;
#endif
}