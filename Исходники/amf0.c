/* dump AMF data into a stream as text */
void amf0_data_dump(FILE * stream, const amf0_data *data, int indent_level) {
    if (data != NULL) {
        amf0_node * node;
        time_t time;
        struct tm * t;
        char datestr[128];
        switch (data->type) {
            case AMF0_TYPE_NUMBER:
                fprintf(stream, "%.12g", data->number_data);
                break;
            case AMF0_TYPE_BOOLEAN:
                fprintf(stream, "%s", (data->boolean_data) ? "true" : "false");
                break;
            case AMF0_TYPE_STRING:
                fprintf(stream, "\'%.*s\'", data->string_data.size, data->string_data.mbstr);
                break;
            case AMF0_TYPE_OBJECT:
                node = amf0_object_first(data);
                fprintf(stream, "{\n");
                while (node != NULL) {
                    fprintf(stream, "%*s", (indent_level+1)*4, "");
                    amf0_data_dump(stream, amf0_object_get_name(node), indent_level+1);
                    fprintf(stream, ": ");
                    amf0_data_dump(stream, amf0_object_get_data(node), indent_level+1);
                    node = amf0_object_next(node);
                    fprintf(stream, "\n");
                }
                fprintf(stream, "%*s", indent_level*4 + 1, "}");
                break;
            case AMF0_TYPE_MOVIECLIP:
                fprintf(stream, "[movieclip]");
                break;
            case AMF0_TYPE_NULL:
                fprintf(stream, "null");
                break;
            case AMF0_TYPE_UNDEFINED:
                fprintf(stream, "undefined");
                break;
            case AMF0_TYPE_REFERENCE: /* TODO */
                fprintf(stream, "[reference]");
                break;
            case AMF0_TYPE_ECMA_ARRAY:
                node = amf0_associative_array_first(data);
                fprintf(stream, "{\n");
                while (node != NULL) {
                    fprintf(stream, "%*s", (indent_level+1)*4, "");
                    amf0_data_dump(stream, amf0_associative_array_get_name(node), indent_level+1);
                    fprintf(stream, " => ");
                    amf0_data_dump(stream, amf0_associative_array_get_data(node), indent_level+1);
                    node = amf0_associative_array_next(node);
                    fprintf(stream, "\n");
                }
                fprintf(stream, "%*s", indent_level*4 + 1, "}");
                break;
            case AMF0_TYPE_OBJECT_END:
                fprintf(stream, "[object end]");
                break;
            case AMF0_TYPE_STRICT_ARRAY:
                node = amf0_array_first(data);
                fprintf(stream, "[\n");
                while (node != NULL) {
                    fprintf(stream, "%*s", (indent_level+1)*4, "");
                    amf0_data_dump(stream, node->data, indent_level+1);
                    node = amf0_array_next(node);
                    fprintf(stream, "\n");
                }
                fprintf(stream, "%*s", indent_level*4 + 1, "]");
                break;
            case AMF0_TYPE_DATE:
                time = amf0_date_to_time_t(data);
                tzset();
                t = localtime(&time);
                strftime(datestr, sizeof(datestr), "%a, %d %b %Y %H:%M:%S %z", t);
                fprintf(stream, "%s", datestr);
                break;
            case AMF0_TYPE_LONG_STRING: /* TODO */
                fprintf(stream, "[long string]");
                break;
            case AMF0_TYPE_UNSUPPORTED:
                fprintf(stream, "[unsupported]");
                break;
            case AMF0_TYPE_RECORDSET:
                fprintf(stream, "[recordset]");
                break;
            case AMF0_TYPE_XML_DOCUMENT: /* TODO */
                fprintf(stream, "[xml document]");
                break;
            case AMF0_TYPE_TYPED_OBJECT: /* TODO */
                fprintf(stream, "[typed object]");
                break;
            default:
                fprintf(stream, "[unknown data type 0x%x]", data->type);
                break;
        }
    }
}