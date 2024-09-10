void InterfaceParticles::ExportSolution(Grid& grid)
{
  Index i;

#ifdef OUTPUT_DEBUG
  vmg_float e = 0.0;
  vmg_float e_long = 0.0;
  vmg_float e_self = 0.0;
  vmg_float e_short_peak = 0.0;
  vmg_float e_short_spline = 0.0;
#endif

  Factory& factory = MG::GetFactory();
  Particle::CommMPI& comm = *dynamic_cast<Particle::CommMPI*>(MG::GetComm());

  /*
   * Get parameters and arrays
   */
  const vmg_int& near_field_cells = factory.GetObjectStorageVal<int>("PARTICLE_NEAR_FIELD_CELLS");
  const vmg_int& interpolation_degree = factory.GetObjectStorageVal<int>("PARTICLE_INTERPOLATION_DEGREE");

  Particle::Interpolation ip(interpolation_degree);

  const vmg_float r_cut = near_field_cells * grid.Extent().MeshWidth().Max();

  /*
   * Copy potential values to a grid with sufficiently large halo size.
   * This may be optimized in future.
   * The parameters of this grid have been set in the import step.
   */
  Grid& particle_grid = comm.GetParticleGrid();

  for (i.X()=0; i.X()<grid.Local().Size().X(); ++i.X())
    for (i.Y()=0; i.Y()<grid.Local().Size().Y(); ++i.Y())
      for (i.Z()=0; i.Z()<grid.Local().Size().Z(); ++i.Z())
        particle_grid(i + particle_grid.Local().Begin()) = grid.GetVal(i + grid.Local().Begin());

  comm.CommToGhosts(particle_grid);

  /*
   * Compute potentials
   */
  Particle::LinkedCellList lc(particles, near_field_cells, grid);
  Particle::LinkedCellList::iterator p1, p2;
  Grid::iterator iter;

  comm.CommLCListToGhosts(lc);

  for (int i=lc.Local().Begin().X(); i<lc.Local().End().X(); ++i)
    for (int j=lc.Local().Begin().Y(); j<lc.Local().End().Y(); ++j)
      for (int k=lc.Local().Begin().Z(); k<lc.Local().End().Z(); ++k) {

	if (lc(i,j,k).size() > 0)
	  ip.ComputeCoefficients(particle_grid, Index(i,j,k) - lc.Local().Begin() + particle_grid.Local().Begin());

	for (p1=lc(i,j,k).begin(); p1!=lc(i,j,k).end(); ++p1) {

	  // Interpolate long-range part of potential and electric field
	  ip.Evaluate(**p1);

	  // Subtract self-induced potential
	  (*p1)->Pot() -= (*p1)->Charge() * spl.GetAntiDerivativeAtZero();

#ifdef OUTPUT_DEBUG
	  e_long += 0.5 * (*p1)->Charge() * ip.EvaluatePotentialLR(**p1);
	  e_self += 0.5 * (*p1)->Charge() * (*p1)->Charge() * spl.GetAntiDerivativeAtZero();
#endif

	  for (int dx=-1*near_field_cells; dx<=near_field_cells; ++dx)
	    for (int dy=-1*near_field_cells; dy<=near_field_cells; ++dy)
	      for (int dz=-1*near_field_cells; dz<=near_field_cells; ++dz) {

		for (p2=lc(i+dx,j+dy,k+dz).begin(); p2!=lc(i+dx,j+dy,k+dz).end(); ++p2)

		  if (*p1 != *p2) {

		    const Vector dir = (*p1)->Pos() - (*p2)->Pos();
		    const vmg_float length = dir.Length();

		    if (length < r_cut) {

		      (*p1)->Pot() += (*p2)->Charge() / length * (1.0 + spl.EvaluatePotential(length));
		      (*p1)->Field() += (*p2)->Charge() * dir * spl.EvaluateField(length);

#ifdef OUTPUT_DEBUG
		      e_short_peak += 0.5 * (*p1)->Charge() * (*p2)->Charge() / length;
		      e_short_spline += 0.5 * (*p1)->Charge() * (*p2)->Charge() / length * spl.EvaluatePotential(length);
#endif
		    }
		  }
	      }
	}
      }

  /* Remove average force term */
  Vector average_force = 0.0;
  for (std::list<Particle::Particle>::const_iterator iter=particles.begin(); iter!=particles.end(); ++iter)
    average_force += iter->Charge() * iter->Field();
  const vmg_int& npl = MG::GetFactory().GetObjectStorageVal<vmg_int>("PARTICLE_NUM_LOCAL");
  const vmg_int num_particles_global = comm.GlobalSum(npl);
  average_force /= num_particles_global;
  comm.GlobalSumArray(average_force.vec(), 3);
  for (std::list<Particle::Particle>::iterator iter=particles.begin(); iter!=particles.end(); ++iter)
    iter->Field() -= average_force / iter->Charge();

  comm.CommParticlesBack(particles);

#ifdef OUTPUT_DEBUG
  vmg_float* q = factory.GetObjectStorageArray<vmg_float>("PARTICLE_CHARGE_ARRAY");
  const vmg_int& num_particles_local = factory.GetObjectStorageVal<vmg_int>("PARTICLE_NUM_LOCAL");
  const vmg_float* p = factory.GetObjectStorageArray<vmg_float>("PARTICLE_POTENTIAL_ARRAY");
  const vmg_float* f = factory.GetObjectStorageArray<vmg_float>("PARTICLE_FIELD_ARRAY");


  e_long = comm.GlobalSumRoot(e_long);
  e_short_peak = comm.GlobalSumRoot(e_short_peak);
  e_short_spline = comm.GlobalSumRoot(e_short_spline);
  e_self = comm.GlobalSumRoot(e_self);

  for (int j=0; j<num_particles_local; ++j)
    e += 0.5 * p[j] * q[j];
  e = comm.GlobalSumRoot(e);

  comm.PrintOnce(Debug, "E_long:         %e", e_long);
  comm.PrintOnce(Debug, "E_short_peak:   %e", e_short_peak);
  comm.PrintOnce(Debug, "E_short_spline: %e", e_short_spline);
  comm.PrintOnce(Debug, "E_self:         %e", e_self);
  comm.PrintOnce(Debug, "E_total:        %e", e);
  comm.PrintOnce(Debug, "E_total*:       %e", e_long + e_short_peak + e_short_spline - e_self);
#endif
}