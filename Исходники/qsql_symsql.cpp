QVariant QSymSQLResult::data(int idx)
{
    QVariant r;
    
    switch (d->stmt.ColumnType(idx)) {
    case ESqlBinary:
        {
            TPtrC8 data; 
            d->stmt.ColumnBinary(idx, data);
            return QByteArray(reinterpret_cast<const char *>(data.Ptr()), data.Length());
            break;
         }
    case ESqlInt:
        r = QVariant(d->stmt.ColumnInt(idx));
        break;
    case ESqlInt64:
        r = QVariant(d->stmt.ColumnInt64(idx));
        break;
    case ESqlReal:
        switch(numericalPrecisionPolicy()) {
        case QSql::LowPrecisionInt32:
            r = QVariant(d->stmt.ColumnInt(idx));
            break;
        case QSql::LowPrecisionInt64:
            r = QVariant(d->stmt.ColumnInt64(idx));
            break;
        case QSql::LowPrecisionDouble:
            r = QVariant(d->stmt.ColumnReal(idx));
            break;
        case QSql::HighPrecision:
        default:
            TPtrC res;
            d->stmt.ColumnText(idx, res);
            r = QVariant(qt_TDesC2QString(res));
            break;
        };
        break;
    case ESqlNull:
        r  = QVariant(QVariant::String);
        break;
    default:
        TPtrC res;
        d->stmt.ColumnText(idx, res);
        r = QVariant(qt_TDesC2QString(res));
        break;
    }

    return r;
}    