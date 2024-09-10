void GridSettings::PopulateMetaType( Reflect::MetaStruct& comp )
{
	comp.AddField( &GridSettings::m_Units, TXT( "Units" ) );
	comp.AddField( &GridSettings::m_Width, TXT( "Width" ) );
	comp.AddField( &GridSettings::m_Length, TXT( "Length" ) );
	comp.AddField( &GridSettings::m_MajorStep, TXT( "Major Step" ) );
	comp.AddField( &GridSettings::m_MinorStep, TXT( "Minor Step" ) );
	comp.AddField( &GridSettings::m_AxisColor, TXT( "Axis Color" ) );
	comp.AddField( &GridSettings::m_MajorColor, TXT( "Major Color" ) );
	comp.AddField( &GridSettings::m_MinorColor, TXT( "Minor Color" ) );
}