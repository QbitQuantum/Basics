JsonObject*
SamiShipment::asJsonObject() {
    JsonObject *pJsonObject = new JsonObject();
    pJsonObject->Construct();

    JsonString *pIdKey = new JsonString(L"id");
    pJsonObject->Add(pIdKey, toJson(getPId(), "String", ""));

    JsonString *pNameKey = new JsonString(L"name");
    pJsonObject->Add(pNameKey, toJson(getPName(), "String", ""));

    JsonString *pPriorityKey = new JsonString(L"priority");
    pJsonObject->Add(pPriorityKey, toJson(getPPriority(), "Integer", ""));

    JsonString *pPickupKey = new JsonString(L"pickup");
    pJsonObject->Add(pPickupKey, toJson(getPPickup(), "SamiStop", ""));

    JsonString *pDeliveryKey = new JsonString(L"delivery");
    pJsonObject->Add(pDeliveryKey, toJson(getPDelivery(), "SamiStop", ""));

    JsonString *pSizeKey = new JsonString(L"size");
    pJsonObject->Add(pSizeKey, toJson(getPSize(), "Integer", "array"));

    JsonString *pRequired_skillsKey = new JsonString(L"required_skills");
    pJsonObject->Add(pRequired_skillsKey, toJson(getPRequiredSkills(), "String", "array"));

    JsonString *pAllowed_vehiclesKey = new JsonString(L"allowed_vehicles");
    pJsonObject->Add(pAllowed_vehiclesKey, toJson(getPAllowedVehicles(), "String", "array"));

    return pJsonObject;
}