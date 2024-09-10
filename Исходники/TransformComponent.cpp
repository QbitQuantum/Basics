 Mat4 TransformComponent::GetTransform(bool Relative)
 {
     if(m_Updated)
     {
         /* To do: Optimize. */
         
         m_Transform = Mat4::Identity;
         if(m_Position.x + m_Position.y + m_Position.z != 0.0f) m_Transform = Translation(m_Position);
         if(!m_FirstPerson) {
             if(m_Orientation.w != 0.0f) m_Transform *= m_Orientation.ToMat();
         } else {
             Quat pitch = Quat(Vec3(1,0,0), m_FirstPersonYRot);
             Quat yaw = Quat(Vec3(0,1,0), m_FirstPersonXRot);
             m_Orientation = yaw * pitch;
             if(m_Orientation.w != 0.0f) m_Transform *= m_Orientation.ToMat();
         }
         m_Transform *= SandboxSimulator::Scale(m_Scale);
         m_NormalMatrix = m_Orientation.ToMat().Inverse().Transpose();
         m_Updated = false;
     }
     //Entity* Parent = m_Entity->GetParent();
     if(m_HasParent) {
         TransformComponent* t = (TransformComponent*)m_RelativeTo->GetComponentByType(CT_TRANSFORM);
         if(t)
         {
             Mat4 ret = m_Transform;
             ret = t->GetOrientation(false).ToMat() * ret;
             ret = SandboxSimulator::Translation(t->GetPosition(false)) * ret;
             ret = SandboxSimulator::Scale(t->GetScale()) * ret;
             return ret;
         }
     }
     /*if(Parent && !m_Simulated && !Relative && (m_InheritPosition || m_InheritOrientation || m_InheritScale))
     {
         TransformComponent* t = GetTransformComponent(Parent);
         if(t)
         {
             if(m_InheritPosition && m_InheritOrientation && m_InheritScale) return t->GetTransform(Relative) * m_Transform;
             Matrix4 ret = m_Transform;
             if(m_InheritOrientation) ret = t->GetOrientation(false).ToMatrix() * ret;
             if(m_InheritPosition   ) ret = Translation(t->GetPosition(false))  * ret;
             if(m_InheritScale      ) ret = Reality::Scale(t->GetScale())       * ret;
             return ret;
         }
     }*/
     return m_Transform;
 }