void CSSStyleDeclaration::setProperty( const DOMString &propName, const DOMString &value, const DOMString &priority )
{
    if(!impl) return;
    int id = getPropertyID(propName.string().lower().ascii(), propName.length());
    if (!id) return;
    bool important = false;
    QString str = priority.string();
    if (str.find("important", 0, false) != -1)
        important = true;

    static_cast<CSSStyleDeclarationImpl *>(impl)->setProperty( id, value, important );
}