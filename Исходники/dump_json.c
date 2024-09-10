/* JSON metadata dumping */
static void amf_to_json(const amf_data * data, json_t ** object) {
    if (data != NULL) {
        json_t * value;
        amf_node * node;
        time_t time;
        struct tm * t;
        char str[128];
        char * escaped_str;

        switch (data->type) {
            case AMF_TYPE_NUMBER:
                sprintf(str, "%.12g", data->number_data);
                *object = json_new_number(str);
                break;
            case AMF_TYPE_BOOLEAN:
                *object = (data->boolean_data) ? json_new_true() : json_new_false();
                break;
            case AMF_TYPE_STRING:
                escaped_str = json_escape((char *)amf_string_get_bytes(data));
                *object = json_new_string(escaped_str);
                free(escaped_str);
                break;
            case AMF_TYPE_OBJECT:
                *object = json_new_object();
                node = amf_object_first(data);
                while (node != NULL) {
                    amf_to_json(amf_object_get_data(node), &value);
                    escaped_str = json_escape((char *)amf_string_get_bytes(amf_object_get_name(node)));
                    json_insert_pair_into_object(*object, escaped_str, value);
                    free(escaped_str);
                    node = amf_object_next(node);
                }
                break;
            case AMF_TYPE_NULL:
            case AMF_TYPE_UNDEFINED:
                *object = json_new_null();
                break;
            case AMF_TYPE_ASSOCIATIVE_ARRAY:
                *object = json_new_object();
                node = amf_associative_array_first(data);
                while (node != NULL) {
                    amf_to_json(amf_associative_array_get_data(node), &value);
                    json_insert_pair_into_object(*object, (const char *)amf_string_get_bytes(amf_associative_array_get_name(node)), value);
                    node = amf_associative_array_next(node);
                }
                break;
            case AMF_TYPE_ARRAY:
                *object = json_new_array();
                node = amf_array_first(data);
                while (node != NULL) {
                    amf_to_json(amf_array_get(node), &value);
                    json_insert_child(*object, value);
                    node = amf_array_next(node);
                }
                break;
            case AMF_TYPE_DATE:
                time = amf_date_to_time_t(data);
                tzset();
                t = localtime(&time);
                strftime(str, sizeof(str), "%Y-%m-%dT%H:%M:%S", t);
                *object = json_new_string(str);
                break;
            case AMF_TYPE_XML: break;
            case AMF_TYPE_CLASS: break;
            default: break;
        }
    }
}