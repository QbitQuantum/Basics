void QQuickCanvasItem::setContextType(const QString &contextType)
{
    Q_D(QQuickCanvasItem);

    if (contextType.compare(d->contextType, Qt::CaseInsensitive) == 0)
        return;

    if (d->context) {
        qmlInfo(this) << "Canvas already initialized with a different context type";
        return;
    }

    d->contextType = contextType;

    if (d->available)
        createContext(contextType);

    emit contextTypeChanged();
}