void sph_simulation::load_settings(std::string fluid_file_name,
                                   std::string parameters_file_name) {
  int particles_inside_influence_radius = 0;

  {
    picojson::value fluid_params;
    std::ifstream fluid_stream(fluid_file_name);
    fluid_stream >> fluid_params;

    parameters.fluid_density =
        (float)(fluid_params.get<picojson::object>()["fluid_density"]
                    .get<double>());
    parameters.dynamic_viscosity =
        (float)(fluid_params.get<picojson::object>()["dynamic_viscosity"]
                    .get<double>());
    parameters.restitution =
        (float)(fluid_params.get<picojson::object>()["restitution"]
                    .get<double>());
    if (parameters.restitution < 0 || parameters.restitution > 1) {
      throw std::runtime_error("Restitution has an invalid value!");
    }

    parameters.K =
        (float)(fluid_params.get<picojson::object>()["k"].get<double>());
    parameters.surface_tension_threshold =
        (float)(fluid_params
                    .get<picojson::object>()["surface_tension_threshold"]
                    .get<double>());
    parameters.surface_tension =
        (float)(fluid_params.get<picojson::object>()["surface_tension"]
                    .get<double>());
    particles_inside_influence_radius =
        (int)(fluid_params
                  .get<picojson::object>()["particles_inside_influence_radius"]
                  .get<double>());
  }

  {
    picojson::value sim_params;
    std::ifstream sim_stream(parameters_file_name);
    sim_stream >> sim_params;

    parameters.particles_count =
        (unsigned int)(sim_params.get<picojson::object>()["particles_count"]
                           .get<double>());

    if (parameters.particles_count % kPreferredWorkGroupSizeMultiple != 0) {
      std::cout << std::endl
                << "\033[1;31m You should choose a number of particles that is "
                   "divisble by the preferred work group size.\033[0m";
      std::cout << std::endl
                << "\033[1;31m Performances will be sub-optimal.\033[0m"
                << std::endl;
    }

    parameters.particle_mass =
        (float)(sim_params.get<picojson::object>()["particle_mass"]
                    .get<double>());
    parameters.simulation_time =
        (float)(sim_params.get<picojson::object>()["simulation_time"]
                    .get<double>());
    parameters.target_fps =
        (float)(sim_params.get<picojson::object>()["target_fps"].get<double>());
    parameters.simulation_scale =
        (float)(sim_params.get<picojson::object>()["simulation_scale"]
                    .get<double>());

    parameters.constant_acceleration.s[0] =
        (float)(sim_params.get<picojson::object>()["constant_acceleration"]
                    .get<picojson::object>()["x"]
                    .get<double>());
    parameters.constant_acceleration.s[1] =
        (float)(sim_params.get<picojson::object>()["constant_acceleration"]
                    .get<picojson::object>()["y"]
                    .get<double>());
    parameters.constant_acceleration.s[2] =
        (float)(sim_params.get<picojson::object>()["constant_acceleration"]
                    .get<picojson::object>()["z"]
                    .get<double>());

    write_intermediate_frames =
        sim_params.get<picojson::object>()["write_all_frames"].get<bool>();
    serialize = sim_params.get<picojson::object>()["serialize"].get<bool>();
  }

  parameters.total_mass = parameters.particles_count * parameters.particle_mass;
  initial_volume = parameters.total_mass / parameters.fluid_density;
  parameters.h = cbrtf(3.f * (particles_inside_influence_radius *
                              (initial_volume / parameters.particles_count)) /
                       (4.f * M_PI));
  parameters.time_delta = 1.f / parameters.target_fps;

  parameters.max_velocity = 0.8f * parameters.h / parameters.time_delta;

  precomputed_terms.poly_6 = 315.f / (64.f * M_PI * pow(parameters.h, 9.f));
  precomputed_terms.poly_6_gradient =
      -945.f / (32.f * M_PI * pow(parameters.h, 9.f));
  precomputed_terms.poly_6_laplacian =
      -945.f / (32.f * M_PI * pow(parameters.h, 9.f));
  precomputed_terms.spiky = -45.f / (M_PI * pow(parameters.h, 6.f));
  precomputed_terms.viscosity = 45.f / (M_PI * pow(parameters.h, 6.f));
}