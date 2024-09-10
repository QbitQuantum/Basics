inline bool
TriangIsNormal( const ElementalMatrix<F>& UPre, Base<F> tol )
{
    auto UPtr = ReadProxy<F,MC,MR>( &UPre );
    auto& U = *UPtr;

    const Base<F> diagFrob = FrobeniusNorm(GetDiagonal(U));
    const Base<F> upperFrob = FrobeniusNorm( U );
    const Base<F> offDiagFrob = Sqrt(upperFrob*upperFrob-diagFrob*diagFrob);
    return offDiagFrob <= tol*diagFrob;
}