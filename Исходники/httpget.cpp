/** @brief enable / disable cache useage
 *  @param c set cache usage
 */
void HttpGet::setCache(bool c)
{
    m_usecache = c;
    // make sure cache is initialized
    if(c)
        m_usecache = initializeCache(m_cachedir);
}