void SettingsManager::PopulateStructure( Reflect::Structure& comp )
{
    comp.AddField( &SettingsManager::m_SettingsMap, TXT( "m_SettingsMap" ), Reflect::FieldFlags::Hide );
}