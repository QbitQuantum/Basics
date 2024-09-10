void RDPListener::RunServer()
{
    int status = 0;
    DWORD exitCode = 0;
    rdp_listener_object = this; // store a reference to the object in thread-local storage for the shadow server

    std::string config_path = vm["config-path"].as<std::string>();
    this->server->ConfigPath = _strdup(config_path.c_str());

    // dbus setup
    Glib::RefPtr<Gio::DBus::NodeInfo> introspection_data;
    const Gio::DBus::InterfaceVTable vtable(sigc::mem_fun(this, &RDPListener::on_method_call),
                                            sigc::mem_fun(this, &RDPListener::on_property_call));
    // create server name
    Glib::ustring dbus_name = "/org/RDPMux/RDPListener/";
    // sanitize uuid before creating dbus object
    std::string tmp = uuid;
    tmp.erase(std::remove(tmp.begin(), tmp.end(), '-'), tmp.end());
    dbus_name += tmp;

    if (shadow_server_init(this->server) < 0) {
        VLOG(1) << "COULD NOT INIT SHADOW SERVER!!!!!";
        goto cleanup;
    }

    try {
        introspection_data = Gio::DBus::NodeInfo::create_for_xml(introspection_xml);
    } catch (const Glib::Error &ex) {
        LOG(WARNING) << "LISTENER " << this << ": Unable to create introspection data.";
        goto cleanup;
    }

    try {
        registered_id = dbus_conn->register_object(dbus_name, introspection_data->lookup_interface(), vtable);
    } catch (Gio::Error &e) {
        LOG(WARNING) << "LISTENER " << this << ": Could not take listener name on bus. Is there a duplicate registered?";
        goto cleanup;
    }

    this->server->port = this->port;

    // Shadow server run loop
    if (shadow_server_start(this->server) < 0) {
        VLOG(1) << "COULD NOT START SHADOW SERVER!!!!!";
        goto cleanup;
    }

    {
        std::lock_guard<std::mutex> lock(listenerStopMutex);
        listener_running = true;
    }

    while (true) {
        WaitForSingleObject(this->server->thread, 150);
        {
            std::lock_guard<std::mutex> lock(listenerStopMutex);
            if (!listener_running) {
                break;
            }
        }
    }

    VLOG(1) << "LISTENER " << this << ": Main loop exited, exit code " << status;
cleanup:
    shutdown(); // this will trigger destruction of the RDPListener object.
}