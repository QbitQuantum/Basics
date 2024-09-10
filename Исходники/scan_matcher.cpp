bool ScanMatcher::closeScanMatching(OptimizableGraph::VertexSet& vset, OptimizableGraph::Vertex* _originVertex, OptimizableGraph::Vertex* _currentVertex,  SE2 *trel, double maxScore){ 
  
  VertexSE2* currentVertex=dynamic_cast<VertexSE2*>(_currentVertex);
  VertexSE2* originVertex =dynamic_cast<VertexSE2*>(_originVertex);

  resetGrid();
  
  RawLaser::Point2DVector scansInRefVertex;
  transformPointsFromVSet(vset, _originVertex, scansInRefVertex);
  _grid.addAndConvolvePoints<RawLaser::Point2DVector>(scansInRefVertex.begin(), scansInRefVertex.end(), _kernel);

  //Current vertex
  RobotLaser* lasercv = dynamic_cast<RobotLaser*>(currentVertex->userData());
  
  if (!lasercv)
    return false;

  RawLaser::Point2DVector cvscan = lasercv->cartesian();
  SE2 laserPoseCV = lasercv->laserParams().laserPose;
  RawLaser::Point2DVector cvScanRobot;
  applyTransfToScan(laserPoseCV, cvscan, cvScanRobot);

  SE2 delta = originVertex->estimate().inverse() * currentVertex->estimate();

  Vector3d initGuess(delta.translation().x(), delta.translation().y(), delta.rotation().angle());

  std::vector<MatcherResult> mresvec;
  clock_t t_ini, t_fin;
  double secs;

  t_ini = clock();

  double thetaRes = 0.0125*.5; // was 0.01
  Vector3f lower(-.3+initGuess.x(), -.3+initGuess.y(), -0.2+initGuess.z());
  Vector3f upper(+.3+initGuess.x(),  .3+initGuess.y(),  0.2+initGuess.z()); 
  _grid.greedySearch(mresvec, cvScanRobot, lower, upper, thetaRes, maxScore, 0.5, 0.5, 0.2);
  t_fin = clock();

  secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
  printf("Greedy search: %.16g ms. Matcher results: %i\n", secs * 1000.0, (int) mresvec.size());

  if (mresvec.size()){
    Vector3d adj=mresvec[0].transformation;
    trel->setTranslation(Vector2d(adj.x(), adj.y()));
    trel->setRotation(adj.z());
    //cerr <<  "bestScore = " << mresvec[0].score << endl << endl; 

    // if (currentVertex->id() > 120 && currentVertex->id() < 200){
    //   CharMatcher auxGrid = _grid;

    //   Vector2dVector transformedScan;
    //   transformedScan.resize(cvScanRobot.size());
    //   for (unsigned int i = 0; i<cvScanRobot.size(); i++){
    // 	SE2 point;
    // 	point.setTranslation(cvScanRobot[i]);
      
    // 	SE2 transformedpoint = *trel * point;
    // 	transformedScan[i] = transformedpoint.translation();
    //   }
    //   auxGrid.addPoints<RawLaser::Point2DVector>(transformedScan.begin(), transformedScan.end());

    //   ofstream image;
    //   std::stringstream filename;
    //   filename << "matchedmap" << currentVertex->id() << "_" << mresvec[0].score << ".ppm";
    //   image.open(filename.str().c_str());
    //   auxGrid.grid().saveAsPPM(image, false);
    // }

    return true;
  } 
  cerr << endl;
  return false;

}