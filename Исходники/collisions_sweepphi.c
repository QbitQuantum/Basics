void collisions_search(void) {
    if (sweeps_init_done!=1) {
        sweeps_init_done = 1;
#ifdef OPENMP
        sweeps_proc 	= omp_get_max_threads();
#endif // OPENMP
        sweepphi	= (struct phivaluelist*) calloc(sweeps_proc,sizeof(struct phivaluelist));
        clist		= (struct collisionlist*)calloc(sweeps_proc,sizeof(struct collisionlist));
#ifndef TREE
        // Sort particles according to their phi position to speed up sorting of lines.
        // Initially the particles are not pre-sorted, thus qsort is faster than insertionsort.
        // Note that this rearranges particles and will cause problems if the particle id is used elsewhere.
        qsort (&(particles[N_collisions]), N-N_collisions, sizeof(struct particle), compare_particle);
    } else {
        // Keep particles sorted according to their phi position to speed up sorting of lines.
        collisions_sweep_insertionsort_particles();
#endif //TREE
    }
    for (int i=N_collisions; i<N; i++) {
        double phi  = atan2(particles[i].y,particles[i].x);
        if (phi != phi) continue;
        double r = sqrt(particles[i].x*particles[i].x + particles[i].y*particles[i].y);
        double w = (particles[i].x*particles[i].vy - particles[i].y*particles[i].vx) / r;
        if (w != w) continue;
        double oldphi = phi-0.5*dt*w-collisions_max_r/r*2.*M_PI;
        double newphi = phi+0.5*dt*w+collisions_max_r/r*2.*M_PI;
        add_to_phivlist(oldphi,newphi,i);
    }

    #pragma omp parallel for schedule (static,1)
    for (int proci=0; proci<sweeps_proc; proci++) {
        struct phivaluelist* sweepphii = &(sweepphi[proci]);
#ifdef TREE
        // Use quicksort when there is a tree. Particles are not pre-sorted.
        qsort (sweepphii->phivalues, sweepphii->N, sizeof(struct phivalue), compare_phivalue);
#else //TREE 
        // Use insertionsort when there is a tree. Particles are pre-sorted.
        collisions_sweep_insertionsort_phivaluelist(sweepphii);
#endif //TREE

        // SWEEPL: List of lines intersecting the plane.
        struct phivaluelist sweepl = {NULL,0,0};

        for (int i=0; i<sweepphii->N; i++) {
            struct phivalue phiv = sweepphii->phivalues[i];
            if (phiv.inout == 0) {
                // Add event if start of line
                if (sweepl.N>=sweepl.Nmax) {
                    sweepl.Nmax +=32;
                    sweepl.phivalues = realloc(sweepl.phivalues,sizeof(struct phivalue)*sweepl.Nmax);
                }
                sweepl.phivalues[sweepl.N] = phiv;
                // Check for collisions with other particles in SWEEPL
                for (int k=0; k<sweepl.N; k++) {
                    int p1 = phiv.pt;
                    int p2 = sweepl.phivalues[k].pt;
                    if (p1==p2) continue;
                    int gbnphi = phiv.nphi;
                    if (sweepl.phivalues[k].nphi!=0) {
                        if (sweepl.phivalues[k].nphi==phiv.nphi) continue;
                        int tmp = p1;
                        p1 = p2;
                        p2 = tmp;
                        gbnphi = sweepl.phivalues[k].nphi;
                    }
                    detect_collision_of_pair(p1,p2,proci,sweepl.phivalues[k].crossing||phiv.crossing);
                }
                sweepl.N++;
            } else {
                // Remove event if end of line
                for (int j=0; j<sweepl.N; j++) {
                    if (sweepl.phivalues[j].pt == phiv.pt) {
                        sweepl.N--;
                        sweepl.phivalues[j] = sweepl.phivalues[sweepl.N];
                        j--;
                        break;
                    }
                }
            }
        }
        free(sweepl.phivalues);
    }

}