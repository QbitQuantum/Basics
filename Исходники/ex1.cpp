void print_xmltree(xmlNodePtr xroot, int level)
{
    print_indent(level);

    printf("%s ", xroot->name);
    if (xroot->properties)
    {
        printf("[");
        for (xmlAttrPtr a = xroot->properties; a != 0; a = a->next)
        {
            printf("%s=%s", a->name, xmlNodeGetContent(a->children));  // or one can write xmlGetProp(xroot, a->name)
            if (a->next) printf(", ");
        }
        printf("]");
    }

    if (xroot->children && xroot->children->next == 0 && xroot->children->type == XML_TEXT_NODE)
    {
        xmlChar *sz = xmlNodeGetContent(xroot->children);
        printf("{%s}", sz);
        xmlFree(sz);
    }
    printf("\n");

    for (xmlNodePtr c = xroot->children; c != 0; c = c->next)
    {
        if (c->type == XML_ELEMENT_NODE)
            print_xmltree(c, level + 1);
    }
}