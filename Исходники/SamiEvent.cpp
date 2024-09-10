JsonObject*
SamiEvent::asJsonObject() {
    JsonObject *pJsonObject = new JsonObject();
    pJsonObject->Construct();

    
    JsonString *p_idKey = new JsonString(L"_id");
    pJsonObject->Add(p_idKey, toJson(getPId(), "String", ""));

    
    JsonString *pTypeKey = new JsonString(L"type");
    pJsonObject->Add(pTypeKey, toJson(getPType(), "String", ""));

    
    JsonString *pRefererKey = new JsonString(L"referer");
    pJsonObject->Add(pRefererKey, toJson(getPReferer(), "String", ""));

    
    JsonString *pOriginal_urlKey = new JsonString(L"original_url");
    pJsonObject->Add(pOriginal_urlKey, toJson(getPOriginalUrl(), "String", ""));

    
    JsonString *pOriginator_emailKey = new JsonString(L"originator_email");
    pJsonObject->Add(pOriginator_emailKey, toJson(getPOriginatorEmail(), "String", ""));

    
    JsonString *pSubject_emailKey = new JsonString(L"subject_email");
    pJsonObject->Add(pSubject_emailKey, toJson(getPSubjectEmail(), "String", ""));

    
    JsonString *pParent_event_idKey = new JsonString(L"parent_event_id");
    pJsonObject->Add(pParent_event_idKey, toJson(getPParentEventId(), "String", ""));

    
    JsonString *pOriginator_idKey = new JsonString(L"originator_id");
    pJsonObject->Add(pOriginator_idKey, toJson(getPOriginatorId(), "String", ""));

    
    JsonString *pAdvisor_idKey = new JsonString(L"advisor_id");
    pJsonObject->Add(pAdvisor_idKey, toJson(getPAdvisorId(), "String", ""));

    
    JsonString *pSubject_idKey = new JsonString(L"subject_id");
    pJsonObject->Add(pSubject_idKey, toJson(getPSubjectId(), "String", ""));

    
    JsonString *pEvent_contentKey = new JsonString(L"event_content");
    pJsonObject->Add(pEvent_contentKey, toJson(getPEventContent(), "SamiEventContent", ""));

    
    JsonString *pCreated_atKey = new JsonString(L"created_at");
    pJsonObject->Add(pCreated_atKey, toJson(getPCreatedAt(), "String", ""));

    
    return pJsonObject;
}