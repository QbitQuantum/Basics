void init_proximity_module(MblMwMetaWearBoard *board) {
    if (board->module_info.count(MBL_MW_MODULE_PROXIMITY) && board->module_info.at(MBL_MW_MODULE_PROXIMITY).present) {
        Tsl2671Config* new_config= (Tsl2671Config*) calloc(1, sizeof(Tsl2671Config));
        new_config->integration_time= 0xff;
        new_config->n_pulses= 1;
        new_config->receiver_channel= MBL_MW_PROXIMITY_TSL2671_CHANNEL_1;
        new_config->transmitter_current= MBL_MW_PROXIMITY_TSL2671_CURRENT_25MA;
        board->module_config.emplace(MBL_MW_MODULE_PROXIMITY, new_config);

        board->sensor_data_signals[PROXIMITY_TSL2671_ADC_RESPONSE_HEADER]= new MblMwDataSignal(PROXIMITY_TSL2671_ADC_RESPONSE_HEADER, board, 
                DataInterpreter::UINT32, 1, 2, 0, 0);
        board->responses[PROXIMITY_TSL2671_ADC_RESPONSE_HEADER]= response_handler_data_no_id;
    }
}