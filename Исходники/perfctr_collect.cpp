Status PerfCounterCollector::collect(BSONObjBuilder* builder) {
    // Ask PDH to collect the counters
    PDH_STATUS status = PdhCollectQueryData(_query);
    if (status != ERROR_SUCCESS) {
        return {ErrorCodes::WindowsPdhError,
                formatFunctionCallError("PdhCollectQueryData", status)};
    }

    // Output timebase
    // Counters that are based on time either use 100NS or System Ticks Per Second.
    // We only need to output system ticks per second once if any counter depends on it.
    // This is typically 3320310.
    if (_timeBaseTicksCounter) {
        int64_t timebase;

        status = PdhGetCounterTimeBase(_timeBaseTicksCounter->handle, &timebase);
        if (status != ERROR_SUCCESS) {
            return {ErrorCodes::WindowsPdhError,
                    formatFunctionCallError("PdhGetCounterTimeBase", status)};
        }

        builder->append("timebase", timebase);
    }

    // Retrieve all the values that PDH collected for us.
    for (const auto& counterGroup : _counters) {
        BSONObjBuilder subObjBuilder(builder->subobjStart(counterGroup.name));

        Status s = collectCounters(counterGroup.counters, &subObjBuilder);
        if (!s.isOK()) {
            return s;
        }

        subObjBuilder.doneFast();
    }

    for (const auto& counterGroup : _nestedCounters) {
        BSONObjBuilder subObjBuilder(builder->subobjStart(counterGroup.name));

        for (const auto& instanceNamePair : counterGroup.counters) {
            BSONObjBuilder instSubObjBuilder(builder->subobjStart(instanceNamePair.first));

            Status s = collectCounters(instanceNamePair.second, &instSubObjBuilder);
            if (!s.isOK()) {
                return s;
            }

            instSubObjBuilder.doneFast();
        }

        subObjBuilder.doneFast();
    }

    return Status::OK();
}