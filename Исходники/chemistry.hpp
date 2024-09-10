geom::FieldCell<Scal> CalcRadiationField(
    const Mesh& mesh,
    const geom::MapFace<std::shared_ptr<solver::ConditionFace>>&
    mf_cond_radiation_shared,
    const geom::FieldCell<Scal>& fc_absorption_rate,
    Vect radiation_direction,
    geom::FieldCell<Scal> initial_guess) {

  if (radiation_direction.norm() == 0.) {
    return initial_guess;
  }

  radiation_direction /= radiation_direction.norm();

  geom::FieldFace<Scal> ff_flux(mesh);
  for (auto idxface : mesh.Faces()) {
    ff_flux[idxface] =
        radiation_direction.dot(mesh.GetSurface(idxface));
  }

  Scal time_step = 1e16;
  for (auto idxcell : mesh.Cells()) {
    for (size_t i = 0; i < mesh.GetNumNeighbourFaces(idxcell); ++i) {
      auto idxface = mesh.GetNeighbourFace(idxcell, i);
      Vect vect = mesh.GetCenter(idxcell) - mesh.GetCenter(idxface);
      Scal vel_dot_vect = std::abs(radiation_direction.dot(vect));
      if (vel_dot_vect != 0.) {
        time_step = std::min(time_step, vect.sqrnorm() / vel_dot_vect);
      }
    }
  }

  geom::FieldCell<Scal> fc_source(mesh, 0.);

  solver::AdvectionSolverExplicit<Mesh, geom::FieldFace<Scal>>
  advection(
      mesh, initial_guess, mf_cond_radiation_shared, &ff_flux,
      &fc_source, 0., time_step);

  Scal error = 1e16;
  size_t count = 0;
  for (; count < 10 && error > 1e-3; ++count) {
    for (auto idxcell : mesh.Cells()) {
      fc_source[idxcell] =
          -fc_absorption_rate[idxcell] * advection.GetField()[idxcell];
    }
    advection.StartStep();
    advection.MakeIteration();
    error = advection.GetConvergenceIndicator();
    advection.FinishStep();
  }
  return advection.GetField();
}