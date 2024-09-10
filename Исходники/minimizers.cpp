void doConjStep(VectorXd &XY,
                VectorXd &s0,
                VectorXd &gradE,
                const vector<spring> &springlist,
                const vector<vector<int>> &springpairs,
		int bendingOn,
                double kappa,
                int conjsteps,
                double g11,
                double g12,
                double g22)
{
    double a1=0.0;
    double a2=1.0;
    double betan;
    VectorXd gradEn(gradE.size());
    VectorXd sn(s0.size());
    functor network(XY,s0,springlist,springpairs,kappa,g11,g12,g22);
   doBracketfind(a1,a2,network);
    if(doBracketfind(a1,a2,network))
    {
        // double an=doFalsePosition(network,a1,a2);
        //double an=Ridder(network,a1,a2);
        double an=Brent(network,a1,a2,1e-12);
        //Update the positions.
        XY=XY+an*s0;
	if(bendingOn==0){
	  gradEn=HarmonicGradient(springlist,XY,g11,g12,g22);
	} else{
	  gradEn=HarmonicGradient(springlist,XY,g11,g12,g22)+BendingGrad(springpairs,springlist,XY,kappa,g11,g12,g22);
	}
	betan=(gradEn-gradE).dot(gradEn)/(gradE.dot(gradE));
        //Did not find bracket, reset CG-method    
    } else{
        betan=0.0;
	if(bendingOn==0){
	  gradE=HarmonicGradient(springlist,XY,g11,g12,g22);
	} else{
	    gradE=HarmonicGradient(springlist,XY,g11,g12,g22)+BendingGrad(springpairs,springlist,XY,kappa,g11,g12,g22);
	}
	s0=-gradE;
        //cout<<"Bracket failed, Reset CG"<<endl;
        return;
    }
    if(conjsteps%5 ==0.0) betan=0.0;
    if(betan<0.0) betan=0; //max(betan,0)
    if(abs(gradEn.dot(gradE))>.5*gradE.dot(gradE)) betan=0.0; 
    if(-2*gradE.dot(gradE)>gradE.dot(s0) && gradE.dot(s0) >-.2*gradE.dot(gradE)) betan=0.0;
    //cout<<"\r"<<"** Beta "<<betan<<flush;
    sn=-gradEn+betan*s0;    
    gradE=gradEn;
    s0=sn;
}