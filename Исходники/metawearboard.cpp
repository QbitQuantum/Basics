uint8_t* mbl_mw_metawearboard_serialize(const MblMwMetaWearBoard* board, uint32_t* size) {
    vector<uint8_t> serialized_state;

    serialized_state.push_back(SIGNAL_COMPONENT_SERIALIZATION_FORMAT);
    
    board->firmware_revision.serialize(serialized_state);

    serialized_state.push_back((uint8_t)board->module_number.size());
    serialized_state.insert(serialized_state.end(), board->module_number.begin(), board->module_number.end());

    {
        vector<uint8_t> sorted_keys;
        for (auto it : board->module_info) {
            sorted_keys.push_back(it.first);
        }
        sort(sorted_keys.begin(), sorted_keys.end());

        serialized_state.push_back((uint8_t)board->module_info.size());
        for (auto it : sorted_keys) {
            board->module_info.at(it).serialize(serialized_state);
        }
    }

    {
        uint8_t n_events= 0;
        vector<uint8_t> event_states;
        vector<ResponseHeader> sorted_keys;
        for (auto it : board->module_events) {
            sorted_keys.emplace_back(it.first.module_id, it.first.register_id, it.first.data_id);
        }
        sort(sorted_keys.begin(), sorted_keys.end());

        for (auto it : sorted_keys) {
            board->module_events.at(it)->serialize(event_states);
            n_events++;

            // serialize component signals after the main signal
            // rely on this ordering to restore the components vector
            if (MblMwDataSignal* signal= dynamic_cast<MblMwDataSignal*>(board->module_events.at(it))) {
                for(auto component: signal->components) {
                    component->serialize(event_states);
                    n_events++;
                }
            }
        }

        serialized_state.push_back(n_events);
        serialized_state.insert(serialized_state.end(), event_states.begin(), event_states.end());
    }

    {
        vector<uint8_t> sorted_keys;
        for (auto it : board->module_config) {
            sorted_keys.push_back(it.first);
        }
        sort(sorted_keys.begin(), sorted_keys.end());

        serialized_state.push_back((uint8_t)board->module_config.size());
        for (auto it : sorted_keys) {
            serialized_state.push_back(it);
            CONFIG_SERIALIZATION.at(it)(board, serialized_state);
        }
    }
    
    serialize_logging(board, serialized_state);
    
    *size = (uint32_t) serialized_state.size();
    uint8_t* state_bytes = (uint8_t*)malloc(sizeof(uint8_t) * (*size));
    memcpy(state_bytes, serialized_state.data(), *size);
    return state_bytes;
}