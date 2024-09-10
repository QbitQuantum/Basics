    void
    operator()(Deferred& deferred, int code, const std::string& data) const {
        if (code == HTTP_OK) {
            deferred.write(std::make_tuple(true, data));
        } else {
            rapidjson::Document root;
            root.Parse<0>(data.c_str());
            if (root.HasParseError()) {
                deferred.abort(asio::error::operation_aborted, cocaine::format("parsing failed - %s", root.GetParseError()));
                return;
            }

            const std::string& error = root.HasMember("error") ? root["error"].GetString() : "";
            const std::string& reason = cocaine::format("%s[%d]", error, code);
            deferred.write(std::make_tuple(false, reason));
        }
    }