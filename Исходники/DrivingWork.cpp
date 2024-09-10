/**
 * \brief driving thread main function
 *
 * The main function works in a loop until the thread is terminated and
 * keeps feeding the guiderport with control commands based on the settings
 * of the tx and ty values. The tx and ty values are signed duty cycle numbers
 * for the guider port, 1 means that the corresponding plus signal of the
 * guiderport should be activated all the time. The loop is timed by the
 * _interval variable, so the method just computes the time to activate
 * the guiderport and then goes to sleep for the rest of the interval.
 */
void	DrivingWork::main(astro::thread::Thread<DrivingWork>& thread) {
	debug(LOG_DEBUG, DEBUG_LOG, 0, "GUIDE: thread main function starts");
	do {
		double	raplus = 0, raminus = 0;
		double	decplus = 0, decminus = 0;
		// read the currently valid corrections from tx and ty,
		// this must be done while the mutex is held, or the
		// data we read my be inconsistent.
		{
			std::unique_lock<std::mutex>	lock(mutex);
			if (totalx > 0) {
				double	dx = std::min(_interval, totalx);
				if (stepx > 0) {
					raplus = dx;
				} else {
					raminus = dx;
				}
				totalx -= dx;
			} else {
				if (defaultx > 0) {
					raplus = defaultx * _interval;
				} else {
					raminus = -defaultx * _interval;
				}
			}
			if (totaly > 0) {
				double	dy = std::min(_interval, totaly);
				if (stepy > 0) {
					decplus = dy;
				} else {
					decminus = dy;
				}
				totaly -= dy;
			} else {
				if (defaulty > 0) {
					decplus = defaulty * _interval;
				} else {
					decminus = -defaulty * _interval;
				}
			}
			if (totalx < 0) { totalx = 0.; }
			if (totaly < 0) { totaly = 0.; }
		}

		// now activate the guider port outputs for the times we found
		debug(LOG_DEBUG, DEBUG_LOG, 0,
			"GUIDE: activate(%.3f, %.3f, %.3f, %.3f)",
			raplus, raminus, decplus, decminus);
		guider().guiderport()->activate(raplus, raminus,
			decplus, decminus);

		// wait for one second.
		Timer::sleep(_interval);

		// checking for termination signal
	} while (!thread.terminate());
	debug(LOG_DEBUG, DEBUG_LOG, 0, "GUIDE: Termination signal received");
}