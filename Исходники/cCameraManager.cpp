Vec3f cCameraManager::getRight()
{
   Vec3f right;
   Vec3f lookingVec = m_vecCamPos - m_vecCamLookAt;
   lookingVec.Normalize();
   Vec3f::Cross3(right, lookingVec, m_vecCamUp);
   right.Normalize();

   return right;
}