void StyledElement::addCSSLength(MappedAttribute* attr, int id, const String &value)
{
    // FIXME: This function should not spin up the CSS parser, but should instead just figure out the correct
    // length unit and make the appropriate parsed value.
    if (!attr->decl())
        createMappedDecl(attr);

    // strip attribute garbage..
    StringImpl* v = value.impl();
    if (v) {
        unsigned int l = 0;
        
        while (l < v->length() && (*v)[l] <= ' ')
            l++;
        
        for (; l < v->length(); l++) {
            UChar cc = (*v)[l];
            if (cc > '9')
                break;
            if (cc < '0') {
                if (cc == '%' || cc == '*')
                    l++;
                if (cc != '.')
                    break;
            }
        }

        if (l != v->length()) {
            attr->decl()->setLengthProperty(id, v->substring(0, l), false);
            return;
        }
    }
    
    attr->decl()->setLengthProperty(id, value, false);
}