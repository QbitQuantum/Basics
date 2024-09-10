static void add_top_tbl(struct All_variables *E, double age_in_myrs, double mantle_temp)
{
    int m, i, j, k, node;
    int nox, noy, noz;
    double r1, dT, tmp;

    nox = E->lmesh.nox;
    noy = E->lmesh.noy;
    noz = E->lmesh.noz;

    dT = (mantle_temp - E->control.TBCtopval);
    tmp = 0.5 / sqrt(age_in_myrs / E->data.scalet);

    fprintf(stderr, "%e %e\n", dT, tmp);
    for(m=1; m<=E->sphere.caps_per_proc; m++)
        for(i=1; i<=noy; i++)
            for(j=1; j<=nox;j ++)
                for(k=1; k<=noz; k++) {
                    node = k + (j-1)*noz + (i-1)*nox*noz;
                    r1 = E->sx[m][3][node];
                    E->T[m][node] -= dT * erfc(tmp * (E->sphere.ro - r1));
                }

    return;
}