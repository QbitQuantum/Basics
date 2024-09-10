void QSpotifySearch::clearSearch(sp_search *search)
{
    QMutexLocker lock(&g_mutex);
    if (search)
        sp_search_release(search);
    g_searchObjects.remove(search);
    if (search == m_sp_search)
        m_sp_search = nullptr;
}