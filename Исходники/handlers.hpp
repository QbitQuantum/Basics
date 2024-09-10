    void
    operator()(const ioremap::swarm::url_fetcher::response& reply,
               const std::string& data,
               const boost::system::error_code& error) {
        const int code = reply.code();
        const bool success = (!error && (code < 400 || code >= 600));

        if (!success) {
            if (code == 0) {
                // Socket-only error, no valid http response
                const std::string &message = cocaine::format("Unable to download %s, error %s",
                                                             reply.request().url().to_string(),
                                                             error.message());
                //deferred.abort(error.value(), message);
                deferred.abort(asio::error::operation_aborted, message);
                return;
            }
        }
        callback(deferred, code, data);
    }