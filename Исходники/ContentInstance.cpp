void Instance::EnumerateClass( Reflect::Compositor<Instance>& comp )
{
  Reflect::Field* fieldSolid                = comp.AddField( &Instance::m_Solid, "m_Solid" );
  Reflect::Field* fieldSolidOverride        = comp.AddField( &Instance::m_SolidOverride, "m_SolidOverride" );
  Reflect::Field* fieldTransparent          = comp.AddField( &Instance::m_Transparent, "m_Transparent" );
  Reflect::Field* fieldTransparentOverride  = comp.AddField( &Instance::m_TransparentOverride, "m_TransparentOverride" );
}