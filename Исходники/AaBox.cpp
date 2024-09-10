void Helium::Simd::AaBox::PopulateMetaType( Reflect::MetaStruct& comp )
{
	comp.AddField( &AaBox::m_minimum, "m_minimum" );
	comp.AddField( &AaBox::m_maximum, "m_maximum" );
}