static QSqlField qToField(MYSQL_FIELD *field, QTextCodec *tc)
{
    QSqlField f(toUnicode(tc, field->name),
                qDecodeMYSQLType(int(field->type), field->flags));
    f.setRequired(IS_NOT_NULL(field->flags));
    f.setLength(field->length);
    f.setPrecision(field->decimals);
    f.setSqlType(field->type);
    f.setAutoValue(field->flags & AUTO_INCREMENT_FLAG);
    return f;
}