void init_gyro_module(MblMwMetaWearBoard *board) {
    if (board->module_info.count(MBL_MW_MODULE_GYRO) && board->module_info.at(MBL_MW_MODULE_GYRO).present) {
        if (!board->module_config.count(MBL_MW_MODULE_GYRO)) {
            GyroBmi160Config *new_config = (GyroBmi160Config*)malloc(sizeof(GyroBmi160Config));

            memset(new_config, 0, sizeof(GyroBmi160Config));
            new_config->gyr_bwp = 2;
            new_config->gyr_odr = MBL_MW_GYRO_BMI160_ODR_100HZ;
            new_config->gyr_range = MBL_MW_GYRO_BMI160_FSR_2000DPS;
            board->module_config.emplace(MBL_MW_MODULE_GYRO, new_config);
        }

        MblMwDataSignal* rotation;
        if (board->module_events.count(GYRO_ROT_RESPONSE_HEADER)) {
            rotation = dynamic_cast<MblMwDataSignal*>(board->module_events[GYRO_ROT_RESPONSE_HEADER]);
        } else {
            rotation = CREATE_ROT_SIGNAL(DataInterpreter::BMI160_ROTATION, 3, 0);
            board->module_events[GYRO_ROT_RESPONSE_HEADER] = rotation;
        }
        if (!rotation->components.size()) {
            rotation->components.push_back(CREATE_ROT_SIGNAL_SINGLE(0));
            rotation->components.push_back(CREATE_ROT_SIGNAL_SINGLE(2));
            rotation->components.push_back(CREATE_ROT_SIGNAL_SINGLE(4));
        }

        board->responses[GYRO_ROT_RESPONSE_HEADER]= response_handler_data_no_id;

        if (board->module_info.at(MBL_MW_MODULE_GYRO).revision >= PACKED_ROT_REVISION) {
            if (!board->module_events.count(GYRO_PACKED_ROT_RESPONSE_HEADER)) {
                board->module_events[GYRO_PACKED_ROT_RESPONSE_HEADER]= new MblMwDataSignal(GYRO_PACKED_ROT_RESPONSE_HEADER, board, 
                    DataInterpreter::BMI160_ROTATION, FirmwareConverter::BMI160_ROTATION, 3, 2, 1, 0);
            }
            board->responses[GYRO_PACKED_ROT_RESPONSE_HEADER]= response_handler_packed_data;
        }
    }
}