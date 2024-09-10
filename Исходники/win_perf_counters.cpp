// Update the data to be exposed as the windows performance counter values.
void update_windows_counters(boost::uint64_t value)
{
    // Set raw counter data for queue length.
    ULONG status = PerfSetULongCounterValue
        (HPXHeartBeat, queue_counter, 1, ULONG(value));
    if (status != ERROR_SUCCESS) {
        std::cerr << "PerfSetCounterRefValue for 'sum_queue_counter' failed "
                     "with error code: "
                  << std::to_string(GetLastError());
        return;
    }

    // Set raw counter data for average queue length.
    status = PerfSetULongCounterValue(HPXHeartBeat, avg_queue_counter, 2, ULONG(value));
    if (status != ERROR_SUCCESS) {
        std::cerr << "PerfSetCounterRefValue for 'avg_queue_counter' failed "
                     "with error code: "
                  << std::to_string(GetLastError());
        return;
    }
}