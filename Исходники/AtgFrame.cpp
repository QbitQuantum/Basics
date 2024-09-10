//-----------------------------------------------------------------------------
// Name: Frame::UpdateCachedWorldTransformIfNeeded()
//-----------------------------------------------------------------------------
VOID Frame::UpdateCachedWorldTransformIfNeeded()
{
    if( IsCachedWorldTransformDirty() )
    {
        if( m_pParent )
        {
            m_pParent->UpdateCachedWorldTransformIfNeeded();
            m_CachedWorldTransform = XMMatrixMultiply( m_LocalTransform, m_pParent->m_CachedWorldTransform );
            m_CachedWorldBound = m_LocalBound * m_CachedWorldTransform;
        }
        else
        {
            m_CachedWorldTransform = m_LocalTransform;
            m_CachedWorldBound = m_LocalBound * m_CachedWorldTransform;
        }
    }
}