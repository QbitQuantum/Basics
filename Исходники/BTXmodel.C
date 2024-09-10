void updateBTX(pulsar *psr,double val,double err,int pos,int k)
{
    if (pos==param_fb)
    {
        psr->param[param_fb].val[k] += (val/powl(1.0e7,k+1));
        psr->param[param_fb].err[k]  = err/powl(1.0e7,k+1);
    }
    else if (pos==param_a1 || pos==param_ecc || pos==param_t0 || pos==param_gamma || pos==param_edot)
    {
        psr->param[pos].val[0] += val;
        psr->param[pos].err[0]  = err;
    }
    else if (pos==param_om)
    {
        psr->param[pos].val[0] += val*180.0/M_PI;
        psr->param[pos].err[0]  = err*180.0/M_PI;
    }
    else if (pos==param_pbdot)
    {
        psr->param[pos].val[0] += val;
        psr->param[pos].err[0]  = err;
    }
    else if (pos==param_omdot)
    {
        psr->param[pos].val[0] += val*(SECDAY*365.25)*180.0/M_PI;
        psr->param[pos].err[0]  = err*(SECDAY*365.25)*180.0/M_PI;
    }
    else if (pos==param_a1dot)
    {
        psr->param[pos].val[0] += val;
        psr->param[pos].err[0]  = err;
    }
}