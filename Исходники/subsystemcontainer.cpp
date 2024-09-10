void SubsystemContainer::captureListSet(QHash<QString,QVariant>* subsystemElement, QString key){
    for(QVariant el : subsystemElement->value(key).toList()){
        QMap<QString,QVariant> set = el.toMap();
        QString setKey = set.value("id").toString();
        set.remove("id");
        m_sets.insert(setKey,set);
    }
}