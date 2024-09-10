void init_barometer_module(MblMwMetaWearBoard *board) {
    Bmp280Config* new_config = (Bmp280Config*)malloc(sizeof(Bmp280Config));

    memset(new_config, 0, sizeof(Bmp280Config));
    new_config->pressure_oversampling = MBL_MW_BARO_BMP280_OVERSAMPLE_STANDARD;
    new_config->iir_filter = MBL_MW_BARO_BMP280_IIR_FILTER_OFF;
    new_config->standby_time = MBL_MW_BARO_BMP280_STANDBY_TIME_0_5MS;
    board->module_config.emplace(MBL_MW_MODULE_BAROMETER, new_config);

    MblMwDataSignal *baro_pa_signal= new MblMwDataSignal(BARO_PRESSURE_RESPONSE_HEADER, board, 
            DataInterpreter::BMP280_PRESSURE, 1, 4, 0, 0);
    baro_pa_signal->number_to_firmware = bmp280_to_firmware;
    board->sensor_data_signals[BARO_PRESSURE_RESPONSE_HEADER]= baro_pa_signal;
    board->responses[BARO_PRESSURE_RESPONSE_HEADER]= response_handler_data_no_id;

    MblMwDataSignal *baro_m_signal= new MblMwDataSignal(BARO_ALTITUDE_RESPONSE_HEADER, board, 
            DataInterpreter::BMP280_ALTITUDE, 1, 4, 1, 0);
    baro_m_signal->number_to_firmware = bmp280_to_firmware;
    board->sensor_data_signals[BARO_ALTITUDE_RESPONSE_HEADER]= baro_m_signal;
    board->responses[BARO_ALTITUDE_RESPONSE_HEADER]= response_handler_data_no_id;
}