void TLSLogForwarderRunner::check() {
  // Instead of using the 'help' database API, prefer to interact with the
  // DBHandle directly for additional performance.
  auto handle = DBHandle::getInstance();

  // Get a list of all the buffered log items, with a max of 1024 lines.
  std::vector<std::string> indexes;
  auto status = handle->Scan(kLogs, indexes, kTLSMaxLogLines);

  // For each index, accumulate the log line into the result or status set.
  std::vector<std::string> results, statuses;
  iterate(indexes,
          ([&handle, &results, &statuses](std::string& index) {
            std::string value;
            auto& target = ((index.at(0) == 'r') ? results : statuses);
            if (handle->Get(kLogs, index, value)) {
              // Enforce a max log line size for TLS logging.
              if (value.size() > FLAGS_logger_tls_max) {
                LOG(WARNING) << "Line exceeds TLS logger max: " << value.size();
              } else {
                target.push_back(std::move(value));
              }
            }
          }));

  // If any results/statuses were found in the flushed buffer, send.
  if (results.size() > 0) {
    status = send(results, "result");
    if (!status.ok()) {
      VLOG(1) << "Could not send results to logger URI: " << uri_ << " ("
              << status.getMessage() << ")";
    } else {
      // Clear the results logs once they were sent.
      iterate(indexes,
              ([&results](std::string& index) {
                if (index.at(0) != 'r') {
                  return;
                }
                deleteDatabaseValue(kLogs, index);
              }));
    }
  }

  if (statuses.size() > 0) {
    status = send(statuses, "status");
    if (!status.ok()) {
      VLOG(1) << "Could not send status logs to logger URI: " << uri_ << " ("
              << status.getMessage() << ")";
    } else {
      // Clear the status logs once they were sent.
      iterate(indexes,
              ([&results](std::string& index) {
                if (index.at(0) != 's') {
                  return;
                }
                deleteDatabaseValue(kLogs, index);
              }));
    }
  }
}