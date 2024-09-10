TEST(PressureTest, Project_Complex)
{
  glm::ivec2 size(50);

  FluidSim sim;
  sim.initialize(1.0f, size.x, size.y);
  sim.set_boundary(boundary_phi);

  AddParticles(size, sim, boundary_phi);

  sim.add_force(0.01f);

  Velocity velocity(*device, size);
  Texture solidPhi(*device, size.x, size.y, vk::Format::eR32Sfloat);
  Texture liquidPhi(*device, size.x, size.y, vk::Format::eR32Sfloat);

  BuildInputs(*device, size, sim, velocity, solidPhi, liquidPhi);

  LinearSolver::Data data(*device, size, VMA_MEMORY_USAGE_CPU_ONLY);

  std::vector<float> computedPressureData(size.x * size.y, 0.0f);
  for (std::size_t i = 0; i < computedPressureData.size(); i++)
  {
    computedPressureData[i] = (float)sim.pressure[i];
  }
  CopyFrom(data.X, computedPressureData);

  Buffer<glm::ivec2> valid(*device, size.x * size.y, VMA_MEMORY_USAGE_CPU_ONLY);

  Pressure pressure(*device, 0.01f, size, data, velocity, solidPhi, liquidPhi, valid);

  pressure.ApplyPressure();
  device->Handle().waitIdle();

  CheckVelocity(*device, size, velocity, sim);
  CheckValid(size, sim, valid);
}