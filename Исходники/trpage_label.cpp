bool trpgLabelPropertyTable::Read(trpgReadBuffer &buf)
{
    trpgLabelProperty property;
    trpgToken propertyTok;
    int32 len;
    bool status;
    int numProperty;
    int i;

    Reset();

    try
    {
        buf.Get(numProperty);
        if (numProperty < 0)
            throw 1;
        //properties.resize(numProperty);
        for (i=0;i<numProperty;i++) {
            buf.GetToken(propertyTok,len);
            if (propertyTok != TRPG_LABEL_PROPERTY) throw 1;
            buf.PushLimit(len);
            property.Reset();
            status = property.Read(buf);
            buf.PopLimit();
            if (!status) throw 1;
            //properties[i] = property;
            AddProperty(property);
        }
    }
    catch (...)
    {
        return false;
    }

    return isValid();
}