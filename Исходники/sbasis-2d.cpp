//TODO: handle the case when B is "behind" A for the natural orientation of the level set.
//TODO: more generally, there might be up to 4 solutions. Choose the best one!
D2<SBasis>
sb2d_cubic_solve(SBasis2d const &f, Geom::Point const &A, Geom::Point const &B){
    D2<SBasis>result;//(Linear(A[X],B[X]),Linear(A[Y],B[Y]));
    //g_warning("check 0 = %f = %f!", f.apply(A[X],A[Y]), f.apply(B[X],B[Y]));

    SBasis2d f_u  = partial_derivative(f  , 0);
    SBasis2d f_v  = partial_derivative(f  , 1);
    SBasis2d f_uu = partial_derivative(f_u, 0);
    SBasis2d f_uv = partial_derivative(f_v, 0);
    SBasis2d f_vv = partial_derivative(f_v, 1);

    Geom::Point dfA(f_u.apply(A[X],A[Y]),f_v.apply(A[X],A[Y]));
    Geom::Point dfB(f_u.apply(B[X],B[Y]),f_v.apply(B[X],B[Y]));

    Geom::Point V0 = rot90(dfA);
    Geom::Point V1 = rot90(dfB);
    
    double D2fVV0 = f_uu.apply(A[X],A[Y])*V0[X]*V0[X]+
                  2*f_uv.apply(A[X],A[Y])*V0[X]*V0[Y]+
                    f_vv.apply(A[X],A[Y])*V0[Y]*V0[Y];
    double D2fVV1 = f_uu.apply(B[X],B[Y])*V1[X]*V1[X]+
                  2*f_uv.apply(B[X],B[Y])*V1[X]*V1[Y]+
                    f_vv.apply(B[X],B[Y])*V1[Y]*V1[Y];

    std::vector<D2<SBasis> > candidates = cubics_fitting_curvature(A,B,V0,V1,D2fVV0,D2fVV1);
    if (candidates.empty()) {
        return D2<SBasis>(Linear(A[X],B[X]),Linear(A[Y],B[Y]));
    }
    //TODO: I'm sure std algorithm could do that for me...
    double error = -1;
    unsigned best = 0;
    for (unsigned i=0; i<candidates.size(); i++){
        Interval bounds = *bounds_fast(compose(f,candidates[i]));
        double new_error = (fabs(bounds.max())>fabs(bounds.min()) ? fabs(bounds.max()) : fabs(bounds.min()) );
        if ( new_error < error || error < 0 ){
            error = new_error;
            best = i;
        }
    }
    return candidates[best];
}