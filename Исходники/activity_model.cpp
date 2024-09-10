bool Activity::updateActivity(QString activityID, QMap<QString, QString> valuesToChange) {
    // Lookup the course to change just by the key since it can't change
    QMap<QString, QString> tmp;
    tmp.insert(getKey(), activityID);

    // Auto incremented, so why would this need to change
    valuesToChange.remove(getKey());

    return updateDBItem(tmp, valuesToChange);
}