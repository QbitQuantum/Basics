bool CSSStyleSheetImpl::parseString(const DOMString &string, bool strict)
{
#ifdef CSS_STYLESHEET_DEBUG
    qDebug() << "parsing sheet, len=" << string.length() << ", sheet is " << string.string();
#endif

    strictParsing = strict;
    CSSParser p(strict);
    p.parseSheet(this, string);
    return true;
}