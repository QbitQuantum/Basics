void Shader::EnumerateClass( Reflect::Compositor<Shader>& comp )
{
  comp.AddField( &Shader::m_WrapU, "m_WrapU" );
  comp.AddField( &Shader::m_WrapV, "m_WrapV" );
  comp.AddField( &Shader::m_RepeatU, "m_RepeatU" );
  comp.AddField( &Shader::m_RepeatV, "m_RepeatV" );
  comp.AddField( &Shader::m_BaseColor, "m_BaseColor" );
  comp.AddField( &Shader::m_AssetPath, "m_AssetPath" );
}