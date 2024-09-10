bool BDTools::update(QString table, QList<QString> fields, QList<QString> values, QString fieldCondition, QString valueCondition){
    QString sql = "update " + table + " set ";

    for (int i = 0; i < fields.length(); i++){

        if (values[i].isEmpty())
            sql += fields[i] + " = null, ";
        else{
            values[i].replace("'", "''");

            sql += fields[i] + " = '" + values[i] + "', ";
        }
    }

    sql = sql.mid(0, sql.length() - 2);

    sql += " where " + fieldCondition + " = '" + valueCondition + "'";

    bool b = exec(sql);
    if (! b)
        qDebug() << "[BDTools] [UPDATE] Erro na SQL: " << sql;

    return b;
}