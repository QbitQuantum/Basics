int
HFETApzLoad(GENmodel *inModel, CKTcircuit *ckt, SPcomplex *s)
{
    HFETAmodel *model = (HFETAmodel*)inModel;
    HFETAinstance *here;
    double gm;
    double gds;
    double xds;
    double ggs;
    double xgs;
    double ggd;
    double xgd;
    double ggspp;
    double ggdpp;
    double f;

    double m;

    for( ; model != NULL; model = model->HFETAnextModel ) 
    {
        for( here = model->HFETAinstances; here != NULL; 
             here = here->HFETAnextInstance) {

            if (here->HFETAowner != ARCHme) continue;

            gm  = *(ckt->CKTstate0 + here->HFETAgm);
            gds = *(ckt->CKTstate0 + here->HFETAgds);
            xds = CDS*ckt->CKTomega;
            ggs = *(ckt->CKTstate0 + here->HFETAggs);
            xgs = *(ckt->CKTstate0 + here->HFETAqgs);
            ggd = *(ckt->CKTstate0 + here->HFETAggd);
            xgd = *(ckt->CKTstate0 + here->HFETAqgd);
            ggspp = *(ckt->CKTstate0 + here->HFETAggspp);
            ggdpp = *(ckt->CKTstate0 + here->HFETAggdpp);
            if(model->HFETAkappaGiven && here->HFETAdelf != 0.0) {
              f     = ckt->CKTomega/2/M_PI;
              gds   = gds*(1+0.5*model->HFETAkappa*(1+tanh((f-here->HFETAfgds)/here->HFETAdelf)));
            }  

            m = here->HFETAm;

            *(here->HFETAdrainDrainPtr)                 += m * (model->HFETAdrainConduct);
            *(here->HFETAsourceSourcePtr)               += m * (model->HFETAsourceConduct);
            *(here->HFETAgatePrimeGatePrimePtr)         += m * (ggd+ggs+ggspp+ggdpp+model->HFETAgateConduct);
            *(here->HFETAdrainPrimeDrainPrimePtr)       += m * (gds+ggd+model->HFETAdrainConduct+model->HFETAgf);
            *(here->HFETAsourcePrimeSourcePrimePtr)     += m * (gds+gm+ggs+model->HFETAsourceConduct+model->HFETAgi);
            *(here->HFETAsourcePrmPrmSourcePrmPrmPtr)   += m * (model->HFETAgi+ggspp);
            *(here->HFETAdrainPrmPrmDrainPrmPrmPtr)     += m * (model->HFETAgf+ggdpp);
            *(here->HFETAdrainDrainPrimePtr)            -= m * (model->HFETAdrainConduct);
            *(here->HFETAdrainPrimeDrainPtr)            -= m * (model->HFETAdrainConduct);
            *(here->HFETAsourceSourcePrimePtr)          -= m * (model->HFETAsourceConduct);
            *(here->HFETAsourcePrimeSourcePtr)          -= m * (model->HFETAsourceConduct);
            *(here->HFETAgatePrimeDrainPrimePtr)        -= m * (ggd);
            *(here->HFETAdrainPrimeGatePrimePtr)        += m * (gm-ggd);
            *(here->HFETAgatePrimeSourcePrimePtr)       -= m * (ggs);
            *(here->HFETAsourcePrimeGatePrimePtr)       += m * (-ggs-gm);
            *(here->HFETAdrainPrimeSourcePrimePtr)      += m * (-gds-gm);
            *(here->HFETAsourcePrimeDrainPrimePtr)      -= m * (gds);
            *(here->HFETAsourcePrimeSourcePrmPrmPtr)    -= m * (model->HFETAgi);            
            *(here->HFETAsourcePrmPrmSourcePrimePtr)    -= m * (model->HFETAgi);
            *(here->HFETAgatePrimeSourcePrmPrmPtr)      -= m * (ggspp);
            *(here->HFETAsourcePrmPrmGatePrimePtr)      -= m * (ggspp);
            *(here->HFETAdrainPrimeDrainPrmPrmPtr)      -= m * (model->HFETAgf);
            *(here->HFETAdrainPrmPrmDrainPrimePtr)      -= m * (model->HFETAgf);
            *(here->HFETAgatePrimeDrainPrmPrmPtr)       -= m * (ggdpp);
            *(here->HFETAdrainPrmPrmGatePrimePtr)       -= m * (ggdpp);
            *(here->HFETAgateGatePtr)                   += m * (model->HFETAgateConduct);
            *(here->HFETAgateGatePrimePtr)              -= m * (model->HFETAgateConduct);
            *(here->HFETAgatePrimeGatePtr)              -= m * (model->HFETAgateConduct);
            
	    *(here->HFETAgatePrimeGatePrimePtr)         += m * ((xgd+xgs) * s->real);    
	    *(here->HFETAgatePrimeGatePrimePtr+1)       += m * ((xgd+xgs) * s->imag); 
	    *(here->HFETAdrainPrmPrmDrainPrmPrmPtr)     += m * (xgd * s->real);                                     
            *(here->HFETAdrainPrmPrmDrainPrmPrmPtr+1)   += m * (xgd * s->imag);
	    *(here->HFETAsourcePrmPrmSourcePrmPrmPtr)   += m * (xgs * s->real);
            *(here->HFETAsourcePrmPrmSourcePrmPrmPtr+1) += m * (xgs * s->imag);
	    *(here->HFETAgatePrimeDrainPrmPrmPtr)       -= m * (xgd * s->real);	  
            *(here->HFETAgatePrimeDrainPrmPrmPtr+1)     -= m * (xgd * s->imag);	    
	    *(here->HFETAgatePrimeSourcePrmPrmPtr)      -= m * (xgs * s->real);
            *(here->HFETAgatePrimeSourcePrmPrmPtr+1)    -= m * (xgs * s->imag);
	    *(here->HFETAdrainPrmPrmGatePrimePtr)       -= m * (xgd * s->real);
            *(here->HFETAdrainPrmPrmGatePrimePtr+1)     -= m * (xgd * s->imag);
	    *(here->HFETAsourcePrmPrmGatePrimePtr)      -= m * (xgs * s->real);
            *(here->HFETAsourcePrmPrmGatePrimePtr+1)    -= m * (xgs * s->imag);
	    *(here->HFETAdrainPrimeDrainPrimePtr)       += m * (xds * s->real);
            *(here->HFETAdrainPrimeDrainPrimePtr+1)     += m * (xds * s->imag);
	    *(here->HFETAsourcePrimeSourcePrimePtr)     += m * (xds * s->real);
            *(here->HFETAsourcePrimeSourcePrimePtr+1)   += m * (xds * s->imag);
	    *(here->HFETAdrainPrimeSourcePrimePtr)      -= m * (xds * s->real);
            *(here->HFETAdrainPrimeSourcePrimePtr+1)    -= m * (xds * s->imag);
	    *(here->HFETAsourcePrimeDrainPrimePtr)      -= m * (xds * s->real);
            *(here->HFETAsourcePrimeDrainPrimePtr+1)    -= m * (xds * s->imag);
        }
    }
    return(OK);
}