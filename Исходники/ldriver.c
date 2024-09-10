void solution_check(central2d_t* sim)
{
    int nx = sim->nx, ny = sim->ny;
    float* u = sim->u;
    float h_sum = 0, hu_sum = 0, hv_sum = 0;
    float hmin = u[central2d_offset(sim,0,0,0)];
    float hmax = hmin;
    for (int j = 0; j < ny; ++j)
        for (int i = 0; i < nx; ++i) {
            float h = u[central2d_offset(sim,0,i,j)];
            h_sum += h;
            hu_sum += u[central2d_offset(sim,1,i,j)];
            hv_sum += u[central2d_offset(sim,2,i,j)];
            hmax = fmaxf(h, hmax);
            hmin = fminf(h, hmin);
        }
    float cell_area = sim->dx * sim->dy;
    h_sum *= cell_area;
    hu_sum *= cell_area;
    hv_sum *= cell_area;
    printf("-\n  Volume: %g\n  Momentum: (%g, %g)\n  Range: [%g, %g]\n",
           h_sum, hu_sum, hv_sum, hmin, hmax);
    assert(hmin > 0);
}