 void transform(Matrix4x4& mat, Matrix4x4& inv){
   m_point = mat*m_point;
   m_normal = inv.transpose()*m_normal;
 }