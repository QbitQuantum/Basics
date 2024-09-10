static void node_to_xml(node_t* node, void *xml_struct)
{
    struct xml_node *xstruct = NULL;
    plist_data_t node_data = NULL;

    xmlNodePtr child_node = NULL;
    char isStruct = FALSE;
    char isUIDNode = FALSE;

    const xmlChar *tag = NULL;
    char *val = NULL;

    //for base64
    char *valtmp = NULL;

    uint32_t i = 0;

    if (!node)
        return;

    xstruct = (struct xml_node *) xml_struct;
    node_data = plist_get_data(node);

    switch (node_data->type)
    {
    case PLIST_BOOLEAN:
    {
        if (node_data->boolval)
            tag = XPLIST_TRUE;
        else
            tag = XPLIST_FALSE;
    }
    break;
	
    case PLIST_UINT:
        tag = XPLIST_INT;
        val = (char*)malloc(64);
        (void)_snprintf(val, 64, "%llu", node_data->intval);
        break;

    case PLIST_REAL:
        tag = XPLIST_REAL;
        val = (char*)malloc(64);
        (void)_snprintf(val, 64, "%f", node_data->realval);
        break;

    case PLIST_STRING:
        tag = XPLIST_STRING;
        val = strdup(node_data->strval);
        break;

    case PLIST_KEY:
        tag = XPLIST_KEY;
        val = strdup((char*) node_data->strval);
        break;

    case PLIST_DATA:
        tag = XPLIST_DATA;
        if (node_data->length)
        {
            size_t len = node_data->length;
            valtmp = base64encode(node_data->buff, &len);
            val = format_string(valtmp, len, 68, xstruct->depth);
            free(valtmp);
        }
        break;
    case PLIST_ARRAY:
        tag = XPLIST_ARRAY;
        isStruct = TRUE;
        break;
    case PLIST_DICT:
        tag = XPLIST_DICT;
        isStruct = TRUE;
        break;
    case PLIST_DATE:
        tag = XPLIST_DATE;
        {
            time_t time = (time_t)node_data->timeval.tv_sec;
            struct tm *btime = localtime(&time);
            if (btime) {
                val = (char*)malloc(24);
                memset(val, 0, 24);
                if (strftime(val, 24, "%Y-%m-%dT%H:%M:%SZ", btime) <= 0) {
                    free (val);
                    val = NULL;
                }
            }
        }
        break;
    case PLIST_UID:
        // special case for keyed encoding
        tag = XPLIST_DICT;
        isStruct = TRUE;
        isUIDNode = TRUE;
        node_data->type = PLIST_DICT;
        node_attach(node, new_key_node("CF$UID"));
        node_attach(node, new_uint_node(node_data->intval));
        break;
    default:
        break;
    }

    for (i = 0; i < xstruct->depth; i++)
    {
        xmlNodeAddContent(xstruct->xml, BAD_CAST("\t"));
    }
    if (node_data->type == PLIST_STRING) {
        /* make sure we convert the following predefined xml entities */
        /* < = &lt; > = &gt; ' = &apos; " = &quot; & = &amp; */
        child_node = xmlNewTextChild(xstruct->xml, NULL, tag, BAD_CAST(val));
    } else
        child_node = xmlNewChild(xstruct->xml, NULL, tag, BAD_CAST(val));
    xmlNodeAddContent(xstruct->xml, BAD_CAST("\n"));
    if (val) {
        free(val);
    }

    //add return for structured types
    if (node_data->type == PLIST_ARRAY || node_data->type == PLIST_DICT)
        xmlNodeAddContent(child_node, BAD_CAST("\n"));

    if (isStruct)
    {
        struct xml_node child = { child_node, xstruct->depth + 1 };
        node_iterator_t *ni = node_iterator_create(node->children);
        node_t *ch;
        while ((ch = node_iterator_next(ni))) {
            node_to_xml(ch, &child);
        }
        node_iterator_destroy(ni);
    }
    //fix indent for structured types
    if (node_data->type == PLIST_ARRAY || node_data->type == PLIST_DICT)
    {

        for (i = 0; i < xstruct->depth; i++)
        {
            xmlNodeAddContent(child_node, BAD_CAST("\t"));
        }
    }
    if (isUIDNode)
    {
        unsigned int num = node_n_children(node);
        unsigned int i;
        for (i = num; i > 0; i--) {
            node_t* ch = node_nth_child(node, i-1);
            node_detach(node, ch);
            node_destroy(ch);
        }
        node_data->type = PLIST_UID;
    }

    return;
}