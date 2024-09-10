void ManifestVersion::EnumerateClass( Reflect::Compositor<ManifestVersion>& comp )
{
  Reflect::Field* fieldManifestVersion = comp.AddField( &ManifestVersion::m_ManifestVersion, "m_ManifestVersion", Reflect::FieldFlags::Force );
}