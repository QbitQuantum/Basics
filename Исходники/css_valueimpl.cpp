void CSSStyleDeclarationImpl::setLengthProperty(int id, const DOMString &value,
						bool important, bool nonCSSHint)
{
    strictParsing = false;
    setProperty( id, value, important, nonCSSHint);
    strictParsing = true;
#if 0 // ### FIXME after 2.0
    if(!value.unicode() || value.length() == 0)
	return;

    if(!m_lstValues)
    {
	m_lstValues = new QList<CSSProperty>;
	m_lstValues->setAutoDelete(true);
    }

    CSSValueImpl *v = parseUnit(value.unicode(), value.unicode()+value.length(),
				INTEGER | PERCENT | LENGTH, );
    if(!v)
    {
	kdDebug( 6080 ) << "invalid length" << endl;
	return;
    }

    CSSPrimitiveValueImpl *p = static_cast<CSSPrimitiveValueImpl *>(v);
    if(p->primitiveType() == CSSPrimitiveValue::CSS_NUMBER)
    {
	// set the parsed number in pixels
	p->setPrimitiveType(CSSPrimitiveValue::CSS_PX);
    }
    CSSProperty *prop = new CSSProperty();
    prop->m_id = id;
    prop->setValue(v);
    prop->m_bImportant = important;
    prop->nonCSSHint = nonCSSHint;

    m_lstValues->append(prop);
#endif
}