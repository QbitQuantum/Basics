void Transform::EnumerateClass( Reflect::Compositor<Transform>& comp )
{
  Reflect::Field* fieldScale = comp.AddField( &Transform::m_Scale, "m_Scale" );
  Reflect::Field* fieldRotate = comp.AddField( &Transform::m_Rotate, "m_Rotate" );
  Reflect::Field* fieldTranslate = comp.AddField( &Transform::m_Translate, "m_Translate" );

  Reflect::Field* fieldObjectTransform = comp.AddField( &Transform::m_ObjectTransform, "m_ObjectTransform" );
  Reflect::Field* fieldGlobalTransform = comp.AddField( &Transform::m_GlobalTransform, "m_GlobalTransform" );
  Reflect::Field* fieldInheritTransform = comp.AddField( &Transform::m_InheritTransform, "m_InheritTransform" );
}