   This file is part of Elemental and is under the BSD 2-Clause License, 
   which can be found in the LICENSE file in the root directory, or at 
   http://opensource.org/licenses/BSD-2-Clause
*/
#include "El.hpp"

namespace El {

template<typename F> 
void Fiedler( Matrix<F>& A, const vector<F>& c )
{
    DEBUG_ONLY(CSE cse("Fiedler"))
    const Int n = c.size();
    A.Resize( n, n );
    auto fiedlerFill = [&]( Int i, Int j ) { return Abs(c[i]-c[j]); };
    IndexDependentFill( A, function<F(Int,Int)>(fiedlerFill) );
}

template<typename F>
void Fiedler( AbstractDistMatrix<F>& A, const vector<F>& c )
{
    DEBUG_ONLY(CSE cse("Fiedler"))
    const Int n = c.size();
    A.Resize( n, n );
    auto fiedlerFill = [&]( Int i, Int j ) { return Abs(c[i]-c[j]); };
    IndexDependentFill( A, function<F(Int,Int)>(fiedlerFill) );
}

template<typename F>
void Fiedler( AbstractBlockDistMatrix<F>& A, const vector<F>& c )