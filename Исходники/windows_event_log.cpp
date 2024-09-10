Status WindowsEventLoggerPlugin::emitLogRecord(
    REGHANDLE registration_handle,
    const std::string& message,
    StatusLogSeverity severity,
    const std::string& source_file_name,
    size_t line) {
  if (registration_handle == 0) {
    return Status(1, "The Windows Event Logger plugin is not initialized.");
  }

  EVENT_DATA_DESCRIPTOR data_descriptor[2] = {};
  EventDataDescCreate(&data_descriptor[0],
                      message.data(),
                      static_cast<ULONG>(message.size() + 1));

  auto location = source_file_name + ":" + std::to_string(line);
  EventDataDescCreate(&data_descriptor[1],
                      location.data(),
                      static_cast<ULONG>(location.size() + 1));

  const EVENT_DESCRIPTOR* event_descriptor = nullptr;
  switch (severity) {
  case O_WARNING: {
    event_descriptor = &WarningMessage;
    break;
  }

  case O_ERROR: {
    event_descriptor = &ErrorMessage;
    break;
  }

  case O_FATAL: {
    event_descriptor = &FatalMessage;
    break;
  }

  case O_INFO:
  default: {
    event_descriptor = &InfoMessage;
    break;
  }
  }

  auto status =
      EventWrite(registration_handle, event_descriptor, 2, data_descriptor);
  if (status != ERROR_SUCCESS) {
    auto error_message =
        std::string("Failed to publish the following log record: ") + location +
        " " + message;
    return Status(1, std::move(error_message));
  }

  return Status();
}