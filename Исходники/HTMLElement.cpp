void HTMLElement::addHTMLLengthToStyle(MutableStylePropertySet* style, CSSPropertyID propertyID, const String& value)
{
    // FIXME: This function should not spin up the CSS parser, but should instead just figure out the correct
    // length unit and make the appropriate parsed value.

    // strip attribute garbage..
    StringImpl* v = value.impl();
    if (v) {
        unsigned length = 0;

        while (length < v->length() && (*v)[length] <= ' ')
            length++;

        for (; length < v->length(); length++) {
            UChar cc = (*v)[length];
            if (cc > '9')
                break;
            if (cc < '0') {
                if (cc == '%' || cc == '*')
                    length++;
                if (cc != '.')
                    break;
            }
        }

        if (length != v->length()) {
            addPropertyToPresentationAttributeStyle(style, propertyID, v->substring(0, length));
            return;
        }
    }

    addPropertyToPresentationAttributeStyle(style, propertyID, value);
}