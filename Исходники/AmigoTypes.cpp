Field SchemaHelper::parseField(const rapidjson::Value &data, int index)
{
    Field field = std::make_shared<SchemaField>();
    field->index = index;
    field->name = getJSONString(data, "name");
    field->type = getJSONString(data, "type");
    field->geometry_type = getJSONString(data, "geometry_type");
    field->nullable = getJSONBool(data, "nullable");
    field->related_to = getJSONLong(data, "related_to", -1);
    field->max_length = getJSONInt(data, "max_length", -1);
    field->default_value = getJSONString(data, "default");

    StringBuffer buffer;
    PrettyWriter<StringBuffer> writer(buffer);
    data.Accept(writer);
    field->json = buffer.GetString();

    if(field->name == "amigo_id")
    {
        field->unique = true;
    }
    return field;
}