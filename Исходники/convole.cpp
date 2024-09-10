Piecewise<SBasis> convole(SBasisOf<double> const &f, Interval dom_f, 
                          SBasisOf<double> const &g, Interval dom_g,
                          bool f_cst_ends = false){

    if ( dom_f.extent() < dom_g.extent() ) return convole(g, dom_g, f, dom_f);

    Piecewise<SBasis> result;

    SBasisOf<SBasisOf<double> > u,v;
    u.push_back(LinearOf<SBasisOf<double> >(SBasisOf<double>(LinearOf<double>(0,1))));
    v.push_back(LinearOf<SBasisOf<double> >(SBasisOf<double>(LinearOf<double>(0,0)),
                                            SBasisOf<double>(LinearOf<double>(1,1))));
    SBasisOf<SBasisOf<double> > v_u = (v - u)*(dom_f.extent()/dom_g.extent());
    v_u += SBasisOf<SBasisOf<double> >(SBasisOf<double>(-dom_g.min()/dom_g.extent()));
    SBasisOf<SBasisOf<double> > gg = multi_compose(g,v_u);
    SBasisOf<SBasisOf<double> > ff = SBasisOf<SBasisOf<double> >(f);
    SBasisOf<SBasisOf<double> > hh = integral(ff*gg,0);
    
    result.cuts.push_back(dom_f.min()+dom_g.min());
    //Note: we know dom_f.extent() >= dom_g.extent()!!
    //double rho = dom_f.extent()/dom_g.extent();
    double t0 = dom_g.min()/dom_f.extent();
    double t1 = dom_g.max()/dom_f.extent();
    double t2 = t0+1;
    double t3 = t1+1;
    SBasisOf<double> a,b,t;
    SBasis seg;
    a = SBasisOf<double>(LinearOf<double>(0,0)); 
    b = SBasisOf<double>(LinearOf<double>(0,t1-t0)); 
    t = SBasisOf<double>(LinearOf<double>(t0,t1)); 
    seg = toSBasis(compose(hh,b,t)-compose(hh,a,t));
    result.push(seg,dom_f.min() + dom_g.max());
    if (dom_f.extent() > dom_g.extent()){
        a = SBasisOf<double>(LinearOf<double>(0,t2-t1)); 
        b = SBasisOf<double>(LinearOf<double>(t1-t0,1)); 
        t = SBasisOf<double>(LinearOf<double>(t1,t2)); 
        seg = toSBasis(compose(hh,b,t)-compose(hh,a,t));
        result.push(seg,dom_f.max() + dom_g.min());
    }
    a = SBasisOf<double>(LinearOf<double>(t2-t1,1.)); 
    b = SBasisOf<double>(LinearOf<double>(1.,1.)); 
    t = SBasisOf<double>(LinearOf<double>(t2,t3)); 
    seg = toSBasis(compose(hh,b,t)-compose(hh,a,t));
    result.push(seg,dom_f.max() + dom_g.max());
    result*=dom_f.extent();
    
    //--constant ends correction--------------
    if (f_cst_ends){
        SBasis ig = toSBasis(integraaal(g))*dom_g.extent();
        ig -= ig.at0();
        Piecewise<SBasis> cor;
        cor.cuts.push_back(dom_f.min()+dom_g.min());
        cor.push(reverse(ig)*f.at0(),dom_f.min()+dom_g.max());
        cor.push(Linear(0),dom_f.max()+dom_g.min());
        cor.push(ig*f.at1(),dom_f.max()+dom_g.max());
        result+=cor;
    }
    //----------------------------------------
    return result;
}