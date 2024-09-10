static RectF RectFUnion(RectF& r1, RectF& r2) {
    if (r2.IsEmptyArea())
        return r1;
    if (r1.IsEmptyArea())
        return r2;
    RectF ru;
    ru.Union(ru, r1, r2);
    return ru;
}