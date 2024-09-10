static inline int32_t create_combiner(MblMwDataSignal *source, DataProcessorType combiner_type,
        MblMwFnDataProcessor processor_created) {
    if (source->n_channels <= 1) {
        return MBL_MW_STATUS_ERROR_UNSUPPORTED_PROCESSOR;
    }

    MblMwDataProcessor *new_processor = new MblMwDataProcessor(*source);
    new_processor->is_signed= 0;
    new_processor->offset= 0;
    new_processor->set_channel_attr(1, source->channel_size);

    switch (source->interpreter) {
    case DataInterpreter::BMI160_ACCELERATION:
        new_processor->interpreter= DataInterpreter::BMI160_ACCELERATION_SINGLE_AXIS;
        break;
    case DataInterpreter::MMA8452Q_ACCELERATION:
        new_processor->interpreter = DataInterpreter::MMA8452Q_ACCELERATION_SINGLE_AXIS;
        break;
    case DataInterpreter::BMI160_ROTATION:
        new_processor->interpreter = DataInterpreter::BMI160_ROTATION_SINGLE_AXIS;
        break;
    default:
        break;
    }

    CombinerConfig *config = (CombinerConfig*) malloc(sizeof(CombinerConfig));
    config->output= source->channel_size - 1;
    config->input= source->channel_size - 1;
    config->count= source->n_channels - 1;
    config->is_signed= source->is_signed;
    config->mode= combiner_type == DataProcessorType::RMS ? MODE_RMS : MODE_RSS;
    create_processor(source, config, sizeof(CombinerConfig), combiner_type, new_processor, processor_created);

    return MBL_MW_STATUS_OK;
}