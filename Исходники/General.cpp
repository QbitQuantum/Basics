void LocalInverse( DistMatrix<F,STAR,STAR>& A )
{
    DEBUG_CSE
    Inverse( A.Matrix() );
}