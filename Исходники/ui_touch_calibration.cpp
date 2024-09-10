void TouchCalibrationView::touch_complete() {
	auto next_phase = static_cast<Phase>(toUType(phase) + 1);

	switch(phase) {
	case Phase::Calibrate0:
	case Phase::Verify0:
		digitizer_points[0] = average;
		break;

	case Phase::Calibrate1:
	case Phase::Verify1:
		digitizer_points[1] = average;
		break;

	case Phase::Calibrate2:
	case Phase::Verify2:
		digitizer_points[2] = average;
		break;

	default:
		break;
	}

	if( phase == Phase::Calibrate2 ) {
		const std::array<Point, 3> display_points { {
			image_calibrate_0.screen_rect().center(),
			image_calibrate_1.screen_rect().center(),
			image_calibrate_2.screen_rect().center(),
		} };

		calibration = { digitizer_points, display_points };
	}

	if( phase == Phase::Verify2 ) {
		const auto calibrated_0 = calibration.translate(digitizer_points[0]);
		const auto d_sq_0 = distance_squared(calibrated_0, image_verify_0);

		const auto calibrated_1 = calibration.translate(digitizer_points[1]);
		const auto d_sq_1 = distance_squared(calibrated_1, image_verify_1);

		const auto calibrated_2 = calibration.translate(digitizer_points[2]);
		const auto d_sq_2 = distance_squared(calibrated_2, image_verify_2);

		if( (d_sq_0 < verify_d_sq_max) && (d_sq_1 < verify_d_sq_max) && (d_sq_2 < verify_d_sq_max) ) {
			next_phase = Phase::Success;
		} else {
			next_phase = Phase::Failure;
		}
	}

	set_phase(next_phase);
}