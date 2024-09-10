bool
VolumeWrap::handleMethod(qmf::AgentSession& session, qmf::AgentEvent& event)
{
    int ret;

    if (*this != event.getDataAddr()) {
        return false;
    }

    const std::string& methodName(event.getMethodName());
    qpid::types::Variant::Map args(event.getArguments());

    if (methodName == "getXMLDesc") {
        const char *desc = virStorageVolGetXMLDesc(_volume_ptr, 0);
        if (!desc) {
            std::string err = FORMAT_ERR(_conn, "Error getting xml description for volume (virStorageVolGetXMLDesc).", &ret);
            raiseException(session, event, err, STATUS_USER + ret);
        } else {
            event.addReturnArgument("description", desc);
            session.methodSuccess(event);
        }
        return true;
    }

    if (methodName == "delete") {
        ret = virStorageVolDelete(_volume_ptr, 0);
        if (ret < 0) {
            std::string err = FORMAT_ERR(_conn, "Error deleting storage volume (virStorageVolDelete).", &ret);
            raiseException(session, event, err, STATUS_USER + ret);
        } else {
            update();
            session.methodSuccess(event);
        }
        return true;
    }

    raiseException(session, event,
                   ERROR_UNKNOWN_METHOD, STATUS_UNKNOWN_METHOD);
    return true;
}