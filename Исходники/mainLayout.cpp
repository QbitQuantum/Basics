void MainWindow::registerProject()
{
  if (m_doc._sfm_data.control_points.size() < 3)
  {
    QMessageBox msgBox;
    msgBox.setText("At least 3 control points are required.");
    msgBox.exec();
    return;
  }

  // Assert that control points can be triangulated
  for (Landmarks::const_iterator iterL = m_doc._sfm_data.control_points.begin();
    iterL != m_doc._sfm_data.control_points.end(); ++iterL)
  {
    if (iterL->second.obs.size() < 2)
    {
      QMessageBox msgBox;
      msgBox.setText("Each control point must be defined in at least 2 pictures.");
      msgBox.exec();
      return;
    }
  }

  //---
  // registration (coarse):
  // - compute the 3D points corresponding to the control point observation for the SfM scene
  // - compute a coarse registration between the controls points & the triangulated point
  // - transform the scene according the found transformation
  //---
  std::map<IndexT, Vec3> vec_control_points, vec_triangulated;
  std::map<IndexT, double> vec_triangulation_errors;
  for (Landmarks::iterator iterCP = m_doc._sfm_data.control_points.begin();
    iterCP != m_doc._sfm_data.control_points.end(); ++iterCP)
  {
    Landmark & landmark = iterCP->second;
    //Triangulate the point:
    Triangulation trianObj;
    const Observations & obs = landmark.obs;
    for(Observations::const_iterator itObs = obs.begin();
      itObs != obs.end(); ++itObs)
    {
      const View * view = m_doc._sfm_data.views.at(itObs->first).get();
      if (!m_doc._sfm_data.IsPoseAndIntrinsicDefined(view))
        continue;
      const openMVG::cameras::IntrinsicBase * cam = m_doc._sfm_data.GetIntrinsics().at(view->id_intrinsic).get();
      const openMVG::geometry::Pose3 pose = m_doc._sfm_data.GetPoseOrDie(view);
      trianObj.add(
        cam->get_projective_equivalent(pose),
        cam->get_ud_pixel(itObs->second.x));
    }
    // Compute the 3D point
    const Vec3 X = trianObj.compute();
    if (trianObj.minDepth() > 0) // Keep the point only if it have a positive depth
    {
      vec_triangulated[iterCP->first] = X;
      vec_control_points[iterCP->first] = landmark.X;
      vec_triangulation_errors[iterCP->first] = trianObj.error()/(double)trianObj.size();
    }
    else
    {
      std::cout << "Invalid triangulation" << std::endl;
      return;
    }
  }

  if (vec_control_points.size() < 3)
  {
    QMessageBox msgBox;
    msgBox.setText("Insufficient number of triangulated control points.");
    msgBox.exec();
    return;
  }

  // compute the similarity
  {
    // data conversion to appropriate container
    Mat x1(3, vec_control_points.size()),
        x2(3, vec_control_points.size());
    for (int i=0; i < vec_control_points.size(); ++i)
    {
      x1.col(i) = vec_triangulated[i];
      x2.col(i) = vec_control_points[i];
    }

    std::cout
      << "Control points observation triangulations:\n"
      << x1 << std::endl << std::endl
      << "Control points coords:\n"
      << x2 << std::endl << std::endl;

    Vec3 t;
    Mat3 R;
    double S;
    if (openMVG::geometry::FindRTS(x1, x2, &S, &t, &R))
    {
      openMVG::geometry::Refine_RTS(x1,x2,&S,&t,&R);
      std::cout << "Found transform:\n"
        << " scale: " << S << "\n"
        << " rotation:\n" << R << "\n"
        << " translation: "<< t.transpose() << std::endl;

      // Encode the transformation as a 3D Similarity transformation matrix // S * R * X + t
      const openMVG::geometry::Similarity3 sim(geometry::Pose3(R, -R.transpose() * t/S), S);

      //--
      // Apply the found transformation
      //--

      // Transform the landmark positions
      for (Landmarks::iterator iterL = m_doc._sfm_data.structure.begin();
        iterL != m_doc._sfm_data.structure.end(); ++iterL)
      {
        iterL->second.X = sim(iterL->second.X);
      }

      // Transform the camera positions
      for (Poses::iterator iterP = m_doc._sfm_data.poses.begin();
        iterP != m_doc._sfm_data.poses.end(); ++iterP)
      {
        geometry::Pose3 & pose = iterP->second;
        pose = sim(pose);
      }

      // Display some statistics:
      std::stringstream os;
      for (Landmarks::const_iterator iterL = m_doc._sfm_data.control_points.begin();
        iterL != m_doc._sfm_data.control_points.end(); ++iterL)
      {
        const IndexT CPIndex = iterL->first;
        // If the control point has not been used, continue...
        if (vec_triangulation_errors.find(CPIndex) == vec_triangulation_errors.end())
          continue;

        os
          << "CP index: " << CPIndex << "\n"
          << "CP triangulation error: " << vec_triangulation_errors[CPIndex] << " pixel(s)\n"
          << "CP registration error: "
          << (sim(vec_triangulated[CPIndex]) - vec_control_points[CPIndex]).norm() << " user unit(s)"<< "\n\n";
      }
      std::cout << os.str();

      QMessageBox msgBox;
      msgBox.setText(QString::fromStdString(string_pattern_replace(os.str(), "\n", "<br>")));
      msgBox.exec();
    }
    else
    {
      QMessageBox msgBox;
      msgBox.setText("Registration failed. Please check your Control Points coordinates.");
      msgBox.exec();
    }
  }
}