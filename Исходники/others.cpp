void general_ewald_sum(UnitCell &uc, const Vector3d &a1, const Vector3d &a2, const Vector3d &a3, const Vector3i &Rcutoff)
{
    int N = uc.size();
    const double sigma = M_PI;

    // renormalize electron occupation
    double unrenorm_Ne = 0, Ne = 0;
    for (UnitCell::iterator it = uc.begin(); it < uc.end(); ++it) {
        unrenorm_Ne += it->ne;
        Ne += it->C;
    }
    for (UnitCell::iterator it = uc.begin(); it < uc.end(); ++it) 
        it->ne *= Ne/unrenorm_Ne;

    // get reciprocal vectors
    Vector3d b1, b2, b3;
    double uc_vol = a1.dot(a2.cross(a3));
    b1 = 2*M_PI*a2.cross(a3)/uc_vol;
    b2 = 2*M_PI*a3.cross(a1)/uc_vol;
    b3 = 2*M_PI*a1.cross(a2)/uc_vol;
    
    // Ewald sum
    double Vs, Vl;
    Vector3d k;
    for (int id = 0; id < N; ++id) {
        Vs = 0; Vl = 0;
        for (int m = -Rcutoff[0]; m < Rcutoff[0]; ++m)
            for (int n = -Rcutoff[1]; n < Rcutoff[1]; ++n)
                for (int l = -Rcutoff[2]; l < Rcutoff[2]; ++l) {
                    k = n*b1 + m*b2 + l*b3;
                    double ksquare = k.dot(k);
                    for (int i = 0; i < N; ++i) {
                        double dR = (uc[id].r - (uc[i].r + m*a1 + n*a2 + l*a3)).norm();
                        // for long-range terms
                        if ( !(m == 0 && n == 0 && l == 0) )
                            Vl += 4*M_PI/uc_vol*(uc[i].C-uc[i].ne)/ksquare * cos(k.dot(uc[id].r-uc[i].r)) * exp(-pow(sigma,2)*ksquare/2.);
                        
                        // for short-range terms
                        if ( !(m == 0 && n == 0 && l == 0 && i == id) )
                            Vs += (uc[i].C - uc[i].ne) / dR * erfc(dR/sqrt(2)/sigma);
                    }
                }
        uc[id].V = Vs + Vl - (uc[id].C - uc[id].ne)*sqrt(2/M_PI)/sigma;
    }
}