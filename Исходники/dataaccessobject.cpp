QSharedPointer<QObject> QpDaoBase::readObject(int id) const
{
    QSharedPointer<QObject> p = d->cache.get(id);

    if(p)
        return p;

    QObject *object = createInstance();

    if(!d->sqlDataAccessObjectHelper->readObject(d->metaObject, id, object)) {
        setLastError(d->sqlDataAccessObjectHelper->lastError());
        delete object;
        return QSharedPointer<QObject>();
    }
    QSharedPointer<QObject> obj = d->cache.insert(Qp::Private::primaryKey(object), object);
    Qp::Private::enableSharedFromThis(obj);

    return obj;
}