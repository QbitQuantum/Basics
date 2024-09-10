const IMATH_NAMESPACE::M44f&
DeepTransform::imatrix()
{
    if (!m_updated)
    {
        g_lock.lock();
        if (!m_updated)
        {
            m_imatrix = m_matrix.inverse();
            m_updated = true;
        }
        g_lock.unlock();
    }
    return m_imatrix;
}