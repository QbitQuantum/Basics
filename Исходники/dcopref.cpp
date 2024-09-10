bool DCOPRef::sendInternal(const QCString &fun, const QCString &args, const QByteArray &data)
{
    if(isNull())
    {
        qWarning("DCOPRef: send '%s' on null reference error", STR(fun));
        return false;
    }
    Q_UNUSED(data);
    QCString sig = fun;
    if(fun.find('(') == -1)
    {
        sig += args;
        if(args.find("<unknown") != -1)
            qWarning(
                "DCOPRef: unknown type error "
                "<\"%s\",\"%s\">::send(\"%s\",%s",
                STR(m_app), STR(m_obj), STR(fun), args.data() + 1);
    }
    DCOPClient *dc = dcopClient();
    if(!dc || !dc->isAttached())
    {
        qWarning("DCOPRef::send(): no DCOP client or client not attached error");
        return false;
    }
    return dc->send(m_app, m_obj, sig, data);
}