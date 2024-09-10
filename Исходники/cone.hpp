 Vector3D computenormal(const Vector3D & p_) const{
     // compute the cone normal at point p_
     Vector3D e = p_ - m_vertex;
     Vector3D h = e.cross_product(m_axis);
     Vector3D n = e.cross_product(h);
     return n.normalize();
 }