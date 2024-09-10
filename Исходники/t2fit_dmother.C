double t2FitFunc_dmsinusoids(pulsar *psr, int ipsr ,double x ,int ipos ,param_label label,int k){
    if (label==param_dm_sin1yr){
        return 1.0/(DM_CONST*powl(psr[ipsr].obsn[ipos].freqSSB/1.0e6,2))*sin(2*M_PI/(365.25)*(psr[ipsr].obsn[ipos].sat - psr[ipsr].param[param_dmepoch].val[0]));
    } else if (label==param_dm_cos1yr) {
        return 1.0/(DM_CONST*powl(psr[ipsr].obsn[ipos].freqSSB/1.0e6,2))*cos(2*M_PI/(365.25)*(psr[ipsr].obsn[ipos].sat - psr[ipsr].param[param_dmepoch].val[0]));
    } else {
        logerr("Called dmsinusoids without dmsin1yr or dmcos1yr");
        return 0;
    }
}