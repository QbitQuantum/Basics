Base<Field> FrobeniusNorm( const SparseMatrix<Field>& A )
{
    EL_DEBUG_CSE
    typedef Base<Field> Real;
    Real scale = 0;
    Real scaledSquare = 1;
    const Int numEntries = A.NumEntries();
    const Field* valBuf = A.LockedValueBuffer();
    for( Int k=0; k<numEntries; ++k )
        UpdateScaledSquare( valBuf[k], scale, scaledSquare );
    return scale*Sqrt(scaledSquare);
}