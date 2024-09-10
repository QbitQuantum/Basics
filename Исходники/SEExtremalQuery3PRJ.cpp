//----------------------------------------------------------------------------
void SEExtremalQuery3PRJf::GetExtremeVertices(const SEVector3f& rDirection, 
    int& riPositiveDirection, int& riNegativeDirection)
{
    SEVector3f vec3fDiff = m_pPolytope->GetVertex(0) - m_Centroid;
    float fMin = rDirection.Dot(vec3fDiff), fMax = fMin;
    riNegativeDirection = 0;
    riPositiveDirection = 0;

    for( int i = 1; i < m_pPolytope->GetVCount(); i++ )
    {
        vec3fDiff = m_pPolytope->GetVertex(i) - m_Centroid;
        float fDot = rDirection.Dot(vec3fDiff);
        if( fDot < fMin )
        {
            riNegativeDirection = i;
            fMin = fDot;
        }
        else if( fDot > fMax )
        {
            riPositiveDirection = i;
            fMax = fDot;
        }
    }
}