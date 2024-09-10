String::String(const QStringRef& ref)
{
    if (!ref.string())
        return;
    m_impl = StringImpl::create(reinterpret_cast_ptr<const UChar*>(ref.unicode()), ref.length());
}