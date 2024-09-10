void JsonValue::getEXTfldvalForValue(tThreadData* pThreadData, EXTfldval &retVal, Json::Value* posPointer) {
    // Create return value object
    JsonValue *newObj = createNVObj<JsonValue>(pThreadData);
    if ( posPointer != 0 ) {
        // Return pointer to found position
        newObj->setJsonValue(document, posPointer); // Set value and pointer to source
    } else {
        // Create and return new null object
        shared_ptr<Json::Value> nullObj(new Json::Value());
        newObj->setJsonValue(nullObj);
    }

    retVal.setObjInst( newObj->getInstance(), qtrue );
}