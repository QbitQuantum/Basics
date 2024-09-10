JsonObject*
SamiNewsletter::asJsonObject() {
    JsonObject *pJsonObject = new JsonObject();
    pJsonObject->Construct();

    
    JsonString *p_idKey = new JsonString(L"_id");
    pJsonObject->Add(p_idKey, toJson(getPId(), "String", ""));

    
    JsonString *pIs_sentKey = new JsonString(L"is_sent");
    pJsonObject->Add(pIs_sentKey, toJson(getPIsSent(), "Boolean", ""));

    
    JsonString *pIs_defaultKey = new JsonString(L"is_default");
    pJsonObject->Add(pIs_defaultKey, toJson(getPIsDefault(), "Boolean", ""));

    
    JsonString *pClick_countKey = new JsonString(L"click_count");
    pJsonObject->Add(pClick_countKey, toJson(getPClickCount(), "Long", ""));

    
    JsonString *pUnique_click_countKey = new JsonString(L"unique_click_count");
    pJsonObject->Add(pUnique_click_countKey, toJson(getPUniqueClickCount(), "Long", ""));

    
    JsonString *pTotal_click_countKey = new JsonString(L"total_click_count");
    pJsonObject->Add(pTotal_click_countKey, toJson(getPTotalClickCount(), "Long", ""));

    
    return pJsonObject;
}