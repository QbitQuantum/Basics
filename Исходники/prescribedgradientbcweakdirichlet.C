void PrescribedGradientBCWeakDirichlet :: checkIfCorner(bool &oIsCorner, bool &oDuplicatable, const FloatArray &iPos, const double &iNodeDistTol) const
{
    oIsCorner = false;
    oDuplicatable = false;

    FloatArray cornerPos = mLC;
    if ( iPos.distance(cornerPos) < iNodeDistTol ) {
        oIsCorner = true;
        oDuplicatable = true;
    }

    cornerPos = {
        mUC [ 0 ], mLC [ 1 ]
    };
    if ( iPos.distance(cornerPos) < iNodeDistTol ) {
        oIsCorner = true;
        oDuplicatable = true;
    }

    cornerPos = {
        mUC [ 0 ], mUC [ 1 ]
    };
    if ( iPos.distance(cornerPos) < iNodeDistTol ) {
        oIsCorner = true;
        oDuplicatable = true;
    }

    cornerPos = {
        mLC [ 0 ], mUC [ 1 ]
    };
    if ( iPos.distance(cornerPos) < iNodeDistTol ) {
        oIsCorner = true;
        oDuplicatable = true;
    }
}