QList<T *> DataMapper<Subclass, T, I>::find(const QString & whereClause)
{
    return basicFind(SELECT("*").FROM(table()).WHERE(whereClause));
}