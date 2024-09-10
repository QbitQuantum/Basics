void EnrichmentItem :: calcPolarCoord(double &oR, double &oTheta, const FloatArray &iOrigin, const FloatArray &iPos, const FloatArray &iN, const FloatArray &iT, const EfInput &iEfInput, bool iFlipTangent)
{
    FloatArray q = {
        iPos.at(1) - iOrigin.at(1), iPos.at(2) - iOrigin.at(2)
    };

    const double tol = 1.0e-20;

    // Compute polar coordinates
    oR = iOrigin.distance(iPos);

    if ( oR > tol ) {
        q.times(1.0 / oR);
    }

    const double pi = M_PI;

    //    if( q.dotProduct(iT) > 0.0 ) {
    //        oTheta = asin( q.dotProduct(iN) );
    //    } else {
    //        if ( q.dotProduct(iN) > 0.0 ) {
    //            oTheta = pi - asin( q.dotProduct(iN) );
    //        } else {
    //            oTheta = -pi - asin( q.dotProduct(iN) );
    //        }
    //    }


    const double tol_q = 1.0e-3;
    double phi = iEfInput.mLevelSet;

    if ( iFlipTangent ) {
        phi *= -1.0;
    }

    double phi_r = 0.0;
    if ( oR > tol ) {
        phi_r = fabs(phi / oR);
    }

    if ( phi_r > 1.0 - XfemTolerances :: giveApproxZero() ) {
        phi_r = 1.0 - XfemTolerances :: giveApproxZero();
    }

    if ( iEfInput.mArcPos < tol_q || iEfInput.mArcPos > ( 1.0 - tol_q ) ) {
        double q_dot_n = q.dotProduct(iN);
        if ( q_dot_n > 1.0 - XfemTolerances :: giveApproxZero() ) {
            q_dot_n = 1.0 - XfemTolerances :: giveApproxZero();
        }

        oTheta = asin(q_dot_n);
    } else {
        if ( phi > 0.0 ) {
            oTheta = pi - asin( fabs(phi_r) );
        } else {
            oTheta = -pi + asin( fabs(phi_r) );
        }
    }
}