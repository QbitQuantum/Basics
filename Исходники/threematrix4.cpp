QJSValue THREEMatrix4::applyVector3Array(QJSValue floatArray, int offset, int length)
{
    if(!floatArray.isArray()) {
        qDebug().nospace() << "THREEMatrix4::" << __FUNCTION__
                           << " invalid parameter type for floatArray, expected JS array";
        return m_engine->newQObject(this);
    }

    static THREEVector3 v1(parent(), m_engine);
    QVariantList list = floatArray.toVariant().toList();

    if (offset < 0)
        offset = 0;

    if (length < 0 || length == 0)
        length = list.length();

    if (offset + length > list.length())
        length = list.length() - offset;

    for ( int i = 0, j = offset; i < length; i += 3, j += 3 ) {
        v1.m_x = float(floatArray.property(j).toNumber());
        v1.m_y = float(floatArray.property(j + 1).toNumber());
        v1.m_z = float(floatArray.property(j + 2).toNumber());

        v1._applyMatrix4( this );

        floatArray.setProperty(j, QJSValue(v1.m_x));
        floatArray.setProperty(j + 1, QJSValue(v1.m_y));
        floatArray.setProperty(j + 2, QJSValue(v1.m_z));
    }

    return floatArray;
}