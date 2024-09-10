int main()
{

    Config cfg;

    cfg.readFile("infiles/WLMC.cfg");

    const Setting & root = cfg.getRoot();

    KMCDebugger_SetEnabledTo(false);

    KMCSolver::enableDumpLAMMPS(false);
    KMCSolver::enableDumpXYZ(false);
    MainLattice::enableEventFile(false);

    KMCSolver* solver = new KMCSolver(root);

    initializeWLMC(solver, root);

    return 0;

}