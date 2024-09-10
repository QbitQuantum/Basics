std::string IDSEXT::InvokeMethod(const std::string& command)
{
    int index = command.find_first_of(" ");

    string strCommand = command.substr(0, index);
    string strParam = command.substr(index + 1, command.length());

    Json::Reader reader;
    Json::Value obj;
    if (strCommand == "getVersion") {
        return GetVersion();
    } else if (strCommand == "registerProvider") {
        return RegisterProvider(strParam);
    } else if (strCommand == "setOption") {
        // parse the JSON
        bool parse = reader.parse(strParam, obj);

        if (!parse) {
            //fprintf(stderr, "%s\n", "error parsing\n");
            return "unable to parse options";
        }
        int option = obj["option"].asInt();
        const std::string value = obj["value"].asString();
        return( SetOption(option, value) );
    } else if (strCommand == "getToken") {
        // parse the JSON
        bool parse = reader.parse(strParam, obj);

        if (!parse) {
            //fprintf(stderr, "%s", "error parsing\n");
            return "unable to parse options";
        }
        event_id = obj["_eventId"].asString();
        std::string provider = obj["provider"].asString();
        std::string tokenType = obj["tokenType"].asString();
        const std::string appliesTo = obj["appliesTo"].asString();

        GetToken(provider, tokenType, appliesTo);
    } else if (strCommand == "clearToken") {
            // parse the JSON
        bool parse = reader.parse(strParam, obj);

        if (!parse) {
            //fprintf(stderr, "%s", "error parsing\n");
            return "unable to parse options";
        }
        event_id = obj["_eventId"].asString();
        std::string provider = obj["provider"].asString();
        std::string tokenType = obj["tokenType"].asString();
        const std::string appliesTo = obj["appliesTo"].asString();

        ClearToken(provider, tokenType, appliesTo);
    } else if (strCommand == "getProperties") {
        // parse the JSON
        bool parse = reader.parse(strParam, obj);
        if (!parse) {
            //fprintf(stderr, "%s", "error parsing\n");
            return "unable to parse options";
        }
        event_id = obj["_eventId"].asString();
        std::string provider = obj["provider"].asString();
        int propertyType = obj["propertyType"].asInt();
        int numProps = obj["numProps"].asInt();
        const std::string userProps = obj["userProperties"].asString();
        GetProperties(provider, propertyType, numProps, userProps);
    } else if (strCommand == "getData") {
        // parse the JSON
        bool parse = reader.parse(strParam, obj);
        if (!parse) {
            //fprintf(stderr, "%s", "error parsing\n");
            return "unable to parse options";
        }
        event_id = obj["_eventId"].asString();
        std::string provider = obj["provider"].asString();
        int dataType = obj["dataType"].asInt();
        int dataFlags = obj["dataFlags"].asInt();
        const std::string dataName = obj["dataName"].asString();
        GetData(provider, dataType, dataFlags, dataName);
    } else if (strCommand == "createData") {
        // parse the JSON
        bool parse = reader.parse(strParam, obj);
        if (!parse) {
            //fprintf(stderr, "%s", "error parsing\n");
            return "unable to parse options";
        }
        event_id = obj["_eventId"].asString();
        std::string provider = obj["provider"].asString();
        int dataType = obj["dataType"].asInt();
        int dataFlags = obj["dataFlags"].asInt();
        const std::string dataName = obj["dataName"].asString();
        const std::string dataValue = obj["dataValue"].asString();
        CreateData(provider, dataType, dataFlags, dataName, dataValue);
    } else if (strCommand == "deleteData") {
        // parse the JSON
        bool parse = reader.parse(strParam, obj);
        if (!parse) {
            //fprintf(stderr, "%s", "error parsing\n");
            return "unable to parse options";
        }
        event_id = obj["_eventId"].asString();
        std::string provider = obj["provider"].asString();
        int dataType = obj["dataType"].asInt();
        int dataFlags = obj["dataFlags"].asInt();
        const std::string dataName = obj["dataName"].asString();
        DeleteData(provider, dataType, dataFlags, dataName);
    } else if (strCommand == "setData") {
        // parse the JSON
        bool parse = reader.parse(strParam, obj);
        if (!parse) {
            //fprintf(stderr, "%s", "error parsing\n");
            return "unable to parse options";
        }
        event_id = obj["_eventId"].asString();
        std::string provider = obj["provider"].asString();
        int dataType = obj["dataType"].asInt();
        int dataFlags = obj["dataFlags"].asInt();
        const std::string dataName = obj["dataName"].asString();
        const std::string dataValue = obj["dataValue"].asString();
        SetData(provider, dataType, dataFlags, dataName, dataValue);
    } else if (strCommand == "listData") {
        // parse the JSON
        bool parse = reader.parse(strParam, obj);
        if (!parse) {
            //fprintf(stderr, "%s", "error parsing\n");
            return "unable to parse options";
        }
        event_id = obj["_eventId"].asString();
        std::string provider = obj["provider"].asString();
        int dataType = obj["dataType"].asInt();
        int dataFlags = obj["dataFlags"].asInt();
        ListData(provider, dataType, dataFlags);
    } else if (strCommand == "challenge") {
        // parse the JSON
        bool parse = reader.parse(strParam, obj);
        if (!parse) {
            //fprintf(stderr, "%s", "error parsing\n");
            return "unable to parse options";
        }
        event_id = obj["_eventId"].asString();
        std::string provider = obj["provider"].asString();
        int challengeType = obj["challengeType"].asInt();
        int challengeFlags = obj["challengeFlags"].asInt();
        Challenge(provider, challengeType, challengeFlags);
    } else if (strCommand == "registerNotifier") {
        // parse the JSON
        bool parse = reader.parse(strParam, obj);
        if (!parse) {
            //fprintf(stderr, "%s", "error parsing\n");
            return "unable to parse options";
        }
        event_id = obj["_eventId"].asString();
        std::string provider = obj["provider"].asString();
        int notifierType = obj["notifierType"].asInt();
        int notifierFlags = obj["notifierFlags"].asInt();
        std::string notifierName = obj["notifierName"].asString();
        RegisterNotifier(provider, notifierType, notifierFlags, notifierName);
    }

    return "";
}