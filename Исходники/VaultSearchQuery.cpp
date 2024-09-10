void VaultSearchQuery::PopulateComposite( Reflect::Composite& comp )
{
    comp.AddField( &VaultSearchQuery::m_QueryString, TXT( "m_QueryString" ) );
}