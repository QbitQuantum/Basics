JsonObject*
SamiActivity::asJsonObject() {
    JsonObject *pJsonObject = new JsonObject();
    pJsonObject->Construct();

    JsonString *pTypeKey = new JsonString(L"type");
    pJsonObject->Add(pTypeKey, toJson(getPType(), "String", ""));

    JsonString *pIdKey = new JsonString(L"id");
    pJsonObject->Add(pIdKey, toJson(getPId(), "String", ""));

    JsonString *pLocation_idKey = new JsonString(L"location_id");
    pJsonObject->Add(pLocation_idKey, toJson(getPLocationId(), "String", ""));

    JsonString *pArr_timeKey = new JsonString(L"arr_time");
    pJsonObject->Add(pArr_timeKey, toJson(getPArrTime(), "Long", ""));

    JsonString *pEnd_timeKey = new JsonString(L"end_time");
    pJsonObject->Add(pEnd_timeKey, toJson(getPEndTime(), "Long", ""));

    JsonString *pWaiting_timeKey = new JsonString(L"waiting_time");
    pJsonObject->Add(pWaiting_timeKey, toJson(getPWaitingTime(), "Long", ""));

    JsonString *pDistanceKey = new JsonString(L"distance");
    pJsonObject->Add(pDistanceKey, toJson(getPDistance(), "Long", ""));

    JsonString *pDriving_timeKey = new JsonString(L"driving_time");
    pJsonObject->Add(pDriving_timeKey, toJson(getPDrivingTime(), "Long", ""));

    JsonString *pLoad_beforeKey = new JsonString(L"load_before");
    pJsonObject->Add(pLoad_beforeKey, toJson(getPLoadBefore(), "Integer", "array"));

    JsonString *pLoad_afterKey = new JsonString(L"load_after");
    pJsonObject->Add(pLoad_afterKey, toJson(getPLoadAfter(), "Integer", "array"));

    return pJsonObject;
}