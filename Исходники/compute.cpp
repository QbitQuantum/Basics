// Given the solution of the equation up to the time step solution.timestep - 1, computes the solution at the sime step solution.timestep and increases timestep by one
void step(double * data, Solution & solution, const SimulationContext & context, const vector<shared_ptr<SimulationResult>> & results)
{
    // The equation is result = (2-Re dt)^(-1) (2 + Re dt) se + (2-Re dt)^(-1) G s

    // Total Spin
    Vector4d s = 0.5*(3.0*solution.current.total.spin - solution.previous.total.spin);

    // Aliases
    const Settings & settings = context.settings();
    double dt = data[Index::Duration] / data[Index::TimestepCount];

    data[Index::Timestep]   = solution.timeStep;
    data[Index::Time]       = solution.timeStep * data[Index::Duration] / data[Index::TimestepCount];

    context.evaluateFunctions(ComputeFor::Step, Compute::OnceForEachStep, data);

    // test
    double h = accumulate(solution.current.spin.begin(), solution.current.spin.end(), 0.0, [](double old, const Vector4d & s) {return old + abs(s(2));}) / solution.current.spin.size();
    (void)h;

    // Solving the equation of motion for the individual spins
    for(unsigned int i = 0; i < settings.energySamples().size(); ++i) {
        Vector4d & spin = solution.current.spin.at(i);

        data[Index::EnergyIndex] = i;
        data[Index::Energy] = settings.energySamples().at(i);

        context.evaluateFunctions(ComputeFor::Step, Compute::OnceForEachEnergy, data);

        // Matrix initialization
        Matrix4d R, RD;
        // R = RF + RE + RD + RL;

        // Pseudo magnetic field
        /* 0,                      -data[Index::Frequency],    0, 0,
         * data[Index::Frequency],  0,                         0, 0,
         * 0,                       0,                         0, 0,
         * 0,                       0,                         0, 0;
         */

        R.setZero();
        R(0,1) += -data[Index::Frequency];
        R(1,0) += +data[Index::Frequency];

        // Exchange
        /*  0,                                 -data[Index::Exchange]*s(2)*s(3),    data[Index::Exchange]*s(1)*s(3),   0,
         *  data[Index::Exchange]*s(2)*s(3),    0,                                 -data[Index::Exchange]*s(0)*s(3),   0,
         * -data[Index::Exchange]*s(1)*s(3),    data[Index::Exchange]*s(0)*s(3),    0,                                 0,
         *  0,                                  0,                                  0,                                 0;
         */
        R(0,1) += -data[Index::Exchange]*s(2)*s(3);
        R(0,2) += +data[Index::Exchange]*s(1)*s(3);
        R(1,0) += +data[Index::Exchange]*s(2)*s(3);
        R(1,2) += -data[Index::Exchange]*s(0)*s(3);
        R(2,0) += -data[Index::Exchange]*s(1)*s(3);
        R(2,1) += +data[Index::Exchange]*s(0)*s(3);

        // Damping
        /* -data[Index::Damping],  0,                       0,                     0,
         *  0,                    -data[Index::Damping],    0,                     0,
         *  0,                     0,                      -data[Index::Damping],  0,
         *  0,                     0,                       0,                     0;
         */
        RD.setZero();
        RD(0,0) += -data[Index::Damping];
        RD(1,1) += -data[Index::Damping];
        RD(2,2) += -data[Index::Damping];

        R += RD;

        // Atom losses
        double dfls = 0.25 * (data[Index::AtomLossFromF1] + data[Index::AtomLossFromF2]);    // Total atom losses to spectator states
        double dfld = 0.25 * (data[Index::AtomLossFromF1] - data[Index::AtomLossFromF2]);    // Difference of atom losses to spectator states
        /* 0, 0,  0,                        0,
         * 0, 0,  0,                        0,
         * 0, 0, -(dfls*s(3) + dfld*s(2)), -(dfld*s(3) + dfls*s(2)),
         * 0, 0, -(dfld*s(3) + dfls*s(2)), -(dfls*s(3) + dfld*s(2));*/
        R(2,2) += -(dfls*s(3) + dfld*s(2));
        R(2,3) += -(dfld*s(3) + dfls*s(2));
        R(3,2) += -(dfld*s(3) + dfls*s(2));
        R(3,3) += -(dfls*s(3) + dfld*s(2));

        // Computation

        Matrix4d RT; // = 2 + R * dt
        Matrix4d RI; // = (2 - R * dt).inverse();

        // We can't inverse in place, so we use RT as a temporary to compute RI
        RT = 2.0 * Matrix4d::Identity() - dt * R;
        RI = RT.inverse();
        RT = 2.0 * Matrix4d::Identity() + dt * R;

        spin = RI * (RT * spin - dt * RD * s).eval();
    }

    // Update values at the previous timestep
    solution.previous.total.spin = solution.current.total.spin;
    solution.previous.total.phase = solution.current.total.phase;

    for(unsigned int i = 0; i < settings.energyBins().size(); ++i) {
        solution.previous.partial(i).phase = solution.current.partial(i).phase;
    }

    // Update current values
    solution.current.total.spin = accumulate(solution.current.spin.begin(), solution.current.spin.end(), Vector4d::Zero().eval()) / solution.current.spin.size();

    // TODO : Move inside the loop
    solution.current.total.atomLosses(1) += dt * data[Index::AtomLossFromF1]* 0.5 * (s(3) + s(2));
    solution.current.total.atomLosses(2) += dt * data[Index::AtomLossFromF2]* 0.5 * (s(3) - s(2));

    // Partial spins
    for(unsigned int i = 0; i < settings.energyBins().size(); ++i) {
        const Settings::EnergyBin & bin = settings.energyBins().at(i);
        solution.current.partial(i).spin = accumulate(solution.current.spin.begin() + bin.first, solution.current.spin.begin() + bin.second, Vector4d::Zero().eval()) / (bin.second - bin.first);
    }

    // Computes the phase of the spins
    phase(solution, settings);

    // Save the data if necessary
    save(data, solution, settings, results);

    ++solution.timeStep;
}