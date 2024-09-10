void Influence::EnumerateClass( Reflect::Compositor<Influence>& comp )
{
  Reflect::Field* fieldObjects = comp.AddField( &Influence::m_Objects, "m_Objects" );
  Reflect::Field* fieldWeights = comp.AddField( &Influence::m_Weights, "m_Weights" );
}