void mbl_mw_dataprocessor_create_passthrough(MblMwDataSignal *source, MblMwPassthroughMode mode, uint16_t count, 
        MblMwFnDataProcessor processor_created) {
    MblMwDataProcessor *new_processor = new MblMwDataProcessor(*source);

    PassthroughConfig *config = (PassthroughConfig*) malloc(sizeof(PassthroughConfig));
    config->mode= mode;
    memcpy(((uint8_t*)(config)) + 1, &count, sizeof(count));
    create_processor(source, config, sizeof(PassthroughConfig), DataProcessorType::PASSTHROUGH, new_processor, processor_created);
}