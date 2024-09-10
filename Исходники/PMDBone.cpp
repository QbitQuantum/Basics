/* PMDBone::update: update internal transform for current position / rotation */
void PMDBone::update()
{
   btQuaternion r;
   const btQuaternion norot(0.0f, 0.0f, 0.0f, 1.0f);

   m_trans.setOrigin(m_pos + m_offset);
   if (m_type == FOLLOW_ROTATE) {
      /* for co-rotate bone, further apply the rotation of child bone scaled by the rotation weight */
      r = m_rot * norot.slerp(m_childBone->m_rot, m_rotateCoef);
      m_trans.setRotation(r);
   } else {
      m_trans.setRotation(m_rot);
   }
   if (m_parentBone)
      m_trans = m_parentBone->m_trans * m_trans;
}