/* XML metadata dumping */
static void xml_amf_data_dump(const amf_data * data, int qualified, int indent_level) {
    if (data != NULL) {
        amf_node * node;
        time_t time;
        struct tm * t;
        char datestr[128];
        int markers;
        char * ns;
        char ns_decl[50];

        /* namespace to use whether we're using qualified mode */
        ns = (qualified == 1) ? "amf:" : "";

        /* if indent_level is zero, that means we're at the root of the xml document
           therefore we need to insert the namespace definition */
        if (indent_level == 0) {
            sprintf(ns_decl, " xmlns%s=\"http://schemas.flvmeta.org/AMF0/1.0/\"", ns);
        }
        else {
            strcpy(ns_decl, "");
        }

        /* print indentation spaces */
        printf("%*s", indent_level * 2, "");

        switch (data->type) {
            case AMF_TYPE_NUMBER:
                printf("<%snumber%s value=\"%.12g\"/>\n", ns, ns_decl, data->number_data);
                break;
            case AMF_TYPE_BOOLEAN:
                printf("<%sboolean%s value=\"%s\"/>\n", ns, ns_decl, (data->boolean_data) ? "true" : "false");
                break;
            case AMF_TYPE_STRING:
                if (amf_string_get_size(data) > 0) {
                    printf("<%sstring%s>", ns, ns_decl);
                    /* check whether the string contains xml characters, if so, CDATA it */
                    markers = has_xml_markers((char*)amf_string_get_bytes(data), amf_string_get_size(data));
                    if (markers) {
                        printf("<![CDATA[");
                    }
                    /* do not print more than the actual length of string */
                    printf("%.*s", (int)amf_string_get_size(data), amf_string_get_bytes(data));
                    if (markers) {
                        printf("]]>");
                    }
                    printf("</%sstring>\n", ns);
                }
                else {
                    /* simplify empty xml element into a more compact form */
                    printf("<%sstring%s/>\n", ns, ns_decl);
                }
                break;
            case AMF_TYPE_OBJECT:
                if (amf_object_size(data) > 0) {
                    printf("<%sobject%s>\n", ns, ns_decl);
                    node = amf_object_first(data);
                    while (node != NULL) {
                        printf("%*s<%sentry name=\"%s\">\n", (indent_level + 1) * 2, "", ns, amf_string_get_bytes(amf_object_get_name(node)));
                        xml_amf_data_dump(amf_object_get_data(node), qualified, indent_level + 2);
                        node = amf_object_next(node);
                        printf("%*s</%sentry>\n", (indent_level + 1) * 2, "", ns);
                    }
                    printf("%*s</%sobject>\n", indent_level * 2, "", ns);
                }
                else {
                    /* simplify empty xml element into a more compact form */
                    printf("<%sobject%s/>\n", ns, ns_decl);
                }
                break;
            case AMF_TYPE_NULL:
                printf("<%snull%s/>\n", ns, ns_decl);
                break;
            case AMF_TYPE_UNDEFINED:
                printf("<%sundefined%s/>\n", ns, ns_decl);
                break;
            case AMF_TYPE_ASSOCIATIVE_ARRAY:
                if (amf_associative_array_size(data) > 0) {
                    printf("<%sassociativeArray%s>\n", ns, ns_decl);
                    node = amf_associative_array_first(data);
                    while (node != NULL) {
                        printf("%*s<%sentry name=\"%s\">\n", (indent_level + 1) * 2, "", ns, amf_string_get_bytes(amf_associative_array_get_name(node)));
                        xml_amf_data_dump(amf_associative_array_get_data(node), qualified, indent_level + 2);
                        node = amf_associative_array_next(node);
                        printf("%*s</%sentry>\n", (indent_level + 1) * 2, "", ns);
                    }
                    printf("%*s</%sassociativeArray>\n", indent_level * 2, "", ns);
                }
                else {
                    /* simplify empty xml element into a more compact form */
                    printf("<%sassociativeArray%s/>\n", ns, ns_decl);
                }
                break;
            case AMF_TYPE_ARRAY:
                if (amf_array_size(data) > 0) {
                    printf("<%sarray%s>\n", ns, ns_decl);
                    node = amf_array_first(data);
                    while (node != NULL) {
                        xml_amf_data_dump(amf_array_get(node), qualified, indent_level + 1);
                        node = amf_array_next(node);
                    }
                    printf("%*s</%sarray>\n", indent_level * 2, "", ns);
                }
                else {
                    /* simplify empty xml element into a more compact form */
                    printf("<%sarray%s/>\n", ns, ns_decl);
                }
                break;
            case AMF_TYPE_DATE:
                time = amf_date_to_time_t(data);
                tzset();
                t = localtime(&time);
                strftime(datestr, sizeof(datestr), "%Y-%m-%dT%H:%M:%S", t);
                printf("<%sdate%s value=\"%s\"/>\n", ns, ns_decl, datestr);
                break;
            case AMF_TYPE_XML: break;
            case AMF_TYPE_CLASS: break;
            default: break;
        }
    }
}