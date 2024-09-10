void rec_jacobi( const double alpha, 
                 const double beta,
                 ROL::Vector<Real> &a,
                 ROL::Vector<Real> &b ) {

    Teuchos::RCP<std::vector<Real> > ap = 
        Teuchos::rcp_const_cast<std::vector<Real> >((Teuchos::dyn_cast<ROL::StdVector<Real> >(a)).getVector()); 
    Teuchos::RCP<std::vector<Real> > bp = 
        Teuchos::rcp_const_cast<std::vector<Real> >((Teuchos::dyn_cast<ROL::StdVector<Real> >(b)).getVector()); 

    int N = ap->size();
    Real nu = (beta-alpha)/double(alpha+beta+2.0);
    Real mu  = pow(2.0,alpha+beta+1.0)*tgamma(alpha+1.0)*tgamma(beta+1.0)/tgamma(alpha+beta+2.0);
    Real nab;
    Real sqdif = pow(beta,2)-pow(alpha,2);
                              
    (*ap)[0] = nu;
    (*bp)[0] = mu;
    
    if(N>1){
     
        for(int n=1;n<N;++n) {
            nab = 2*n+alpha+beta;
            (*ap)[n] = sqdif/(nab*(nab+2));              
        }

        (*bp)[1] = 4.0*(alpha+1.0)*(beta+1.0)/(pow(alpha+beta+2.0,2)*(alpha+beta+3.0));

        if(N>2) {
            for(int n=2;n<N;++n) {
                nab = 2*n+alpha+beta;
                (*bp)[n] = 4.0*(n+alpha)*(n+beta)*n*(n+alpha+beta)/(nab*nab*(nab+1.0)*(nab-1.0));
            }
        }
    }    
}