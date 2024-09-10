void UpdateUserData::handle(Manager* manager, SharedManager* sManager) {
    bool validation = this->validateInput();
    if(validation) {
        struct mg_str *cl_header = mg_get_http_header(hm, "Token");
        if(!cl_header) {
            this->response(1, "Token Missing ", returnEmptyJsonObject());
            return;
        }
        Json::Reader r = Json::Reader();
        Json::Value value = Json::Value();
        r.parse(hm->body.p, value);
        // Local user update
        User* user = manager->getUser(value.get("username","").asString());
        if(!user) {
            this->response(1, "User could not be modified", returnEmptyJsonObject());
            return;
        }
        std::string token(getHeaderParam(cl_header->p));
        if(token.compare(user->getToken()) != 0) {
            this->response(2, "Invalid Token", returnEmptyJsonObject());
            return;
        }
        user->updateWithJson(value);
        bool updateUser = manager->updateUser(user);
        if(updateUser) {
            value["id"] = user->getId();
            if(value.isMember("photoProfile") || value.isMember("photo_profile")) {
                // Photo Profile Upload
                std::string key = "";
                value.isMember("photoProfile") ? key = "photoProfile" : key = "photo_profile";
                Json::Value uploadP = Json::Value();
                uploadP["photo"] = value.get(key, "").asString();
                uploadP["id"] = user->getId();
                value.removeMember(key);
                int photoUp = sManager->putUserPhoto(uploadP);
                if(!photoUp) {
                    this->response(1, "User photo profile could not be uploaded", returnEmptyJsonObject());
                    return;
                }
            }
            // Rest of user data to update on Shared Server
            // TODO: Falta subir los intereses nuevos que haya!
            if(value.isMember("interests")) {
                Json::Value interests = value.get("interests", Json::Value(Json::arrayValue));
                Json::ValueConstIterator interestsIt = interests.begin();
                while(interestsIt != interests.end()) {
                    Json::Value response = sManager->postInterest(*interestsIt);
                    // TODO: Alguna cola para reupload de intereses que debieron subir
                    // pero no pudieron por algun problema (que no sea duplicado)
                    interestsIt++;
                }
            }
            if(value.isMember("edad")) value["age"] = value.get("edad", 18).asInt();
            int sharedUpdate = sManager->putUser(value);
            if(sharedUpdate) {
                this->response(0, "Modified", user->getJson());
            } else {
                this->response(1, "User could not be modified", returnEmptyJsonObject());
            }
        } else {
            this->response(1, "User could not be modified", returnEmptyJsonObject());
        }
        delete user;
    }
}