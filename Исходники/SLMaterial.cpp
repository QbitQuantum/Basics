// Solve numerically for lambda
// Subclasses can override for analytical solution if possible
double SLMaterial::SolveForLambdaBracketed(MPMBase *mptr,int np,double strial,Tensor *stk,double Gred,
								double psKred,double Ptrial,double delTime,HardeningAlpha *a,void *properties,int offset) const
{
	if(np==PLANE_STRESS_MPM)
	{	// not allowed
		return 0.;
	}
	else
	{	// solve - sqrt(2/3)GetYield(alpha+dalpha,dalpha) + strial - 2 GRed sqrt(3/2)dalpha  = 0
		SLProperties *p = (SLProperties *)properties;
		double rho = parent->GetRho(mptr);
		
		// test lower limit
		a->dalpha = delTime*p->epdotmin;
		a->alpint = mptr->GetHistoryDble(0,offset) + a->dalpha;
		p->isConstantYT = true;
		p->constantYT = YTmin;
		double gmin = strial - 2.*Gred*a->dalpha/SQRT_TWOTHIRDS - SQRT_TWOTHIRDS*GetYield(mptr,np,delTime,a,p);
		if(gmin<0.)
		{	// low strain rate answer between 0 and epdotmin
			double lambdak = HardeningLawBase::SolveForLambda(mptr,np,strial,stk,Gred,psKred,1.,delTime,a,p,offset);
			//cout << "# low strain rate condition " << lambdak << " should be below " << delTime*epdotmin/SQRT_TWOTHIRDS << endl;
			p->isConstantYT = false;
			mptr->SetHistoryDble(YT_HISTORY,p->currentYTred*rho*1.e-6,offset);
			mptr->SetHistoryDble(EPDOT_HISTORY,SQRT_TWOTHIRDS*lambdak/delTime,offset);
			return lambdak;
		}
		
		// test upper limit
		a->dalpha = delTime*p->epdotmax;
		a->alpint = mptr->GetHistoryDble(0,offset) + a->dalpha;
		p->constantYT=YPred;
		double gmax =  strial - 2.*Gred*a->dalpha/SQRT_TWOTHIRDS - SQRT_TWOTHIRDS*GetYield(mptr,np,delTime,a,p);
		if(gmax>0.)
		{	// high string rate answer for rate higher than epmax
			double lambdak=HardeningLawBase::SolveForLambda(mptr,np,strial,stk,Gred,psKred,1.,delTime,a,p,offset);
			//cout << "# high strain rate condition " << lambdak << " should be above " << delTime*epdotmax/SQRT_TWOTHIRDS << endl;
			p->isConstantYT = false;
			mptr->SetHistoryDble(YT_HISTORY,p->currentYTred*rho*1.e-6,offset);
			mptr->SetHistoryDble(EPDOT_HISTORY,SQRT_TWOTHIRDS*lambdak/delTime,offset);
			return lambdak;
		}
		p->isConstantYT=false;
		
		// Newton method in ln epdot space
		p->currentYTred=fmax(YTmin,mptr->GetHistoryDble(YT_HISTORY,offset)*1.e6/rho);
		double epdot=GetEpdot(p->currentYTred,p->TwoUkkT);
		double logepdot = log(epdot);
		a->dalpha = epdot*delTime;
		a->alpint = mptr->GetHistoryDble(0,offset) + a->dalpha;
		int step=1;
		while(true)
		{	// update iterative variables (alpha, dalpha)
			double glam = -SQRT_TWOTHIRDS*GetYield(mptr,np,delTime,a,p) + strial - 2.*Gred*a->dalpha/SQRT_TWOTHIRDS;
			double slope = -2.*Gred*a->dalpha/SQRT_TWOTHIRDS - GetKPrime(mptr,np,delTime,a,p);
			double delLogepdot = -glam/slope;
			logepdot += delLogepdot;
			
			// check for convergence
			a->dalpha = exp(logepdot)*delTime;
			a->alpint = mptr->GetHistoryDble(0,offset) + a->dalpha;
			if(step>20 || fabs(delLogepdot)<0.0001) break;
			step++;
		}
	
		// set history when done
		mptr->SetHistoryDble(YT_HISTORY,p->currentYTred*rho*1.e-6,offset);
		mptr->SetHistoryDble(EPDOT_HISTORY,a->dalpha/delTime,offset);
		return a->dalpha/SQRT_TWOTHIRDS;
		
	}
	
}