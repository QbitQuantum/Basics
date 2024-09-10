/** \brief event by event analysis
 *
 * ScanList() operates on the time sorted list of all channels that triggered in
 * a given spill.  Starting from the begining of the list and continuing to the
 * end, an individual channel event time is compared with the previous channel
 * event time to determine if they occur within a time period defined by the
 * diff_t variable (time is in units of 10 ns).  Depending on the answer,
 * different actions are performed:
 *   - yes - the two channels are grouped together as belonging to the same event
 *   and the current channel is added to the list of channels for the rawevent
 *   - no - the previous rawevent is sent for processing and once finished, the
 *   rawevent is zeroed and the current channel placed inside it.
 * \param [in] eventList : The event list to scan
 * \param [in] rawev : the raw event to read */
void ScanList(vector<ChanEvent*> &eventList, RawEvent& rawev) {
    unsigned long chanTime, eventTime;

    DetectorLibrary* modChan = DetectorLibrary::get();
    DetectorDriver* driver = DetectorDriver::get();
    Messenger messenger;
    stringstream ss;
    /** Rejection regions */
    vector< pair<int, int> > rejectRegions = Globals::get()->rejectRegions();

    // local variable for the detectors used in a given event
    set<string> usedDetectors;

    vector<ChanEvent*>::iterator iEvent = eventList.begin();

    // local variables for the times of the current event, previous
    // event and time difference between the two
    double diffTime = 0;

    //set last_t to the time of the first event
    double lastTime = (*iEvent)->GetTime();
    double currTime = lastTime;
    unsigned int id = (*iEvent)->GetID();

    /* KM
     * Save time of the beginning of the file,
     * this is needed for the rejection regions */
    static double firstTime = lastTime;
    HistoStats(id, diffTime, lastTime, BUFFER_START);

    //loop over the list of channels that fired in this buffer
    for(; iEvent != eventList.end(); iEvent++) {
        id = (*iEvent)->GetID();
        if (id == pixie::U_DELIMITER) {
            ss << "pattern 0 ignore";
            messenger.warning(ss.str());
            ss.str("");
            continue;
        }
        if ((*modChan)[id].GetType() == "ignore") {
            continue;
        }

        // this is a channel we're interested in
        chanTime  = (*iEvent)->GetTrigTime();
        eventTime = (*iEvent)->GetEventTimeLo();

        /* retrieve the current event time and determine the time difference
        between the current and previous events.
        */
        currTime = (*iEvent)->GetTime();
        diffTime = currTime - lastTime;

        /* KM: rejection of bad regions
         * If time (in sec) is within the 'bad' region
         * just drop the rest of this for loop and go for another buffer
         *
         * Do checks only if hasReject flag is True.
         */
        if (Globals::get()->hasReject()) {
            double bufferTime = (currTime - firstTime) *
                                 Globals::get()->clockInSeconds();
            bool rejectBuffer = false;
            for (vector< pair<int, int> >::iterator region = rejectRegions.begin();
                 region != rejectRegions.end();
                 ++region ) {
                /** If event time is within a rejection region
                 * set rejectBuffer flag true and stop checking */
                if (bufferTime > region->first &&
                    bufferTime < region->second) {
                    rejectBuffer = true;
                    break;
                }
            }
            if (rejectBuffer)
                continue;
        }
        /* end KM */

        /* if the time difference between the current and previous event is
        larger than the event width, finalize the current event, otherwise
        treat this as part of the current event
        */
        if ( diffTime > Globals::get()->eventWidth() ) {
            if(rawev.Size() > 0) {
            /* detector driver accesses rawevent externally in order to
            have access to proper detector_summaries
            */
                driver->ProcessEvent(rawev);
            }

            //after processing zero the rawevent variable
            rawev.Zero(usedDetectors);
            usedDetectors.clear();

            // Now clear all places in correlator (if resetable type)
            for (map<string, Place*>::iterator it =
                    TreeCorrelator::get()->places_.begin();
                it != TreeCorrelator::get()->places_.end(); ++it)
                if ((*it).second->resetable())
                    (*it).second->reset();
            HistoStats(id, diffTime, currTime, EVENT_START);
        } else HistoStats(id, diffTime, currTime, EVENT_CONTINUE);

        unsigned long dtimebin = 2000 + eventTime - chanTime;
        if (dtimebin < 0 || dtimebin > (unsigned)(SE)) {
            ss << "strange dtime for id " << id << ":" << dtimebin;
            messenger.warning(ss.str());
            ss.str("");
        }
        driver->plot(D_TIME + id, dtimebin);
        usedDetectors.insert((*modChan)[id].GetType());
        rawev.AddChan(*iEvent);

        // update the time of the last event
        lastTime = currTime;
    } //end loop over event list

    //process the last event in the buffer
    if (rawev.Size() > 0) {
        string mode;
        HistoStats(id, diffTime, currTime, BUFFER_END);

        driver->ProcessEvent(rawev);
        rawev.Zero(usedDetectors);
    }
}