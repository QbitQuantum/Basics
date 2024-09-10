   Copyright (c) 2009-2016, Jack Poulson
   All rights reserved.

   This file is part of Elemental and is under the BSD 2-Clause License, 
   which can be found in the LICENSE file in the root directory, or at 
   http://opensource.org/licenses/BSD-2-Clause
*/
#include "El.hpp"

namespace El {

template<typename Real>
void LowerClip( Matrix<Real>& X, Real lowerBound )
{
    DEBUG_ONLY(CSE cse("LowerClip"))
    auto lowerClip = [&]( Real alpha ) { return Max(lowerBound,alpha); };
    EntrywiseMap( X, function<Real(Real)>(lowerClip) );
}

template<typename Real>
void UpperClip( Matrix<Real>& X, Real upperBound )
{
    DEBUG_ONLY(CSE cse("UpperClip"))
    auto upperClip = [&]( Real alpha ) { return Min(upperBound,alpha); };
    EntrywiseMap( X, function<Real(Real)>(upperClip) );
}

template<typename Real>
void Clip( Matrix<Real>& X, Real lowerBound, Real upperBound )
{
    DEBUG_ONLY(CSE cse("Clip"))