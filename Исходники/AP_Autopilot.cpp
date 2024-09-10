void AP_Autopilot::callback1(void * data) {
    AP_Autopilot * apo = (AP_Autopilot *) data;
    //apo->getBoard()->debug->println_P(PSTR("callback 1"));

    /*
     * update guidance laws
     */
    if (apo->getGuide())
    {
        //apo->getBoard()->debug->println_P(PSTR("updating guide"));
        apo->getGuide()->update();
    }

    /*
     * slow navigation loop update
     */
    if (apo->getNavigator()) {
        apo->getNavigator()->updateSlow(apo->subLoops()[1]->dt());
    }

    /*
     * send telemetry
     */
    if (apo->getBoard()->gcs) {
        apo->getBoard()->gcs->sendMessage(MAVLINK_MSG_ID_ATTITUDE);
        apo->getBoard()->gcs->sendMessage(MAVLINK_MSG_ID_GLOBAL_POSITION);
    }

    /*
     * handle ground control station communication
     */
    if (apo->getBoard()->gcs) {
        // send messages
        apo->getBoard()->gcs->requestCmds();
        apo->getBoard()->gcs->sendParameters();

        // receive messages
        apo->getBoard()->gcs->receive();
    }

    /*
     * navigator debug
     */
    /*
     if (apo->navigator()) {
     apo->getBoard()->debug->printf_P(PSTR("roll: %f deg\tpitch: %f deg\tyaw: %f deg\n"),
     apo->navigator()->getRoll()*rad2Deg,
     apo->navigator()->getPitch()*rad2Deg,
     apo->navigator()->getYaw()*rad2Deg);
     apo->getBoard()->debug->printf_P(PSTR("lat: %f deg\tlon: %f deg\talt: %f m\n"),
     apo->navigator()->getLat()*rad2Deg,
     apo->navigator()->getLon()*rad2Deg,
     apo->navigator()->getAlt());
     }
     */
}