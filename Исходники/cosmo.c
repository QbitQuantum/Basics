double csmExp2Time(CSM csm,double dExp) {
    double dOmega0 = csm->dOmega0;
    double dHubble0 = csm->dHubble0;
    double a0,A,B,eta;

    if (!csm->bComove) {
	/*
	 ** Invalid call!
	 */
	assert(0);
	}
    if (csm->dLambda == 0.0 && csm->dOmegaRad == 0.0) {
	if (dOmega0 == 1.0) {
	    assert(dHubble0 > 0.0);
	    if (dExp == 0.0) return(0.0);
	    return(2.0/(3.0*dHubble0)*pow(dExp,1.5));
	    }
	else if (dOmega0 > 1.0) {
	    assert(dHubble0 >= 0.0);
	    if (dHubble0 == 0.0) {
		B = 1.0/sqrt(dOmega0);
		eta = acos(1.0-dExp);
		return(B*(eta-sin(eta)));
		}
	    if (dExp == 0.0) return(0.0);
	    a0 = 1.0/dHubble0/sqrt(dOmega0-1.0);
	    A = 0.5*dOmega0/(dOmega0-1.0);
	    B = A*a0;
	    eta = acos(1.0-dExp/A);
	    return(B*(eta-sin(eta)));
	    }
	else if (dOmega0 > 0.0) {
	    assert(dHubble0 > 0.0);
	    if (dExp == 0.0) return(0.0);
	    a0 = 1.0/dHubble0/sqrt(1.0-dOmega0);
	    A = 0.5*dOmega0/(1.0-dOmega0);
	    B = A*a0;
	    eta = acosh(dExp/A+1.0);
	    return(B*(sinh(eta)-eta));
	    }
	else if (dOmega0 == 0.0) {
	    assert(dHubble0 > 0.0);
	    if (dExp == 0.0) return(0.0);
	    return(dExp/dHubble0);
	    }
	else {
	    /*
	     ** Bad value.
	     */
	    assert(0);
	    return(0.0);
	    }
	}
    else {
	return dRombergO(csm, (double (*)(void *, double)) csmCosmoTint,
			 0.0, pow(dExp, 1.5), EPSCOSMO);
	}
    }