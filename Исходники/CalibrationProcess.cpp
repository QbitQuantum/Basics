/**
 * \brief Main function of the CalibrationProcess class
 *
 * This method assumes that the observed star position depends linearly
 * on time and the applied correction. It then performs several position
 * measurements and solves for the equation. The resulting matrix should have
 * two nearly perpendicular columns.
 *
 * The mesurements are placed in a grid pattern with coordinate (ra, dec)
 * corresponding to a point that can be reached from the initial position
 * by speeing up (down for negative values) the right ascension/declination
 * motors for ra resp. dec seconds. After each measurement, we return to the
 * central position.
 *
 */
void	CalibrationProcess::main(astro::thread::Thread<CalibrationProcess>& _thread) {
	debug(LOG_DEBUG, DEBUG_LOG, 0, "start calibrating: terminate = %s",
		_thread.terminate() ? "YES" : "NO");
	// set the start time
	starttime = Timer::gettime();

	// grid range we want to scan
	range = 1;

	// the grid constant normally depends on the focallength and the
	// pixels size. Smaller pixels are larger focallength allow to
	// use a smaller grid constant. The default value of 10 is a good
	// choice for a 100mm guide scope and 7u pixels as for the SBIG
	// ST-i guider kit
	grid = gridconstant(_focallength, _pixelsize);

	// prepare a GuiderCalibrator class that does the actual computation
	GuiderCalibrator	calibrator;

	// measure the initial point
	CalibrationPoint	initialpoint(0, Point(0, 0), starAt(0, 0));
	calibrator.add(initialpoint);
	callback(initialpoint);

	// perform a grid search
	try {
		for (int ra = -range; ra <= range; ra++) {
			for (int dec = -range; dec <= range; dec++) {
				measure(calibrator, ra, dec);
				if (_thread.terminate()) {
					debug(LOG_DEBUG, DEBUG_LOG, 0,
						"terminate signal received");
					throw calibration_interrupted();
				}
				_progress = currentprogress(ra, dec);
			}
		}
	} catch (calibration_interrupted&) {
		debug(LOG_DEBUG, DEBUG_LOG, 0, "calibration interrupted");
		return;
	}
	
	// now compute the calibration data, and fix the time constant
	GuiderCalibration	cal = calibrator.calibrate();
	//cal.rescale(1. / grid);
	guider().calibration(cal);

	// inform the callback that calibration is complete
	callback(cal);

	// the guider is now calibrated
	debug(LOG_DEBUG, DEBUG_LOG, 0, "calibration: %s",
		guider().calibration().toString().c_str());
	calibrated = true;

	// signal other threads that we are done
	debug(LOG_DEBUG, DEBUG_LOG, 0, "calibration complete");
	_progress = 1.0;
}