CVector3DF CVector3DF::Normal(const CVector3DF &vAB, const CVector3DF &vAC)
{
    return vAB.Cross(vAC).m_vVector.normalized();
}