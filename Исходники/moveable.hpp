 /** Sets the XYZ coordinates of the moveable. */
 void setXYZ(const Vec3& a)
 {
     m_transform.setOrigin(a);
     if(m_motion_state)
         m_motion_state->setWorldTransform(m_transform);
 }