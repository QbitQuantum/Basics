void test_flowsolver(const GI& g, const RI& r, double tol, int kind)
{
    typedef typename GI::CellIterator                   CI;
    typedef typename CI::FaceIterator                   FI;
    typedef double (*SolutionFuncPtr)(const Vec&);

    //typedef Opm::BasicBoundaryConditions<true, false>  FBC;
    typedef Opm::FunctionBoundaryConditions<SolutionFuncPtr> FBC;
    typedef Opm::IncompFlowSolverHybrid<GI, RI, FBC,
        Opm::MimeticIPEvaluator> FlowSolver;

    FlowSolver solver;

    // FBC flow_bc;
    // assign_bc(g, flow_bc);
    FBC flow_bc(&u);

    typename CI::Vector gravity(0.0);

    std::cout << "========== Init pressure solver =============" << std::endl;
    Opm::time::StopWatch rolex;
    rolex.start();
    solver.init(g, r, gravity, flow_bc);
    rolex.stop();
    std::cout << "========== Time in seconds: " << rolex.secsSinceStart() << " =============" << std::endl;

    std::vector<double> src(g.numberOfCells(), 0.0);
    assign_src(g, src);
    std::vector<double> sat(g.numberOfCells(), 0.0);


    std::cout << "========== Starting pressure solve =============" << std::endl;
    rolex.start();
    solver.solve(r, sat, flow_bc, src, tol, 3, kind);
    rolex.stop();
    std::cout << "========== Time in seconds: " << rolex.secsSinceStart() << " =============" << std::endl;

    typedef typename FlowSolver::SolutionType FlowSolution;
    FlowSolution soln = solver.getSolution();

    std::vector<typename GI::Vector> cell_velocity;
    estimateCellVelocity(cell_velocity, g, solver.getSolution());
    // Dune's vtk writer wants multi-component data to be flattened.
    std::vector<double> cell_velocity_flat(&*cell_velocity.front().begin(),
                                           &*cell_velocity.back().end());
    std::vector<double> cell_pressure;
    getCellPressure(cell_pressure, g, soln);

    compare_pressure(g, cell_pressure);

    Dune::VTKWriter<typename GI::GridType::LeafGridView> vtkwriter(g.grid().leafView());
    vtkwriter.addCellData(cell_velocity_flat, "velocity", GI::GridType::dimension);
    vtkwriter.addCellData(cell_pressure, "pressure");
    vtkwriter.write("testsolution-" + boost::lexical_cast<std::string>(0),
                    Dune::VTKOptions::ascii);
}