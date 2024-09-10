void
Moose::Math::CPlane::Calculate( CVector3<float> vNormal, const CVector3<float> & vPoint )
{
  vNormal.Normalize();
  m_aValues[0] =  vNormal[0];
  m_aValues[1] =  vNormal[1];
  m_aValues[2] =  vNormal[2];
  m_aValues[3] = -(vNormal.Dot(vPoint));
}