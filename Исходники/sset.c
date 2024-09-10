void Q_SSetReverseSort(sset_t *ss, qboolean caseSensitive) {
    int (*func)(void *, const void *, const void *) = caseSensitive ? revtokcmp : revtokcasecmp;
#ifdef WIN32
    qsort_s(&ss->tokens[0], ss->currentSize, sizeof(int32_t), func, (void *)&ss->table);
#else
    qsort_r(&ss->tokens[0], ss->currentSize, sizeof(int32_t), (void *)&ss->table, func);
#endif
}