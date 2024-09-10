 void ani_subobject_state::set_affine_transform(const ani_affine_transform& affine_transform)
 {
     m_scale.x = sqrtf((affine_transform.a * affine_transform.a) + (affine_transform.c * affine_transform.c));
     m_scale.y = sqrtf((affine_transform.b * affine_transform.b) + (affine_transform.d * affine_transform.d));
     
     m_position.x = affine_transform.tx;
     m_position.y = affine_transform.ty;
     
     f32 sign = atanf(-affine_transform.c / affine_transform.a);
     f32 radians  = acosf(affine_transform.a / m_scale.x);
     m_rotation  = glm::degrees(radians);
     
     if ((m_rotation > 90.f && sign > 0.f) || (m_rotation < 90.f && sign < 0.f))
     {
         m_rotation = 360.f - m_rotation;
     }
 }