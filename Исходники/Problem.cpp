  void System::Problem_generate_geometry(const int param)
  {

    const double dt_max = 1.0/64;
    scheduler = Scheduler(dt_max);

    t_end      = 2.5;
    dt_restart = 1.0/64;
    dt_snap    = 1.0/16;

    dt_restart = std::max(dt_restart, dt_max);
    dt_snap    = std::max(dt_snap,    dt_max);

#if 1
    dt_snap = dt_max;
#endif


    const int global_n = NX*NY*NZ;
    std::vector<int> n_per_element(numElements, 0);

    for (int i = 0; i < global_n; i++)
      n_per_element[i % numElements]++;

    local_n = n_per_element[thisIndex];

    ptcl_list.clear();
    ptcl_list.reserve(local_n);

    Rand48 rnd;
    rnd.srand(123 + 123*thisIndex);
    for (int i = 0; i < local_n; i++)
    {
      vec3 pos;
      pos.x = global_domain.get_rmin().x + rnd.drand() * global_domain_size.x;
      pos.y = global_domain.get_rmin().y + rnd.drand() * global_domain_size.y;
      pos.z = global_domain.get_rmin().z + rnd.drand() * global_domain_size.z;
      ptcl_list.push_back(Particle(i, thisIndex, pos));
    }

    generateGeometry_nRelax = 2;
  }