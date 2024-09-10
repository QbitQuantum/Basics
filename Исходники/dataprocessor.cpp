MblMwDataProcessor::~MblMwDataProcessor() {
    delete state;
    state = nullptr;

    free(config);
    config= nullptr;

    if (remove) {
        uint8_t command[3]= { MBL_MW_MODULE_DATA_PROCESSOR, ORDINAL(DataProcessorRegister::REMOVE), header.data_id };
        send_command(owner, command, sizeof(command));
    }
}