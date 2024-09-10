QList<QVariantMap > HsMenuClientPrivate::getList(const QVariantMap &queryPreference)
{
    QList<QVariantMap> list;
    QMap<QString, QVariant> map = queryPreference;
    
    map.remove(hsItemName);
    map.remove(hsItemDescription);
    
    CaQuery query;
    // define query
    query.setFlagsOn(VisibleEntryFlag);
    query.setEntryRoles(ItemEntryRole);
    query.setEntryTypeNames(QStringList(Hs::templatedApplicationTypeName));
    
    
    // add atributes to caquery
    QMapIterator<QString, QVariant> k(map);
    while (k.hasNext()) {
        k.next();
        query.setAttribute(k.key(),k.value().toString());
    }  
    QList< QSharedPointer<CaEntry> > entries = CaService::instance()->getEntries(query);
    map.clear();
    if (entries.count()) {
        QMap<QString, QString> attrMap;
        QMapIterator<QString, QString> k(attrMap);
        //walk trought entrys and extract keys into map
        for (int i = 0; i < entries.count(); ++i) {
            map[hsItemId] = entries.at(i)->id();
            map[hsItemName] = entries.at(i)->text();
            map[hsItemDescription] = entries.at(i)->description();
            CaIconDescription iconDesc = entries.at(i)->iconDescription();
            map[hsIconFileName] = iconDesc.filename();
            map[hsIconName] = iconDesc.skinId();
            map[hsIconApplicationId] = iconDesc.applicationId();
            
            // extract entry atributes
            attrMap = entries.at(i)->attributes();
            QMapIterator<QString, QString> k(attrMap);
            // insert entrys attr into map
            while (k.hasNext()) {
                k.next();
                map.insert(k.key(),k.value());
            }
            list.append(map); //append entry map to list
            // clean used maps
            map.clear();
            attrMap.clear();
        }
    }
    return list;
}