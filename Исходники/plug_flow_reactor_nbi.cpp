int main( ){

    USING_NAMESPACE_ACADO

    // INTRODUCE FIXED PARAMETERS:
    // ---------------------------
    #define  v		0.1
    #define  L		1.0
    #define  Beta	0.2
    #define  Delta	0.25
    #define  E		11250.0
    #define  k0		1E+06
    #define  R		1.986
    #define  K1		250000.0
    #define  Cin	0.02
    #define  Tin	340.0


    // INTRODUCE THE VARIABLES:
    // -------------------------
    DifferentialState     x1,x2;
    Control               u    ;
    DifferentialEquation  f( 0.0, L );


    // DEFINE A DIFFERENTIAL EQUATION:
    // -------------------------------
    double Alpha, Gamma;
    Alpha = k0*exp(-E/(R*Tin));
    Gamma = E/(R*Tin);

    f << dot(x1) ==  Alpha       /v * (1.0-x1) * exp((Gamma*x2)/(1.0+x2));
    f << dot(x2) == (Alpha*Delta)/v * (1.0-x1) * exp((Gamma*x2)/(1.0+x2)) + Beta/v * (u-x2);


    // DEFINE AN OPTIMAL CONTROL PROBLEM:
    // ----------------------------------
    OCP ocp( 0.0, L, 50 );
    ocp.minimizeMayerTerm( 0, Cin*(1.0-x1)            ); // Solve conversion optimal problem
    ocp.minimizeMayerTerm( 1, (pow((Tin*x2),2.0)/K1) + 0.005*Cin*(1.0-x1) ); // Solve energy optimal problem (perturbed by small conversion cost; 
									     // otherwise the problem is ill-defined.)

    ocp.subjectTo( f );

    ocp.subjectTo( AT_START, x1 ==  0.0 );
    ocp.subjectTo( AT_START, x2 ==  0.0 );

    ocp.subjectTo(  0.0            <= x1 <=  1.0             );
    ocp.subjectTo( (280.0-Tin)/Tin <= x2 <= (400.0-Tin)/Tin  );
    ocp.subjectTo( (280.0-Tin)/Tin <= u  <= (400.0-Tin)/Tin  );


    // DEFINE A MULTI-OBJECTIVE ALGORITHM AND SOLVE THE OCP:
    // -----------------------------------------------------
    MultiObjectiveAlgorithm algorithm(ocp);

    algorithm.set( INTEGRATOR_TYPE, INT_BDF );
    algorithm.set( KKT_TOLERANCE, 1e-7 );

    algorithm.set( PARETO_FRONT_GENERATION    , PFG_NORMAL_BOUNDARY_INTERSECTION );
    algorithm.set( PARETO_FRONT_DISCRETIZATION, 11 );

    // Minimize individual objective function
    algorithm.solveSingleObjective(0);
    
    // Minimize individual objective function
    algorithm.solveSingleObjective(1);
    
    // Generate Pareto set 
    algorithm.solve();

    algorithm.getWeights("plug_flow_reactor_nbi_weights.txt");
    algorithm.getAllDifferentialStates("plug_flow_reactor_nbi_states.txt");
    algorithm.getAllControls("plug_flow_reactor_nbi_controls.txt");


    // VISUALIZE THE RESULTS IN A GNUPLOT WINDOW:
    // ------------------------------------------
    VariablesGrid paretoFront;
    algorithm.getParetoFront( paretoFront );

    GnuplotWindow window1;
    window1.addSubplot( paretoFront, "Pareto Front (conversion versus energy)", "OUTLET CONCENTRATION", "ENERGY", PM_POINTS );
    window1.plot( );


    // PRINT INFORMATION ABOUT THE ALGORITHM:
    // --------------------------------------
    algorithm.printInfo();


    // SAVE INFORMATION:
    // -----------------
    paretoFront.print();

    return 0;
}