Piecewise<SBasis> reciprocalOnDomain(Interval range, double tol){
    Piecewise<SBasis> reciprocal_fn;
    //TODO: deduce R from tol...
    double R=2.;
    SBasis reciprocal1_R=reciprocal(Linear(1,R),3);
    double a=range.min(), b=range.max();
    if (a*b<0){
        b=std::max(fabs(a),fabs(b));
        a=0;
    }else if (b<0){
        a=-range.max();
        b=-range.min();
    }

    if (a<=tol){
        reciprocal_fn.push_cut(0);
        int i0=(int) floor(std::log(tol)/std::log(R));
        a=pow(R,i0);
        reciprocal_fn.push(Linear(1/a),a);
    }else{
        int i0=(int) floor(std::log(a)/std::log(R));
        a=pow(R,i0);
        reciprocal_fn.cuts.push_back(a);
    }  

    while (a<b){
        reciprocal_fn.push(reciprocal1_R/a,R*a);
        a*=R;
    }
    if (range.min()<0 || range.max()<0){
        Piecewise<SBasis>reciprocal_fn_neg;
        //TODO: define reverse(pw<sb>);
        reciprocal_fn_neg.cuts.push_back(-reciprocal_fn.cuts.back());
        for (unsigned i=0; i<reciprocal_fn.size(); i++){
            int idx=reciprocal_fn.segs.size()-1-i;
            reciprocal_fn_neg.push_seg(-reverse(reciprocal_fn.segs.at(idx)));
            reciprocal_fn_neg.push_cut(-reciprocal_fn.cuts.at(idx));
        }
        if (range.max()>0){
            reciprocal_fn_neg.concat(reciprocal_fn);
        }
        reciprocal_fn=reciprocal_fn_neg;
    }

    return(reciprocal_fn);
}