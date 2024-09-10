void QQmlTypePrivate::init() const
{
    if (m_isSetup) return;

    QWriteLocker lock(metaTypeDataLock());
    if (m_isSetup)
        return;

    const QMetaObject *mo = m_baseMetaObject;
    if (!mo) {
        // singleton type without metaobject information
        return;
    }

    // Setup extended meta object
    // XXX - very inefficient
    if (m_extFunc) {
        QMetaObjectBuilder builder;
        clone(builder, m_extMetaObject, m_extMetaObject, m_extMetaObject);
        builder.setFlags(QMetaObjectBuilder::DynamicMetaObject);
        QMetaObject *mmo = builder.toMetaObject();
        mmo->d.superdata = mo;
        QQmlProxyMetaObject::ProxyData data = { mmo, m_extFunc, 0, 0 };
        m_metaObjects << data;
    }

    mo = mo->d.superdata;
    while(mo) {
        QQmlType *t = metaTypeData()->metaObjectToType.value(mo);
        if (t) {
            if (t->d->m_extFunc) {
                QMetaObjectBuilder builder;
                clone(builder, t->d->m_extMetaObject, t->d->m_baseMetaObject, m_baseMetaObject);
                builder.setFlags(QMetaObjectBuilder::DynamicMetaObject);
                QMetaObject *mmo = builder.toMetaObject();
                mmo->d.superdata = m_baseMetaObject;
                if (!m_metaObjects.isEmpty())
                    m_metaObjects.last().metaObject->d.superdata = mmo;
                QQmlProxyMetaObject::ProxyData data = { mmo, t->d->m_extFunc, 0, 0 };
                m_metaObjects << data;
            }
        }
        mo = mo->d.superdata;
    }

    for (int ii = 0; ii < m_metaObjects.count(); ++ii) {
        m_metaObjects[ii].propertyOffset =
            m_metaObjects.at(ii).metaObject->propertyOffset();
        m_metaObjects[ii].methodOffset =
            m_metaObjects.at(ii).metaObject->methodOffset();
    }
    
    // Check for revisioned details
    {
        const QMetaObject *mo = 0;
        if (m_metaObjects.isEmpty())
            mo = m_baseMetaObject;
        else
            mo = m_metaObjects.first().metaObject;

        for (int ii = 0; !m_containsRevisionedAttributes && ii < mo->propertyCount(); ++ii) {
            if (isPropertyRevisioned(mo, ii))
                m_containsRevisionedAttributes = true;
        }

        for (int ii = 0; !m_containsRevisionedAttributes && ii < mo->methodCount(); ++ii) {
            if (mo->method(ii).revision() != 0)
                m_containsRevisionedAttributes = true;
        }
    }

    m_isSetup = true;
    lock.unlock();
}