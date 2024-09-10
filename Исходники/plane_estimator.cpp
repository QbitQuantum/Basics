  void PlaneEstimator :: estimate(RGBDImage& image, Mat1b& plane_points)
  {

      // Passing from 3D to the optimizer

      const cv::Mat3f& normal_image = image.normal();
      const cv::Mat1f& distance_image = image.depth();
      cv::Mat1b& mask_image = image.depthMaskRef();
      cv::Mat1b objfilter;
      mask_image.copyTo(objfilter);
      plane_points = image.normal().clone();
      plane_points = 0;

    if (!image.normal().data)
    {
      ntk_dbg(0) << "WARNING: you must active the normal filter to get plane estimation!";
      return;
    }

    double min[dim];
    double max[dim];
    int i;

    for (i=0;i<dim;i++)
    {
      max[i] = 1000.0;
      min[i] = -1000.0;
    }
    m_solver.Setup(min,max,DifferentialEvolutionSolver::stBest1Exp,0.8,0.75);


   // Early estimation of plane points projecting the normal values

    for (int r = 1; r < plane_points.rows-1; ++r)
    for (int c = 1; c < plane_points.cols-1; ++c)
    {
      if (objfilter.data && objfilter(r,c))
      {
        cv::Vec3f normal = normal_image(r,c);
        double prod = normal.dot(m_ref_plane);
        if (prod > 0.95)
          plane_points(r,c) = 255;
        else
          plane_points(r,c) = 0;
      }
    }

    // cleaning of the surface very first estimation
    dilate(plane_points,plane_points,cv::Mat());
    erode(plane_points,plane_points,cv::Mat());
    //imwrite("plane-initial.png",plane_points);

    std:vector<Point3f>& g = m_solver.planePointsRef();

    g.clear();
    
    for (int r = 1; r < plane_points.rows-1; ++r)
    for (int c = 1; c < plane_points.cols-1; ++c)
    {
      if (plane_points(r,c))
      {
        // possible table member!
        Point3f p3d = image.calibration()->depth_pose->unprojectFromImage(Point2f(c,r), distance_image(r,c));
        g.push_back(p3d);
      }
    }
    
    // Calculating...
    m_solver.Solve(max_generations);

    double *solution = m_solver.Solution();

    // Plane normalizer
    float suma = solution[0] + solution[1] + solution[2] + solution[3] ;
    for (int i = 0; i < 4; i++)
      solution[i] = solution[i]/ suma;

    ntk::Plane plano (solution[0], solution[1], solution[2], solution[3]);
    //Update RGBD object
    m_plane.set(solution[0], solution[1], solution[2], solution[3]);


    // Final estimation of plane points projecting the normal values

     cv::Vec3f diffevolnormal(solution[0], solution[1], solution[2]);

     for (int r = 1; r < plane_points.rows-1; ++r)
     for (int c = 1; c < plane_points.cols-1; ++c)
     {
       if (objfilter.data && objfilter(r,c))
       {
         cv::Vec3f normal = normal_image(r,c);
         double prod = normal.dot(diffevolnormal);

         if (prod > 0.5)
           plane_points(r,c) = 255;
         else
           plane_points(r,c) = 0;
       }
     }

     // Cleaning of the DE plane-pixels solution
     dilate(plane_points,plane_points,cv::Mat());
     erode(plane_points,plane_points,cv::Mat());
    // imwrite("plane-DE.png",plane_points);


  }