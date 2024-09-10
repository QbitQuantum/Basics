QList<T> sorted(const QList<T> &list)
{
    QList<T> res = list;
    qSort(res);
    return res;
}