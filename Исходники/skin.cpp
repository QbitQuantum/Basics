void Influence::PopulateMetaType( Reflect::MetaStruct& comp )
{
    comp.AddField( &Influence::m_Objects,           TXT( "m_Objects" ) );
    comp.AddField( &Influence::m_Weights,           TXT( "m_Weights" ) );
}