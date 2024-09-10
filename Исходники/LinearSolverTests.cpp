TEST(LinearSolverTests, Multigrid_Simple_PCG)
{
  glm::ivec2 size(64);

  FluidSim sim;
  sim.initialize(1.0f, size.x, size.y);
  sim.set_boundary(boundary_phi);

  AddParticles(size, sim, boundary_phi);

  sim.add_force(0.01f);
  sim.compute_phi();
  sim.extrapolate_phi();
  sim.apply_projection(0.01f);

  LinearSolver::Data data(*device, size, VMA_MEMORY_USAGE_CPU_ONLY);

  Velocity velocity(*device, size);
  Texture liquidPhi(*device, size.x, size.y, vk::Format::eR32Sfloat);
  Texture solidPhi(*device, size.x, size.y, vk::Format::eR32Sfloat);
  Buffer<glm::ivec2> valid(*device, size.x * size.y, VMA_MEMORY_USAGE_CPU_ONLY);

  SetSolidPhi(*device, size, solidPhi, sim, (float)size.x);
  SetLiquidPhi(*device, size, liquidPhi, sim, (float)size.x);

  BuildLinearEquation(size, data.Diagonal, data.Lower, data.B, sim);

  Pressure pressure(*device, 0.01f, size, data, velocity, solidPhi, liquidPhi, valid);

  Multigrid preconditioner(*device, size, 0.01f);
  preconditioner.BuildHierarchiesBind(pressure, solidPhi, liquidPhi);

  LinearSolver::Parameters params(LinearSolver::Parameters::SolverType::Iterative, 1000, 1e-5f);
  ConjugateGradient solver(*device, size, preconditioner);

  solver.Bind(data.Diagonal, data.Lower, data.B, data.X);

  preconditioner.BuildHierarchies();
  solver.Solve(params);

  device->Queue().waitIdle();

  CheckPressure(size, sim.pressure, data.X, 1e-5f);

  std::cout << "Solved with number of iterations: " << params.OutIterations << std::endl;
}