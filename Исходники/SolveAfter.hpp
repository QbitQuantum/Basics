inline void
SolveAfter
( UpperOrLower uplo, Orientation orientation, 
  const DistMatrix<F>& A, DistMatrix<F>& B )
{
#ifndef RELEASE
    CallStackEntry entry("cholesky::SolveAfter");
    if( A.Grid() != B.Grid() )
        LogicError("{A,B} must be distributed over the same grid");
    if( A.Height() != A.Width() )
        LogicError("A must be square");
    if( A.Height() != B.Height() )
        LogicError("A and B must be the same height");
#endif
    if( B.Width() == 1 )
    {
        if( uplo == LOWER )
        {
            if( orientation == TRANSPOSE )
                Conjugate( B );
            Trsv( LOWER, NORMAL, NON_UNIT, A, B );
            Trsv( LOWER, ADJOINT, NON_UNIT, A, B );
            if( orientation == TRANSPOSE )
                Conjugate( B );
        }
        else
        {
            if( orientation == TRANSPOSE )
                Conjugate( B );
            Trsv( UPPER, ADJOINT, NON_UNIT, A, B );
            Trsv( UPPER, NORMAL, NON_UNIT, A, B );
            if( orientation == TRANSPOSE )
                Conjugate( B );
        }
    }
    else
    {
        if( uplo == LOWER )
        {
            if( orientation == TRANSPOSE )
                Conjugate( B );
            Trsm( LEFT, LOWER, NORMAL, NON_UNIT, F(1), A, B );
            Trsm( LEFT, LOWER, ADJOINT, NON_UNIT, F(1), A, B );
            if( orientation == TRANSPOSE )
                Conjugate( B );
        }
        else
        {
            if( orientation == TRANSPOSE )
                Conjugate( B );
            Trsm( LEFT, UPPER, ADJOINT, NON_UNIT, F(1), A, B );
            Trsm( LEFT, UPPER, NORMAL, NON_UNIT, F(1), A, B );
            if( orientation == TRANSPOSE )
                Conjugate( B );
        }
    }
}