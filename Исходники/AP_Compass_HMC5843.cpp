// Public Methods //////////////////////////////////////////////////////////////
bool
AP_Compass_HMC5843::init()
{
    int numAttempts = 0, good_count = 0;
    bool success = false;
    uint8_t calibration_gain = 0x20;
    uint16_t expected_x = 715;
    uint16_t expected_yz = 715;
    float gain_multiple = 1.0;

    hal.scheduler->delay(10);

    _i2c_sem = hal.i2c->get_semaphore();
    if (!_i2c_sem->take(HAL_SEMAPHORE_BLOCK_FOREVER)) {
        hal.scheduler->panic(PSTR("Failed to get HMC5843 semaphore"));
    }

    // determine if we are using 5843 or 5883L
    _base_config = 0;
    if (!write_register(ConfigRegA, SampleAveraging_8<<5 | DataOutputRate_75HZ<<2 | NormalOperation) ||
        !read_register(ConfigRegA, &_base_config)) {
        _healthy[0] = false;
        _i2c_sem->give();
        return false;
    }
    if ( _base_config == (SampleAveraging_8<<5 | DataOutputRate_75HZ<<2 | NormalOperation)) {
        // a 5883L supports the sample averaging config
        product_id = AP_COMPASS_TYPE_HMC5883L;
        calibration_gain = 0x60;
        expected_x = 766;
        expected_yz  = 713;
        gain_multiple = 660.0 / 1090;  // adjustment for runtime vs calibration gain
    } else if (_base_config == (NormalOperation | DataOutputRate_75HZ<<2)) {
        product_id = AP_COMPASS_TYPE_HMC5843;
    } else {
        // not behaving like either supported compass type
        _i2c_sem->give();
        return false;
    }

    calibration[0] = 0;
    calibration[1] = 0;
    calibration[2] = 0;

    while ( success == 0 && numAttempts < 20 && good_count < 5)
    {
        // record number of attempts at initialisation
        numAttempts++;

        // force positiveBias (compass should return 715 for all channels)
        if (!write_register(ConfigRegA, PositiveBiasConfig))
            continue;      // compass not responding on the bus
        hal.scheduler->delay(50);

        // set gains
        if (!write_register(ConfigRegB, calibration_gain) ||
            !write_register(ModeRegister, SingleConversion))
            continue;

        // read values from the compass
        hal.scheduler->delay(50);
        if (!read_raw())
            continue;      // we didn't read valid values

        hal.scheduler->delay(10);

        float cal[3];

        cal[0] = fabsf(expected_x / (float)_mag_x);
        cal[1] = fabsf(expected_yz / (float)_mag_y);
        cal[2] = fabsf(expected_yz / (float)_mag_z);

        if (cal[0] > 0.7f && cal[0] < 1.35f &&
            cal[1] > 0.7f && cal[1] < 1.35f &&
            cal[2] > 0.7f && cal[2] < 1.35f) {
            good_count++;
            calibration[0] += cal[0];
            calibration[1] += cal[1];
            calibration[2] += cal[2];
        }

#if 0
        /* useful for debugging */
        hal.console->printf_P(PSTR("MagX: %d MagY: %d MagZ: %d\n"), (int)_mag_x, (int)_mag_y, (int)_mag_z);
        hal.console->printf_P(PSTR("CalX: %.2f CalY: %.2f CalZ: %.2f\n"), cal[0], cal[1], cal[2]);
#endif
    }

    if (good_count >= 5) {
        calibration[0] = calibration[0] * gain_multiple / good_count;
        calibration[1] = calibration[1] * gain_multiple / good_count;
        calibration[2] = calibration[2] * gain_multiple / good_count;
        success = true;
    } else {
        /* best guess */
        calibration[0] = 1.0;
        calibration[1] = 1.0;
        calibration[2] = 1.0;
    }

    // leave test mode
    if (!re_initialise()) {
        _i2c_sem->give();
        return false;
    }

    _i2c_sem->give();
    _initialised = true;

	// perform an initial read
	_healthy[0] = true;
	read();

    return success;
}