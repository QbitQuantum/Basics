static void bindParameters(const QVariantList& bindValues, QSqlQuery *sqlQuery) {
    if (!bindValues.isEmpty()) {
        for (int i = bindValues.length() - 1; i >= 0; --i) {
            sqlQuery->bindValue(i, bindValues.at(i));
        }
    }
}