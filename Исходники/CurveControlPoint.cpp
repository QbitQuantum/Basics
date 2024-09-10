void CurveControlPoint::EnumerateClass( Reflect::Compositor<CurveControlPoint>& comp )
{
    comp.AddField( &CurveControlPoint::m_Position, "m_Position" );
}