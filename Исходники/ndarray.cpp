NDArray::NDArray(const QVariantList &values)
    : NDArray(TypeMap<qreal>::type, {values.length()}, 0)
{
    qreal* dptr = (qreal*)data();
    // Copy in data from list
    for (int i=0; i<m_size; ++i) {
//        qDebug() << QString("%1: %2").arg(i).arg(values[i].toReal());
        (*dptr++) = values[i].toReal();
    }
}