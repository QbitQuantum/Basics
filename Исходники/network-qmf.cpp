gboolean
NetAgent::invoke(qmf::AgentSession session, qmf::AgentEvent event,
                 gpointer user_data)
{
    if (event.getType() != qmf::AGENT_METHOD) {
        return TRUE;
    }

    const std::string& methodName(event.getMethodName());
    qpid::types::Variant::Map& args = event.getArguments();

    if (methodName == "list") {
        GList *plist = NULL;
        GList *interface_list = NULL;

        _qtype::Variant::List s_list;

        interface_list = mh_network_get_interfaces();
        for (plist = g_list_first(interface_list); plist;
             plist = g_list_next(plist)) {
            struct mh_network_interface *iface =
                        static_cast<struct mh_network_interface *>(plist->data);
            s_list.push_back(mh_network_interface_get_name(iface));
        }
        g_list_free_full(interface_list, mh_network_interface_destroy);
        event.addReturnArgument("iface_map", s_list);
    } else if (methodName == "start") {
        int rc = interface_status(
                args["iface"].asString().c_str());

        if (rc == 1) {
            mh_network_start(args["iface"].asString().c_str());
            rc = interface_status(
                    args["iface"].asString().c_str());
        }
        event.addReturnArgument("status", rc);
    } else if (methodName == "stop") {
        int rc = interface_status(
                args["iface"].asString().c_str());
        if (rc == 0) {
            mh_network_stop(args["iface"].asString().c_str());
            rc = interface_status(
                    args["iface"].asString().c_str());
        }
        event.addReturnArgument("status", rc);
    } else if (methodName == "status") {
        event.addReturnArgument("status", interface_status(
                args["iface"].asString().c_str()));
    } else if (methodName == "get_ip_address") {
        char buf[64];
        event.addReturnArgument("ip", mh_network_get_ip_address(
                args["iface"].asString().c_str(),
                buf, sizeof(buf)));
    } else if (methodName == "get_mac_address") {
        char buf[32];
        event.addReturnArgument("mac", mh_network_get_mac_address(
                args["iface"].asString().c_str(),
                buf, sizeof(buf)));
    } else {
        session.raiseException(event, mh_result_to_str(MH_RES_NOT_IMPLEMENTED));
        goto bail;
    }

    session.methodSuccess(event);

bail:
    return TRUE;
}