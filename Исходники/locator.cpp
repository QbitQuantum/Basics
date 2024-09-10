void Locator::PopulateStructure( Reflect::Structure& comp )
{
    Reflect::Field* field = comp.AddField( &Locator::m_Shape, TXT( "m_Shape" ) );
    field->SetProperty( TXT( "HelpText" ), TXT( "Determines the shape of the locator node." ) );
}