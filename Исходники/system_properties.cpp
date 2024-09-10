int mb__system_property_set(const char* key, const char* value) {
  if (key == nullptr) return -1;
  if (value == nullptr) value = "";
  if (strlen(value) >= PROP_VALUE_MAX) return -1;

  if (g_propservice_protocol_version == 0) {
    detect_protocol_version();
  }

  if (g_propservice_protocol_version == kProtocolVersion1) {
    // Old protocol does not support long names
    if (strlen(key) >= PROP_NAME_MAX) return -1;

    prop_msg msg;
    memset(&msg, 0, sizeof msg);
    msg.cmd = PROP_MSG_SETPROP;
    strlcpy(msg.name, key, sizeof msg.name);
    strlcpy(msg.value, value, sizeof msg.value);

    return send_prop_msg(&msg);
  } else {
    // Use proper protocol
    PropertyServiceConnection connection;
    if (!connection.IsValid()) {
      errno = connection.GetLastError();
      LOGW("Unable to set property \"%s\" to \"%s\": connection failed; errno=%d (%s)",
           key,
           value,
           errno,
           strerror(errno));
      return -1;
    }

    SocketWriter writer(&connection);
    if (!writer.WriteUint32(PROP_MSG_SETPROP2).WriteString(key).WriteString(value).Send()) {
      errno = connection.GetLastError();
      LOGW("Unable to set property \"%s\" to \"%s\": write failed; errno=%d (%s)",
           key,
           value,
           errno,
           strerror(errno));
      return -1;
    }

    int result = -1;
    if (!connection.RecvInt32(&result)) {
      errno = connection.GetLastError();
      LOGW("Unable to set property \"%s\" to \"%s\": recv failed; errno=%d (%s)",
           key,
           value,
           errno,
           strerror(errno));
      return -1;
    }

    if (result != PROP_SUCCESS) {
      LOGW("Unable to set property \"%s\" to \"%s\": error code: 0x%x",
           key,
           value,
           result);
      return -1;
    }

    return 0;
  }
}