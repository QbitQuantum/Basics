static void radialBeamformSetWNG (RadialBeamform *x,  t_object *attr, int argc, t_atom *argv) {
    float max_wng,curr_lvl,next_lvl,curr_omega,next_omega,curr_slope,next_slope;
    float *shn_bpnum=sph_omega_bp[x->sh_degree];
    int n_bpnum=sph_bp_n[x->sh_degree];
    float *shn_bpden=sph_omega_bp[x->sh_degree];;
    int n_bpden=sph_bp_n[x->sh_degree];
    int knum=0;
    int kden=0;
    float one_over_dn=1.0f/x->delta_n;
    float one_over_dn0=1.0f/x->delta_n0;
    
    if ((argc<1)|(argv[0].a_type!=A_FLOAT && (argv[0].a_type!=A_LONG))) {
        post("radial_beamform~: no value given for wng");
        max_wng=20.0f;
    }
    else
        max_wng = atom_getfloat(&argv[0]);
    
    x->max_wng=max_wng;
    
    if (x->bf_mode==VELOCITY) {
        shn_bpden = sph_omega_bpd[x->sh_degree];
        n_bpden = sph_bpd_n[x->sh_degree];
    }
    
    next_slope=0.0f;
    next_omega=1000.0f;
    next_lvl=0.0f;
    
    do {
        curr_omega=next_omega;
        curr_lvl=next_lvl;
        curr_slope=next_slope;
        if ((knum<n_bpnum)&&(kden<n_bpden)) {
            if (shn_bpden[kden]*one_over_dn0>shn_bpnum[knum]*one_over_dn) {
                next_omega=shn_bpden[kden++]*one_over_dn0;
                next_slope+=6.0f;
            }
            else{
                next_omega=shn_bpnum[knum++]*one_over_dn;
                next_slope-=6.0f;
            }
        }
        else if (kden<n_bpden) {
            next_omega=shn_bpden[kden++]*one_over_dn0;
            next_slope+=6.0f;
        }
        else if (knum<n_bpnum) {
            next_omega=shn_bpnum[knum++]*one_over_dn;
            next_slope-=6.0f;
        } 
        else {
            break;
        }
        next_lvl = curr_lvl + curr_slope * (log2f(curr_omega)-log2f(next_omega));
    } while (next_lvl<max_wng);
    
    if (curr_slope>0.0f) {
        next_omega=curr_omega*pow(2.0f,(curr_lvl-max_wng)/curr_slope); 
    }
    else {
        next_omega=0;
    }
    x->omega_cutoff=next_omega;
    x->slope_cutoff=curr_slope;
    //   radialBeamformInfo(x);
}