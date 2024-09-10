void mbl_mw_dataprocessor_create_threshold(MblMwDataSignal *source, MblMwThresholdMode mode, float boundary, 
        float hysteresis, MblMwFnDataProcessor processor_created) {
    MblMwDataProcessor *new_processor = new MblMwDataProcessor(*source);

    if (mode == MBL_MW_THRESHOLD_MODE_BINARY) {
        new_processor->is_signed = 1;
        new_processor->convertor = ResponseConvertor::UINT32;
        new_processor->set_channel_attr(1, 1);
        new_processor->number_to_firmware = number_to_firmware_default;
    }

    int32_t scaled_boundary= (int32_t) source->number_to_firmware(source, boundary);
    uint16_t scaled_hysteresis= (uint16_t) source->number_to_firmware(source, hysteresis);

    ThresholdConfig *config = (ThresholdConfig*) malloc(sizeof(ThresholdConfig));
    *((uint8_t*) config)= 0;
    config->length= source->length() - 1;
    config->is_signed= source->is_signed;
    config->mode= mode;
    memcpy(((uint8_t*)(config)) + 1, &scaled_boundary, sizeof(scaled_boundary));
    memcpy(((uint8_t*)(config)) + 5, &scaled_hysteresis, sizeof(scaled_hysteresis));

    create_processor(source, config, sizeof(ThresholdConfig), DataProcessorType::THRESHOLD, new_processor, processor_created);
}