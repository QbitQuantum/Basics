void ExampleStruct::PopulateMetaType( Helium::Reflect::MetaStruct& comp )
{
	comp.AddField( &ExampleStruct::m_Value1, "m_Value1" );
	comp.AddField( &ExampleStruct::m_Value2, "m_Value2" );
}