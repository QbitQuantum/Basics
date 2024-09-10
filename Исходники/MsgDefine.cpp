void CBookingInquiryResultMsg::ParseJSon(const char* json)
{
    USES_CONVERSION;

    Json::Reader reader;
    Json::Value root;

    if (reader.parse(json, root))
    {
        Error = root["errcode"].asInt();
        ErrMsg = A2T(root["errmsg"].asString().c_str());

        Json::Value data = root["data"];
        Json::Value secs = data["secs"];

        for (UINT i = 0; i < secs.size(); i++)
        {
            Json::Value &current = secs[i];
            CSecs *SSecs = new CSecs();
            Secs.push_back(SSecs);

            SSecs->StockID = A2T(current["stock_id"].asString().c_str());
            SSecs->Volume = current["volume"].asUInt();
        }
    }
}