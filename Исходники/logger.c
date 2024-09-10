void logEventEnd(uint8_t posNo, const char *eventName) {
    struct timespec endTimestamp;
    if (clock_gettime(CLOCK_MONOTONIC, &endTimestamp)) {
        perror("logger.c: logEvent: clock_gettime failed.");
        exit(EXIT_FAILURE);
    }

    struct timespec runtime = diffTime(eventStartTimestamp[posNo], endTimestamp);

    event_t event;
    event.timestamp = runtime;
    event.name = strdup(eventName);


    if (logInitialised[posNo]) {
        event_t minEvent = logMin[posNo];
        if (compareTime(runtime, minEvent.timestamp) == 2) {
            // if minEvent.timestamp is bigger than runtime, we found a new
            // minimum candidate
            logMin[posNo] = event;
        }

        event_t maxEvent = logMax[posNo];
        if (compareTime(runtime, maxEvent.timestamp) == 1) {
            // if runtime is bigger than maxEvent.timestamp, we found a new
            // maximum candidate
            logMax[posNo] = event;
        }
    } else {
        logMin[posNo] = event;
        logMax[posNo] = event;
        logInitialised[posNo] = 1;
    }
}