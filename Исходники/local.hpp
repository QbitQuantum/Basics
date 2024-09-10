#include ELEM_SCALE_INC
#include ELEM_GERU_INC

namespace elem {
namespace lu {

// Local LU _without_ partial pivoting

template<typename F> 
inline void
UnbFLAME( Matrix<F>& A )
{
    DEBUG_ONLY(CallStackEntry cse("lu::UnbFLAME"))
    const Int m = A.Height();
    const Int n = A.Width();
    const Int minDim = Min(m,n);
    for( Int k=0; k<minDim; ++k )
    {
        auto alpha11 = ViewRange( A, k,   k,   k+1, k+1 );
        auto a12     = ViewRange( A, k,   k+1, k+1, n   );
        auto a21     = ViewRange( A, k+1, k,   m,   k+1 );
        auto A22     = ViewRange( A, k+1, k+1, m,   n   );

        F alpha = alpha11.Get(0,0);
        if( alpha == F(0) )
            throw SingularMatrixException();
        Scale( 1/alpha, a21 );
        Geru( F(-1), a21, a12, A22 );
    }
}
