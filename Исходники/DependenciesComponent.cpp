void DependenciesComponent::EnumerateClass( Reflect::Compositor<DependenciesComponent>& comp )
{
  comp.GetComposite().m_UIName = TXT( "Dependencies" );

  Reflect::Field* fieldPaths = comp.AddField( &DependenciesComponent::m_Paths, "m_Paths", Reflect::FieldFlags::Path );
}