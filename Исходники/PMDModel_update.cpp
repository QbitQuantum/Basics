/* PMDModel::smearAllBonesToDefault: smear all bone pos/rot into default value (rate 1.0 = keep, rate 0.0 = reset) */
void PMDModel::smearAllBonesToDefault(float rate)
{
   unsigned short i;
   const btVector3 v(0.0f, 0.0f, 0.0f);
   const btQuaternion q(0.0f, 0.0f, 0.0f, 1.0f);
   btVector3 tmpv;
   btQuaternion tmpq;

   for (i = 0; i < m_numBone; i++) {
      m_boneList[i].getCurrentPosition(&tmpv);
      tmpv = v.lerp(tmpv, rate);
      m_boneList[i].setCurrentPosition(&tmpv);
      m_boneList[i].getCurrentRotation(&tmpq);
      tmpq = q.slerp(tmpq, rate);
      m_boneList[i].setCurrentRotation(&tmpq);
   }
   for (i = 0; i < m_numFace; i++) {
      m_faceList[i].setWeight(m_faceList[i].getWeight() * rate);
   }
}