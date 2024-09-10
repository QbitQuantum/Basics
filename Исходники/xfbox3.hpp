 void setTransform(const Matrix4<Type> & m)
 {
     m_matrix = m;
     m_invertedMatrix = m.inverse();
 }