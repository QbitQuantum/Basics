int main(int narg, char **args)
{
  GRID grid(DIMENSIONALITY);
  EM_FIELD myfield;
  CURRENT current;
  std::vector<SPECIE*> species;
  std::vector<SPECIE*>::const_iterator spec_iterator;
  my_rng_generator rng;

  //*******************************************BEGIN GRID DEFINITION*******************************************************

  grid.setXrange(-50.0, 0.0);
  grid.setYrange(-15.0, 15.0);
  grid.setZrange(-15, +15);

  grid.setNCells(1536, 512, 512);
  grid.setNProcsAlongY(NPROC_ALONG_Y);
  grid.setNProcsAlongZ(NPROC_ALONG_Z);

  //grid.enableStretchedGrid();
  //grid.setXandNxLeftStretchedGrid(-20.0,1000);
  //grid.setYandNyLeftStretchedGrid(-8.0,21);
  //grid.setXandNxRightStretchedGrid(20.0,1000);
  //grid.setYandNyRightStretchedGrid(8.0,21);

  grid.setBoundaries(xOpen | yPBC | zPBC);
  grid.mpi_grid_initialize(&narg, args);
  grid.setCourantFactor(0.98);

  grid.setSimulationTime(100.0);

  grid.withParticles = YES;//NO;
  grid.withCurrent = YES;//YES;

  grid.setStartMovingWindow(0);
  //grid.setBetaMovingWindow(1.0);
  //grid.setFrequencyMovingWindow(20);

  grid.setMasterProc(0);

  srand(time(NULL));
  grid.initRNG(rng, RANDOM_NUMBER_GENERATOR_SEED);

  grid.finalize();

  grid.visualDiag();

  //********************************************END GRID DEFINITION********************************************************

  //*******************************************BEGIN FIELD DEFINITION*********************************************************
  myfield.allocate(&grid);
  myfield.setAllValuesToZero();

  laserPulse pulse1;
  pulse1.setGaussianPulse();
  pulse1.setWaist(4.0);
  pulse1.setDurationFWHM(10.0);
  pulse1.setNormalizedAmplitude(0.5);
  pulse1.setCircularPolarization();
  pulse1.setPulseInitialPosition(-10.1);
  pulse1.setFocusPosition(0.0);
  pulse1.setLambda(1.0);
  pulse1.setFocusPosition(0.0);
  //    pulse1.setRotationAngleAndCenter(2.0*M_PI*(-30.0 / 360.0), 0.0);
  myfield.addPulse(&pulse1);

  myfield.boundary_conditions();

  current.allocate(&grid);
  current.setAllValuesToZero();
  //*******************************************END FIELD DEFINITION***********************************************************

  //*******************************************BEGIN SPECIES DEFINITION*********************************************************
  PLASMA plasma1;
  plasma1.density_function = box;
  plasma1.setXRangeBox(0.0, 100.0);
  plasma1.setYRangeBox(grid.rmin[1], grid.rmax[1]);
  plasma1.setZRangeBox(grid.rmin[2], grid.rmax[2]);
  plasma1.setDensityCoefficient(0.0025);

  SPECIE  electrons1(&grid);
  electrons1.plasma = plasma1;
  electrons1.setParticlesPerCellXYZ(1, 2, 2);
  electrons1.setName("ELE1");
  electrons1.type = ELECTRON;
  electrons1.creation();
  species.push_back(&electrons1);


  SPECIE ions1(&grid);
  ions1.plasma = plasma1;
  ions1.setParticlesPerCellXYZ(1, 2, 2);
  ions1.setName("ION1");
  ions1.type = ION;
  ions1.Z = 6.0;
  ions1.A = 12.0;
  //ions1.creation();
  //species.push_back(&ions1);


  //tempDistrib distribution;
  //distribution.setWaterbag(1.0e-8);
  //electrons1.add_momenta(rng,0.0,0.0,0.0,distribution);
  //ions1.add_momenta(rng,0.0, 0.0, 0.0, distribution);

  for (spec_iterator = species.begin(); spec_iterator != species.end(); spec_iterator++) {
    (*spec_iterator)->printParticleNumber();
  }

  //*******************************************END SPECIED DEFINITION***********************************************************

  //*******************************************BEGIN DIAGNOSTICS DEFINITION**************************************************
  OUTPUT_MANAGER manager(&grid, &myfield, &current, species);

  //manager.addEBFieldFrom(0.0,20.0);
  //manager.addSpeciesDensityFrom(electrons1.name, 0.0, 20.0);
  //manager.addSpeciesPhaseSpaceFrom(electrons1.name, 0.0, 10.0);
  //manager.addSpeciesDensityFrom(ions1.name, 0.0, 1.0);
  //manager.addDiagFrom(0.0, 1.0);

  manager.initialize(DIRECTORY_OUTPUT);
  //*******************************************END DIAGNOSTICS DEFINITION**************************************************
  grid.setDumpPath(DIRECTORY_DUMP);
  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ MAIN CYCLE (DO NOT MODIFY!!) @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  if (grid.myid == grid.master_proc) {
    printf("----- START temporal cicle -----\n");
    fflush(stdout);
  }

  int Nstep = grid.getTotalNumberOfTimesteps();
  int dumpID = 1, dumpEvery;
  if (DO_DUMP) {
    dumpEvery = (int)(TIME_BTW_DUMP / grid.dt);
  }
  grid.istep = 0;
  if (_DO_RESTART) {
    dumpID = _RESTART_FROM_DUMP;
    restartFromDump(&dumpID, &grid, &myfield, species);
  }
  while (grid.istep <= Nstep)
  {

    grid.printTStepEvery(FREQUENCY_STDOUT_STATUS);

    manager.callDiags(grid.istep);

    myfield.openBoundariesE_1();
    myfield.new_halfadvance_B();
    myfield.boundary_conditions();

    current.setAllValuesToZero();
    for (spec_iterator = species.begin(); spec_iterator != species.end(); spec_iterator++) {
      (*spec_iterator)->current_deposition_standard(&current);
    }
    current.pbc();

    for (spec_iterator = species.begin(); spec_iterator != species.end(); spec_iterator++) {
      (*spec_iterator)->position_parallel_pbc();
    }

    myfield.openBoundariesB();
    myfield.new_advance_E(&current);

    myfield.boundary_conditions();
    myfield.openBoundariesE_2();
    myfield.new_halfadvance_B();
    myfield.boundary_conditions();

    for (spec_iterator = species.begin(); spec_iterator != species.end(); spec_iterator++) {
      (*spec_iterator)->momenta_advance(&myfield);
    }

    grid.time += grid.dt;

    moveWindow(&grid, &myfield, species);

    grid.istep++;
    if (DO_DUMP) {
      if (grid.istep != 0 && !(grid.istep % (dumpEvery))) {
        dumpFilesForRestart(&dumpID, &grid, &myfield, species);
      }
    }
  }

  manager.close();
  MPI_Finalize();
  exit(1);

}