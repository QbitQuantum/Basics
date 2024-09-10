void init_ambient_light_module(MblMwMetaWearBoard *board) {
    Ltr329Config* new_config = (Ltr329Config*) malloc(sizeof(Ltr329Config));

    memset(new_config, 0, sizeof(Ltr329Config));
    new_config->als_measurement_rate = MBL_MW_ALS_LTR329_RATE_500MS;
    board->module_config.emplace(MBL_MW_MODULE_AMBIENT_LIGHT, new_config);

    board->sensor_data_signals[LTR329_ILLUMINANCE_RESPONSE_HEADER]= new MblMwDataSignal(LTR329_ILLUMINANCE_RESPONSE_HEADER, 
            board, ResponseConvertor::UINT32, 1, 4, 0, 0);
}