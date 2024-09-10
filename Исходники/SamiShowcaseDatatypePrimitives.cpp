JsonObject*
SamiShowcaseDatatypePrimitives::asJsonObject() {
    JsonObject *pJsonObject = new JsonObject();
    pJsonObject->Construct();

    
    JsonString *pSingleByteKey = new JsonString(L"singleByte");
    pJsonObject->Add(pSingleByteKey, toJson(getPSingleByte(), "String", ""));

    
    JsonString *pTinyNumberKey = new JsonString(L"tinyNumber");
    pJsonObject->Add(pTinyNumberKey, toJson(getPTinyNumber(), "Integer", ""));

    
    JsonString *pCounterKey = new JsonString(L"counter");
    pJsonObject->Add(pCounterKey, toJson(getPCounter(), "Integer", ""));

    
    JsonString *pIdKey = new JsonString(L"id");
    pJsonObject->Add(pIdKey, toJson(getPId(), "Long", ""));

    
    JsonString *pBudgetFloatKey = new JsonString(L"budgetFloat");
    pJsonObject->Add(pBudgetFloatKey, toJson(getPBudgetFloat(), "Long", ""));

    
    JsonString *pBudgetKey = new JsonString(L"budget");
    pJsonObject->Add(pBudgetKey, toJson(getPBudget(), "Double", ""));

    
    JsonString *pDeletedKey = new JsonString(L"deleted");
    pJsonObject->Add(pDeletedKey, toJson(getPDeleted(), "Boolean", ""));

    
    JsonString *pSingleCharacterKey = new JsonString(L"singleCharacter");
    pJsonObject->Add(pSingleCharacterKey, toJson(getPSingleCharacter(), "String", ""));

    
    return pJsonObject;
}