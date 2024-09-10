int main()
{

    Config cfg;
    wall_clock t;


    cfg.readFile("infiles/diamondSquareSurface.cfg");

    const Setting & root = cfg.getRoot();


    KMCDebugger_SetFilename("diamondSquareSurface");

    KMCDebugger_SetEnabledTo(getSetting<int>(root, "buildTrace") == 0 ? false : true);


    KMCSolver* solver = new KMCSolver(root);

    initialize_diamondSquareSurface(solver, root);


    t.tic();

    solver->mainloop();

    cout << "Simulation ended after " << t.toc() << " seconds" << endl;


    KMCDebugger_DumpFullTrace();

    delete solver;


    return 0;

}