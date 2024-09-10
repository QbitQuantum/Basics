SimulationBar::SimulationBar()
    : ToolBar(N_("SimulationBar"))
{
    using boost::bind;

    setVisibleByDefault(true);    
    
    addButton(QIcon(":/Body/icons/store-world-initial.png"),
              _("Store body positions to the initial world state"))->
        sigClicked().connect(bind(&SimulationBar::onStoreInitialClicked, this));
    
    addButton(QIcon(":/Body/icons/restore-world-initial.png"),
              _("Restore body positions from the initial world state"))->
        sigClicked().connect(bind(&SimulationBar::onRestoreInitialClicked, this));

    typedef boost::function<void(SimulatorItem* simulator)> Callback;

    addButton(QIcon(":/Body/icons/start-simulation.png"), _("Start simulation from the beginning"))->
        sigClicked().connect(bind(&SimulationBar::startSimulation, this, true));

    addButton(QIcon(":/Body/icons/restart-simulation.png"),
              _("Start simulation from the current state"))->
        sigClicked().connect(bind(&SimulationBar::startSimulation, this, false));
    
    addButton(QIcon(":/Body/icons/stop-simulation.png"), _("Stop simulation"))->
        sigClicked().connect(bind(&SimulationBar::onStopSimulationClicked, this));
}