string JsonReader::_readString(const string& name) {
    auto val = json_object_get(getCurrentObject(), name.c_str());
    if (!json_is_string(val))
        throwBadType(name, "string");
    return json_string_value(val);
}