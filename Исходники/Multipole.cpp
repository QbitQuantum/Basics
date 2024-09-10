void MultipoleExpansion::fill_radial_grid(double aa0, double rrmin, double rrmax){
    // if loggrid use logarithmic grid else sinh
    a0 = aa0; rmax = rrmax; rmin = rrmin;
    double dmin = asinh(rmin/a0);
    double ra = asinh(rmax/a0)-dmin;
    if(loggrid){
        dmin = log(rmin/a0);
        ra = log(rmax/rmin);
    }
    for(int i=0;i<NR;i++){
        delta_grid.push_back(i*ra/(double)(NR-1)+dmin);
        if(loggrid)
            radial_grid.push_back(a0*exp(delta_grid[i]));
        else
            radial_grid.push_back(a0*sinh(delta_grid[i]));
    }
}