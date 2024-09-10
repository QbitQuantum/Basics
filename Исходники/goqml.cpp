void objectSetParent(QObject_ *object, QObject_ *parent)
{
    QObject *qobject = reinterpret_cast<QObject *>(object);
    QObject *qparent = reinterpret_cast<QObject *>(parent);

    qobject->setParent(qparent);
}