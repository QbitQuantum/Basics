int main(int argc, const char* argv[])
{
  if (argc<2)
  {
    cout << endl;
    cout << "Please type: " << endl;
    cout << "ba_demo [PIXEL_NOISE] [OUTLIER RATIO] [ROBUST_KERNEL] [STRUCTURE_ONLY] [DENSE]" << endl;
    cout << endl;
    cout << "PIXEL_NOISE: noise in image space (E.g.: 1)" << endl;
    cout << "OUTLIER_RATIO: probability of spuroius observation  (default: 0.0)" << endl;
    cout << "ROBUST_KERNEL: use robust kernel (0 or 1; default: 0==false)" << endl;
    cout << "STRUCTURE_ONLY: performe structure-only BA to get better point initializations (0 or 1; default: 0==false)" << endl;
    cout << "DENSE: Use dense solver (0 or 1; default: 0==false)" << endl;
    cout << endl;
    cout << "Note, if OUTLIER_RATIO is above 0, ROBUST_KERNEL should be set to 1==true." << endl;
    cout << endl;
    exit(0);
  }

  double PIXEL_NOISE = atof(argv[1]);

  double OUTLIER_RATIO = 0.0;

  if (argc>2)
  {
    OUTLIER_RATIO = atof(argv[2]);
  }

  bool ROBUST_KERNEL = false;
  if (argc>3)
  {
    ROBUST_KERNEL = atoi(argv[3]) != 0;
  }
  bool STRUCTURE_ONLY = false;
  if (argc>4)
  {
    STRUCTURE_ONLY = atoi(argv[4]) != 0;
  }

  bool DENSE = false;
  if (argc>5)
  {
    DENSE = atoi(argv[5]) != 0;
  }

  cout << "PIXEL_NOISE: " <<  PIXEL_NOISE << endl;
  cout << "OUTLIER_RATIO: " << OUTLIER_RATIO<<  endl;
  cout << "ROBUST_KERNEL: " << ROBUST_KERNEL << endl;
  cout << "STRUCTURE_ONLY: " << STRUCTURE_ONLY<< endl;
  cout << "DENSE: "<<  DENSE << endl;



  g2o::SparseOptimizer optimizer;
  optimizer.setVerbose(false);
  g2o::BlockSolver_6_3::LinearSolverType * linearSolver;
  if (DENSE)
  {
        linearSolver= new g2o::LinearSolverDense<g2o::BlockSolver_6_3::PoseMatrixType>();
		cerr << "Using DENSE" << endl;
  }
  else
  {
#ifdef G2O_HAVE_CHOLMOD
	cerr << "Using CHOLMOD" << endl;
    linearSolver = new g2o::LinearSolverCholmod<g2o::BlockSolver_6_3::PoseMatrixType>();
#elif defined G2O_HAVE_CSPARSE
    linearSolver = new g2o::LinearSolverCSparse<g2o::BlockSolver_6_3::PoseMatrixType>();
	cerr << "Using CSPARSE" << endl;
#else
#error neither CSparse nor Cholmod are available
#endif
  }


  g2o::BlockSolver_6_3 * solver_ptr
      = new g2o::BlockSolver_6_3(linearSolver);

  g2o::OptimizationAlgorithmLevenberg* solver = new g2o::OptimizationAlgorithmLevenberg(solver_ptr);

  optimizer.setAlgorithm(solver);

  // set up 500 points
  vector<Vector3d> true_points;
  for (size_t i=0;i<500; ++i)
  {
    true_points.push_back(Vector3d((Sample::uniform()-0.5)*3,
                                   Sample::uniform()-0.5,
                                   Sample::uniform()+10));
  }


  Vector2d focal_length(500,500); // pixels
  Vector2d principal_point(320,240); // 640x480 image
  double baseline = 0.075;      // 7.5 cm baseline


  vector<g2o::SE3Quat,
      aligned_allocator<g2o::SE3Quat> > true_poses;

  // set up camera params
  g2o::VertexSCam::setKcam(focal_length[0],focal_length[1],
                           principal_point[0],principal_point[1],
                           baseline);
  
  // set up 5 vertices, first 2 fixed
  int vertex_id = 0;
  for (size_t i=0; i<5; ++i)
  {


    Vector3d trans(i*0.04-1.,0,0);

    Eigen:: Quaterniond q;
    q.setIdentity();
    g2o::SE3Quat pose(q,trans);


    g2o::VertexSCam * v_se3
        = new g2o::VertexSCam();

    v_se3->setId(vertex_id);
    v_se3->setEstimate(pose);
    v_se3->setAll();            // set aux transforms

    if (i<2)
      v_se3->setFixed(true);
    
    optimizer.addVertex(v_se3);
    true_poses.push_back(pose);
    vertex_id++;
  }

  int point_id=vertex_id;
  int point_num = 0;
  double sum_diff2 = 0;

  cout << endl;
  tr1::unordered_map<int,int> pointid_2_trueid;
  tr1::unordered_set<int> inliers;

  // add point projections to this vertex
  for (size_t i=0; i<true_points.size(); ++i)
  {
    g2o::VertexSBAPointXYZ * v_p
        = new g2o::VertexSBAPointXYZ();


    v_p->setId(point_id);
    v_p->setMarginalized(true);
    v_p->setEstimate(true_points.at(i)
        + Vector3d(Sample::gaussian(1),
                   Sample::gaussian(1),
                   Sample::gaussian(1)));



    int num_obs = 0;

    for (size_t j=0; j<true_poses.size(); ++j)
    {
      Vector3d z;
      dynamic_cast<g2o::VertexSCam*>
        (optimizer.vertices().find(j)->second)
        ->mapPoint(z,true_points.at(i));

      if (z[0]>=0 && z[1]>=0 && z[0]<640 && z[1]<480)
      {
        ++num_obs;
      }
    }

    if (num_obs>=2)
    {
      optimizer.addVertex(v_p);

      bool inlier = true;
      for (size_t j=0; j<true_poses.size(); ++j)
      {
        Vector3d z;
        dynamic_cast<g2o::VertexSCam*>
          (optimizer.vertices().find(j)->second)
          ->mapPoint(z,true_points.at(i));

        if (z[0]>=0 && z[1]>=0 && z[0]<640 && z[1]<480)
        {
          double sam = Sample::uniform();
          if (sam<OUTLIER_RATIO)
          {
            z = Vector3d(Sample::uniform(64,640),
                         Sample::uniform(0,480),
                         Sample::uniform(0,64)); // disparity
            z(2) = z(0) - z(2); // px' now

            inlier= false;
          }

          z += Vector3d(Sample::gaussian(PIXEL_NOISE),
                        Sample::gaussian(PIXEL_NOISE),
                        Sample::gaussian(PIXEL_NOISE/16.0));

          g2o::Edge_XYZ_VSC * e
              = new g2o::Edge_XYZ_VSC();


          e->vertices()[0]
              = dynamic_cast<g2o::OptimizableGraph::Vertex*>(v_p);

          e->vertices()[1]
              = dynamic_cast<g2o::OptimizableGraph::Vertex*>
              (optimizer.vertices().find(j)->second);

          e->setMeasurement(z);
          //e->inverseMeasurement() = -z;
          e->information() = Matrix3d::Identity();

          e->setRobustKernel(ROBUST_KERNEL);
          e->setHuberWidth(1);

          optimizer.addEdge(e);


        }

      }

      if (inlier)
      {
        inliers.insert(point_id);
        Vector3d diff = v_p->estimate() - true_points[i];

        sum_diff2 += diff.dot(diff);
      }
     // else
     //   cout << "Point: " << point_id <<  "has at least one spurious observation" <<endl;

      pointid_2_trueid.insert(make_pair(point_id,i));

      ++point_id;
      ++point_num;
    }

  }

  cout << endl;
  optimizer.initializeOptimization();

  optimizer.setVerbose(true);

  if (STRUCTURE_ONLY)
  {
    cout << "Performing structure-only BA:"   << endl;
    g2o::StructureOnlySolver<3> structure_only_ba;
    g2o::OptimizableGraph::VertexContainer points;
    for (g2o::OptimizableGraph::VertexIDMap::const_iterator it = optimizer.vertices().begin(); it != optimizer.vertices().end(); ++it) {
      g2o::OptimizableGraph::Vertex* v = static_cast<g2o::OptimizableGraph::Vertex*>(it->second);
      if (v->dimension() == 3)
        points.push_back(v);
    }

    structure_only_ba.calc(points, 10);
  }

    cout << endl;
  cout << "Performing full BA:" << endl;
  optimizer.optimize(10);

  cout << endl;
  cout << "Point error before optimisation (inliers only): " << sqrt(sum_diff2/point_num) << endl;


  point_num = 0;
  sum_diff2 = 0;


  for (tr1::unordered_map<int,int>::iterator it=pointid_2_trueid.begin();
       it!=pointid_2_trueid.end(); ++it)
  {

    g2o::HyperGraph::VertexIDMap::iterator v_it
        = optimizer.vertices().find(it->first);

    if (v_it==optimizer.vertices().end())
    {
      cerr << "Vertex " << it->first << " not in graph!" << endl;
      exit(-1);
    }

    g2o::VertexSBAPointXYZ * v_p
        = dynamic_cast< g2o::VertexSBAPointXYZ * > (v_it->second);

    if (v_p==0)
    {
      cerr << "Vertex " << it->first << "is not a PointXYZ!" << endl;
      exit(-1);
    }

    Vector3d diff = v_p->estimate()-true_points[it->second];

    if (inliers.find(it->first)==inliers.end())
      continue;

    sum_diff2 += diff.dot(diff);

    ++point_num;
  }

  cout << "Point error after optimisation (inliers only): " << sqrt(sum_diff2/point_num) << endl;
  cout << endl;

}