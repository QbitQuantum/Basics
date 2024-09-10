void PrescribedGradientBCWeakPeriodic :: checkIfCorner(bool &oIsCorner, bool &oDuplicatable, const FloatArray &iPos, const double &iNodeDistTol) const
{
	oIsCorner = false;
	oDuplicatable = false;

    FloatArray cornerPos = mLC;
    if( iPos.distance(cornerPos) < iNodeDistTol ) {
    	oIsCorner = true;
    }

    cornerPos = {mUC[0], mLC[1]};
    if( iPos.distance( cornerPos ) < iNodeDistTol ) {
    	oIsCorner = true;
    }

    cornerPos = {mUC[0], mUC[1]};
    if( iPos.distance( cornerPos ) < iNodeDistTol ) {
    	oIsCorner = true;
    	if(mTractionInterpOrder == 1) {
    	    oDuplicatable = true;
    	}
    }

    cornerPos = {mLC[0], mUC[1]};
    if( iPos.distance( cornerPos ) < iNodeDistTol ) {
    	oIsCorner = true;
    }
}