bool unset(const QStringList & keys, QVariantMap & context){
    if(keys.size() == 1){
        return context.remove(keys.first()) > 0;
    }
    QVariant v = value_unsafe(keys.mid(0, keys.size() - 1), context);
    if(v.isNull())
        return false;
    if(v.type() == QVariant::Map) {
        QVariantMap & map = asMap(v);
        return map.remove(keys.last()) != 0;
    }
    if(v.type() == QVariant::List) {
        QVariantList & lst = asList(v);
        bool ok;
        int idx = keys.last().toInt(&ok);
        if(!ok || idx >= lst.size())
            return false;
        lst.removeAt(idx);
        return true;

    }
    return false;
}