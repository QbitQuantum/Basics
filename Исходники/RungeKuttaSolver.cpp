void RungeKuttaSolver::rkqs(double y[], double dydx[], int n, double *x, double htry, double eps, double yscal[], double *hdid, double *hnext, RungeKuttaEquation *Equations[])
{
	int i;
	double errmax,h,xnew,*yerr,*ytemp;

	yerr=new_vector(1,n);
	ytemp=new_vector(1,n);
	h=htry;
	for (;;)
	{
		rkck(y,dydx,n,*x,h,ytemp,yerr,Equations);
		errmax=0.0;
		for (i=1;i<=n;i++) 
			errmax=FMAX(errmax,fabs(yerr[i]/yscal[i]));
		errmax /= eps;
		if (errmax > 1.0)
		{
			h=SAFETY*h*pow(errmax,PSHRNK);
			if (h < 0.1*h)
				h *= 0.1;

			xnew=(*x)+h;
			if (xnew == *x)	
				nrerror("stepsize underflow in rkqs");
			continue;
		}
		else
		{
			if (errmax > ERRCON) 
				*hnext=SAFETY*h*pow(errmax,PGROW);
			else 
				*hnext=5.0*h;
			*x += (*hdid=h);
			for (i=1;i<=n;i++) 
				y[i]=ytemp[i];
			break;
		}
	}
	delete_vector(ytemp,1,n);
	delete_vector(yerr,1,n);
}