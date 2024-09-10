datatypes::ReturnType HaierCommonSDK::GetInfo(const datatypes::RealDevice &device,
                                              const datatypes::Attribute &attr_names, void *extra) {

    if (attr_names.GetAttributeName().compare(GET_ALARM) == 0) {

        if (device_alarm_cache.find(device) != device_alarm_cache.end()) {

            datatypes::Value value = datatypes::Value();
            if (device_alarm_cache.find(device) != device_alarm_cache.end()) {
                for (int i = 0; i < device_alarm_cache[device].size(); i++) {
                    value.InsertValue(
                            datatypes::ValueTypePair(
                                    device_alarm_cache[device][i],
                                    datatypes::ValType::STRING
                            )
                    );
                }
            }


            datatypes::AttributeValuePair pair = datatypes::AttributeValuePair(
                    datatypes::Attribute(GET_ALARM), value);
            datatypes::ReturnType returnType = datatypes::ReturnType(device, pair, "",
                                                                     datatypes::ReturnType::SDK_OK,
                                                                     "");
            return returnType;
        }
        else {

            datatypes::AttributeValuePair pair = datatypes::AttributeValuePair(datatypes::Attribute(GET_ALARM),
                                                                               datatypes::Value());

            return datatypes::ReturnType(device, pair, "", datatypes::ReturnType::SDK_OK, "");
        }


    }

    char *attr_name = (char *) attr_names.GetAttributeName().c_str();
    context_t *context = ugw_new_context();
    //while (!device_set_attr_lock);
    int ret = ugw_get_attr(handle, context, (char *) device.GetDeviceId().c_str(), attr_name);

    std::vector<datatypes::ValueTypePair> vector;// = std::vector<datatypes::ValueTypePair>();
    if (ret == 0) {
        datatypes::ValueTypePair pair(new int(atoi(context->value)), datatypes::ValType::INT);

        vector.push_back(pair);
    }
    datatypes::AttributeValuePair attributeValuePair(attr_names, datatypes::Value(vector));

    datatypes::ReturnType returnType(device, attributeValuePair, "", ConvertErrorCode(ret), "");

    ugw_free_context(context);

    return returnType;
}