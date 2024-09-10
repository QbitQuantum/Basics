QVariant CompositeValuePropertyItem::data(qint32 column, qint32 role) const
{
    if (role == Qt::DisplayRole)
        return toUnicode(m_property.name);
    else
        return QVariant();
}