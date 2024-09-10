int main(int argc, char** argv)
{
  bool fixLaser;
  int maxIterations;
  bool verbose;
  string inputFilename;
  string outputfilename;
  string rawFilename;
  string odomTestFilename;
  string dumpGraphFilename;
  // command line parsing
  CommandArgs commandLineArguments;
  commandLineArguments.param("i", maxIterations, 10, "perform n iterations");
  commandLineArguments.param("v", verbose, false, "verbose output of the optimization process");
  commandLineArguments.param("o", outputfilename, "", "output final version of the graph");
  commandLineArguments.param("test", odomTestFilename, "", "apply odometry calibration to some test data");
  commandLineArguments.param("dump", dumpGraphFilename, "", "write the graph to the disk");
  commandLineArguments.param("fixLaser", fixLaser, false, "keep the laser offset fixed during optimization");
  commandLineArguments.paramLeftOver("gm2dl-input", inputFilename, "", "gm2dl file which will be processed");
  commandLineArguments.paramLeftOver("raw-log", rawFilename, "", "raw log file containing the odometry");

  commandLineArguments.parseArgs(argc, argv);

  SparseOptimizer optimizer;
  optimizer.setVerbose(verbose);
  optimizer.setForceStopFlag(&hasToStop);

  allocateSolverForSclam(optimizer);

  // loading
  if (! Gm2dlIO::readGm2dl(inputFilename, optimizer, false)) {
    cerr << "Error while loading gm2dl file" << endl;
  }
  DataQueue robotLaserQueue;
  int numLaserOdom = Gm2dlIO::readRobotLaser(rawFilename, robotLaserQueue);
  if (numLaserOdom == 0) {
    cerr << "No raw information read" << endl;
    return 0;
  }
  cerr << "Read " << numLaserOdom << " laser readings from file" << endl;

  bool gaugeFreedom = optimizer.gaugeFreedom();

  OptimizableGraph::Vertex* gauge = optimizer.findGauge();
  if (gaugeFreedom) {
    if (! gauge) {
      cerr <<  "# cannot find a vertex to fix in this thing" << endl;
      return 2;
    } else {
      cerr << "# graph is fixed by node " << gauge->id() << endl;
      gauge->setFixed(true);
    }
  } else {
    cerr << "# graph is fixed by priors" << endl;
  }

  addOdometryCalibLinksDifferential(optimizer, robotLaserQueue);

  // sanity check
  HyperDijkstra d(&optimizer);
  UniformCostFunction f;
  d.shortestPaths(gauge, &f);
  //cerr << PVAR(d.visited().size()) << endl;

  if (d.visited().size()!=optimizer.vertices().size()) {
    cerr << CL_RED("Warning: d.visited().size() != optimizer.vertices().size()") << endl;
    cerr << "visited: " << d.visited().size() << endl;
    cerr << "vertices: " << optimizer.vertices().size() << endl;
    if (1)
      for (SparseOptimizer::VertexIDMap::const_iterator it = optimizer.vertices().begin(); it != optimizer.vertices().end(); ++it) {
        OptimizableGraph::Vertex* v = static_cast<OptimizableGraph::Vertex*>(it->second);
        if (d.visited().count(v) == 0) {
          cerr << "\t unvisited vertex " << it->first << " " << (void*)v << endl;
          v->setFixed(true);
        }
      }
  }

  for (SparseOptimizer::VertexIDMap::const_iterator it = optimizer.vertices().begin(); it != optimizer.vertices().end(); ++it) {
    OptimizableGraph::Vertex* v = static_cast<OptimizableGraph::Vertex*>(it->second);
    if (v->fixed()) {
      cerr << "\t fixed vertex " << it->first << endl;
    }
  }

  VertexSE2* laserOffset = dynamic_cast<VertexSE2*>(optimizer.vertex(Gm2dlIO::ID_LASERPOSE));
  VertexOdomDifferentialParams* odomParamsVertex = dynamic_cast<VertexOdomDifferentialParams*>(optimizer.vertex(Gm2dlIO::ID_ODOMCALIB));

  if (fixLaser) {
    cerr << "Fix position of the laser offset" << endl;
    laserOffset->setFixed(true);
  }

  signal(SIGINT, sigquit_handler);
  cerr << "Doing full estimation" << endl;
  optimizer.initializeOptimization();
  optimizer.computeActiveErrors();
  cerr << "Initial chi2 = " << FIXED(optimizer.chi2()) << endl;

  int i=optimizer.optimize(maxIterations);
  if (maxIterations > 0 && !i){
    cerr << "optimize failed, result might be invalid" << endl;
  }

  if (laserOffset) {
    cerr << "Calibrated laser offset (x, y, theta):" << laserOffset->estimate().toVector().transpose() << endl;
  }

  if (odomParamsVertex) {
    cerr << "Odometry parameters (scaling factors (v_l, v_r, b)): " << odomParamsVertex->estimate().transpose() << endl;
  }

  cerr << "vertices: " << optimizer.vertices().size() << endl;
  cerr << "edges: " << optimizer.edges().size() << endl;

  if (dumpGraphFilename.size() > 0) {
    cerr << "Writing " << dumpGraphFilename << " ... ";
    optimizer.save(dumpGraphFilename.c_str());
    cerr << "done." << endl;
  }

  // optional input of a seperate file for applying the odometry calibration
  if (odomTestFilename.size() > 0) {

    DataQueue testRobotLaserQueue;
    int numTestOdom = Gm2dlIO::readRobotLaser(odomTestFilename, testRobotLaserQueue);
    if (numTestOdom == 0) {
      cerr << "Unable to read test data" << endl;
    } else {

      ofstream rawStream("odometry_raw.txt");
      ofstream calibratedStream("odometry_calibrated.txt");
      const Vector3d& odomCalib = odomParamsVertex->estimate();
      RobotLaser* prev = dynamic_cast<RobotLaser*>(testRobotLaserQueue.buffer().begin()->second);
      SE2 prevCalibratedPose = prev->odomPose();

      for (DataQueue::Buffer::const_iterator it = testRobotLaserQueue.buffer().begin(); it != testRobotLaserQueue.buffer().end(); ++it) {
        RobotLaser* cur = dynamic_cast<RobotLaser*>(it->second);
        assert(cur);

        double dt = cur->timestamp() - prev->timestamp();
        SE2 motion = prev->odomPose().inverse() * cur->odomPose();

        // convert to velocity measurment
        MotionMeasurement motionMeasurement(motion.translation().x(), motion.translation().y(), motion.rotation().angle(), dt);
        VelocityMeasurement velocityMeasurement = OdomConvert::convertToVelocity(motionMeasurement);

        // apply calibration
        VelocityMeasurement calibratedVelocityMeasurment = velocityMeasurement;
        calibratedVelocityMeasurment.setVl(odomCalib(0) * calibratedVelocityMeasurment.vl());
        calibratedVelocityMeasurment.setVr(odomCalib(1) * calibratedVelocityMeasurment.vr());
        MotionMeasurement mm = OdomConvert::convertToMotion(calibratedVelocityMeasurment, odomCalib(2));

        // combine calibrated odometry with the previous pose
        SE2 remappedOdom;
        remappedOdom.fromVector(mm.measurement());
        SE2 calOdomPose = prevCalibratedPose * remappedOdom;

        // write output
        rawStream << prev->odomPose().translation().x() << " " << prev->odomPose().translation().y() << " " << prev->odomPose().rotation().angle() << endl;
        calibratedStream << calOdomPose.translation().x() << " " << calOdomPose.translation().y() << " " << calOdomPose.rotation().angle() << endl;

        prevCalibratedPose = calOdomPose;
        prev = cur;
      }
    }

  }

  if (outputfilename.size() > 0) {
    Gm2dlIO::updateLaserData(optimizer);
    cerr << "Writing " << outputfilename << " ... ";
    bool writeStatus = Gm2dlIO::writeGm2dl(outputfilename, optimizer);
    cerr << (writeStatus ? "done." : "failed") << endl;
  }

  return 0;
}