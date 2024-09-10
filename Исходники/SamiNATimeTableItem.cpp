JsonObject*
SamiNATimeTableItem::asJsonObject() {
    JsonObject *pJsonObject = new JsonObject();
    pJsonObject->Construct();


    JsonString *pIdKey = new JsonString(L"id");
    pJsonObject->Add(pIdKey, toJson(getPId(), "Integer", ""));


    JsonString *pM_offsetKey = new JsonString(L"m_offset");
    pJsonObject->Add(pM_offsetKey, toJson(getPMOffset(), "Integer", ""));


    return pJsonObject;
}