void Locator::EnumerateClass( Reflect::Compositor<Locator>& comp )
{
  Reflect::EnumerationField* enumShape = comp.AddEnumerationField( &Locator::m_Shape, "m_Shape" );
}