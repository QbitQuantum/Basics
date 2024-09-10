void evolve(double *G, double *h, double *u, double g, double dx, double dt, int nBC, int n,double *nG, double *nh)
{
    //modifies nh and nG to give the new values of h and G after a single time step
    double idx = 1.0 / dx;
    double ithree = 1.0 / 3.0;
    int i = nBC - 1;

    //calculate values at right of i cell
    double hir = h[i];
    double Gir = G[i];
    double uir = u[i];

    //calculate values at left of i+1 cell
    double hip1l = h[i+1];
    double Gip1l = G[i+1];
    double uip1l = u[i+1];

    //right force

    double duer = idx*(u[i+2] - u[i+1]);
    double duel = idx*(u[i] - u[i-1]);

    double sqrtghel = sqrt(g* hir);
    double sqrtgher = sqrt(g* hip1l);

    double sl = fmin(0,fmin(uir - sqrtghel, uip1l - sqrtgher));
    double sr = fmax(0,fmax(uir + sqrtghel, uip1l + sqrtgher));

    double felh = uir*hir;
    double felG = Gir*uir + 0.5*g*hir*hir - 2*ithree*hir*hir*hir*duel*duel;
    double ferh = uip1l*hip1l;
    double ferG = Gip1l*uip1l + 0.5*g*hip1l*hip1l -2*ithree*hip1l*hip1l*hip1l*duer*duer;

    double isrmsl = 0.0;

    if(sr != sl) isrmsl = 1.0 / (sr - sl);
   
    double foh = isrmsl*(sr*felh - sl*ferh + sl*sr*(hip1l - hir));

    double foG = isrmsl*(sr*felG - sl*ferG + sl*sr*(Gip1l - Gir));

    double fih = foh;
    double fiG = foG;
    for (i = nBC ; i < n +nBC;i++)
    {
        //i right

        hir = h[i];
        Gir = G[i];
        uir = u[i];

        //i+1 left

        hip1l = h[i+1];
        Gip1l = G[i+1];
        uip1l = u[i+1];


        duer = idx*(u[i+2] - u[i+1]);
        duel = idx*(u[i] - u[i-1]);

        sqrtghel = sqrt(g*hir);
        sqrtgher = sqrt(g*hip1l);

        sl = fmin(0,fmin(uir - sqrtghel, uip1l - sqrtgher));
        sr = fmax(0,fmax(uir + sqrtghel, uip1l + sqrtgher));

        felh = uir*hir;
        felG = Gir*uir + 0.5*g*hir*hir - 2*ithree*hir*hir*hir*duel*duel;
        ferh = uip1l*hip1l;
        ferG = Gip1l*uip1l + 0.5*g*hip1l*hip1l -2*ithree*hip1l*hip1l*hip1l*duer*duer;

        isrmsl = 0.0;

        if(sr != sl) isrmsl = 1.0 / (sr - sl);
   
        foh = isrmsl*(sr*felh - sl*ferh + sl*sr*(hip1l - hir));
        foG = isrmsl*(sr*felG - sl*ferG + sl*sr*(Gip1l - Gir));

        //source term
        nh[i -nBC] = h[i] -dt*idx*(foh - fih);
        nG[i -nBC] = G[i] -dt*idx*(foG -fiG);

        fih = foh;
        fiG = foG;  
 
    }
    
   
}