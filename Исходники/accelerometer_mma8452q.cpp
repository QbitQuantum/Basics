static void* create_mma8452q_config() {
    Mma8452qConfig* new_config = (Mma8452qConfig*)calloc(1, sizeof(Mma8452qConfig));

    new_config->tap_threshold = 2.f;
    new_config->tap_latency = 200;
    new_config->tap_window = 300;
    new_config->tap_duration = 60;
    new_config->shake_threshold = 0.5f;
    new_config->shake_duration = 50;
    new_config->movement_threshold = 1.5f;
    new_config->movement_duration = 100;
    new_config->orientation_delay = 100;
    new_config->active_timeout = 0;
    //    shake_axis(MBL_MW_ACC_MMA8452Q_AXIS_X),
    new_config->movement_axis_x = 1;
    new_config->movement_axis_y = 1;
    new_config->movement_axis_z = 1;
    //    movement_type(MBL_MW_ACC_MMA8452Q_MOTION),
    //    tap_axis(MBL_MW_ACC_MMA8452Q_AXIS_Z), 
    new_config->tap_type_single = 1;
    new_config->tap_type_double = 0;
    new_config->odr = MBL_MW_ACC_MMA8452Q_ODR_100HZ;
    new_config->accel_fsr = MBL_MW_ACC_MMA8452Q_FSR_2G;
    return new_config;
}