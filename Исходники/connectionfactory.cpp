bool ConnectionFactory::createRemoteConnection(const enum ngsCatalogObjectType type,
                                               const std::string &path,
                                               const Options &options)
{
    switch(type) {
    case CAT_CONTAINER_NGW:
    {
        std::string url = options.asString(KEY_URL);
        if(url.empty()) {
            return errorMessage(_("Missing required option 'url'"));
        }

        std::string login = options.asString(KEY_LOGIN);
        if(login.empty()) {
            login = "******";
        }
        else {
            std::string oldLogin(login);
            login = CPLString(login).Trim();
            if(!compare(oldLogin, login, true)) {
                warningMessage("Login was trimmed!");
            }
        }
        std::string password = options.asString(KEY_PASSWORD);
        bool isGuest = options.asBool(KEY_IS_GUEST);

        CPLJSONDocument connectionFile;
        CPLJSONObject root = connectionFile.GetRoot();
        root.Add(KEY_TYPE, type);
        root.Add(KEY_URL, url);
        root.Add(KEY_LOGIN, login);
        root.Add(KEY_IS_GUEST, isGuest);
        if(!password.empty()) {
            root.Add(KEY_PASSWORD, encrypt(password));
        }

        return connectionFile.Save(path);
    }
    default:
        return errorMessage(_("Unsupported connection type %d"), type);
    }
}