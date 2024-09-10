void HTMLPreElement::setWidth( long _width )
{
    if(!impl) return;

    TQString aStr;
    aStr.sprintf("%ld", _width);
    DOMString value(aStr);
    ((ElementImpl *)impl)->setAttribute(ATTR_WIDTH, value);
}