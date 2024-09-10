QSqlRelationalTableModel * AddStoragePlace::getBoxModel(QString tableName) {
    QSqlRelationalTableModel *m = new QSqlRelationalTableModel();
    m->setTable(tableName);
    m->select();
    return m;
}