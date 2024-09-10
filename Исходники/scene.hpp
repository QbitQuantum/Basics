 void set_transform(const Matrix4x4& m)
 {
   m_trans = m;
   m_invtrans = m.invert();
 }