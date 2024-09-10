void ChatConnection::Connect()
{
    QStatus status = ER_OK;
    assert(invariants());
    createMessageBus();
    NotifyUser(MSG_STATUS, "Start the message bus.");
    /* Start the msg bus */
    if (ER_OK == status) {
        status = this->busAttachment->Start();
        if (ER_OK != status) {
            NotifyUser(MSG_ERROR, "BusAttachment::Start failed (%s)\n", QCC_StatusText(status));
        }
    }
    /* Register a bus listener */
    if (ER_OK == status) {
        // make sure the callback has been set
        this->busAttachment->RegisterBusListener(*(this->busListener));
    }
    NotifyUser(MSG_STATUS, "Registered BusListener");

    /* Connect to the local daemon */
    NotifyUser(MSG_STATUS, "Connect to the local daemon.");
    if (ER_OK == status) {
        status = this->busAttachment->Connect();
    }
    if (ER_OK != status) {
        NotifyUser(MSG_ERROR, "BusAttachment::Connect(%s) failed (%s)\n", this->busAttachment->GetConnectSpec().c_str(), QCC_StatusText(status));
    }
    if (!this->advertisedName.empty()) {
        NotifyUser(MSG_STATUS, "Request name");
        status = this->busAttachment->RequestName(this->advertisedName.c_str(), DBUS_NAME_FLAG_DO_NOT_QUEUE);
        if (ER_OK != status) {
            NotifyUser(MSG_ERROR, "RequestName(%s) failed (status=%s)\n", this->advertisedName.c_str(), QCC_StatusText(status));
            status = (status == ER_OK) ? ER_FAIL : status;
        }
        /* Bind the session port*/
        NotifyUser(MSG_STATUS, "Bind session port.");
        SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, true, SessionOpts::PROXIMITY_ANY, TRANSPORT_ANY);
        if (ER_OK == status) {
            SessionPort sp = CHAT_PORT;
            status = this->busAttachment->BindSessionPort(sp, opts, *(this->busListener));
            if (ER_OK != status) {
                NotifyUser(MSG_ERROR, "BindSessionPort failed (%s)\n", QCC_StatusText(status));
            }
        }

        /* Advertise same well-known name */
        if (ER_OK == status) {
            status = this->busAttachment->AdvertiseName(this->advertisedName.c_str(), opts.transports);
            if (status != ER_OK) {
                NotifyUser(MSG_ERROR, "Failed to advertise name %s (%s)\n", this->advertisedName.c_str(), QCC_StatusText(status));
            }
        }
    } else {
        /* Discover name */
        status = this->busAttachment->FindAdvertisedName(this->joinName.c_str());
        if (status != ER_OK) {
            NotifyUser(MSG_ERROR, "org.alljoyn.Bus.FindAdvertisedName failed (%s)\n", QCC_StatusText(status));
        }
        NotifyUser(MSG_STATUS, "Found Advertised Name \n");
    }
    NotifyUser(MSG_STATUS, "Ready...");
}