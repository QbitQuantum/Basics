api_return QueueApi::handleAddDirectoryBundle(ApiRequest& aRequest) {
    const auto& reqJson = aRequest.getRequestBody();

    BundleFileInfo::List files;
    for (const auto& fileJson : reqJson["files"]) {
        files.push_back(BundleFileInfo(
                            JsonUtil::getField<string>("name", reqJson),
                            Deserializer::deserializeTTH(fileJson),
                            JsonUtil::getField<int64_t>("size", reqJson),
                            JsonUtil::getField<time_t>("time", reqJson),
                            Deserializer::deserializePriority(fileJson, true))
                       );
    }

    BundlePtr b = nullptr;
    std::string errors;
    try {
        b = QueueManager::getInstance()->createDirectoryBundle(
                JsonUtil::getField<string>("target", reqJson),
                Deserializer::deserializeHintedUser(reqJson),
                files,
                Deserializer::deserializePriority(reqJson, true),
                JsonUtil::getField<time_t>("time", reqJson),
                errors
            );
    }
    catch (const QueueException& e) {
        aRequest.setResponseErrorStr(e.getError());
        return websocketpp::http::status_code::internal_server_error;
    }

    if (b) {
        json retJson = {
            { "id", b->getToken() },
            { "errors", errors }
        };

        aRequest.setResponseBody(retJson);
    }

    return websocketpp::http::status_code::ok;
}