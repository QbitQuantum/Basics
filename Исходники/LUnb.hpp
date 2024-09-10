   which can be found in the LICENSE file in the root directory, or at 
   http://opensource.org/licenses/BSD-2-Clause
*/
#pragma once
#ifndef EL_HESSENBERG_LUNB_HPP
#define EL_HESSENBERG_LUNB_HPP

namespace El {
namespace hessenberg {

template<typename F>
inline void LUnb( Matrix<F>& A, Matrix<F>& t )
{
    DEBUG_ONLY(CallStackEntry cse("hessenberg::LUnb"))
    const Int n = A.Height();
    const Int tHeight = Max(n-1,0);
    t.Resize( tHeight, 1 );

    Matrix<F> z1, z21;

    for( Int k=0; k<n-1; ++k )
    {
        auto a12      = ViewRange( A, k,   k+1, k+1, n   );
        auto alpha12L = ViewRange( A, k,   k+1, k+1, k+2 );
        auto a12R     = ViewRange( A, k,   k+2, k+1, n   );
        auto A22      = ViewRange( A, k+1, k+1, n,   n   );
        auto A2       = ViewRange( A, k+1, 0,   n,   n   );

        // Find tau and v such that
        //  |alpha12L a12R| /I - tauP | 1   | | 1 conj(v) |\ = |beta 0|
        //                  \         | v^T |              /