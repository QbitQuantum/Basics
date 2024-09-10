bool EdgeWin::process_project(edgeconfig &conf) {
  QTime time; time.start();
  
  vector<QThread *> threads;  ProcessThread process_thread(project);
  threads.push_back((QThread*)&process_thread);
  progressDialog("Processing image stacks. Please wait.", threads);

  if(project->num_stacks() == 0) {
    delete project;
    project = NULL;
    QMessageBox::critical(this, tr("Error"), tr("Unable to laod any stacks. Please check parameters, and the stack file.") );
    return false;
  }

  // NOTE: update_gl() populates vertex buffers and must run in a single (main) thread.
  if(conf.use_GL_buffers) project->update_gl(); 


  view->setProject(project);
  view->setVol(project->stacks[0]);
  view->clearSelected();

  // Set slider positions.
  scrollTime->setRange(0, project->stacks.size() - 1); scrollTime->setSliderPosition(0);

  int width0 = project->stacks[0]->width(), height0 = project->stacks[0]->height(), depth0 = project->stacks[0]->depth();
  scrollXplane->setRange(0, width0 - 1);  scrollXplane->setSliderPosition(width0 / 2);
  scrollYplane->setRange(0, height0 - 1); scrollYplane->setSliderPosition(height0 / 2);
  scrollZplane->setRange(0, depth0 - 1);  scrollZplane->setSliderPosition(depth0 / 2);

  updateInfo();
  // Done setting slider positions.

  mTree->clear(); 
  mTree2Idx.clear();
  // TODO: Organize into noise, background, etc. at time point 0 get models 
  for(int idx = 0; idx < project->num_cells(0); idx++) {
    QString defaultText = tr("Model ") + QString::number(idx + 1);
    QTreeWidgetItem *modelItem = new QTreeWidgetItem(mTree, QStringList() << defaultText);
    modelItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    mTree2Idx[modelItem] = idx;
  }
  view->updateGL();

  // Display an information box with processing information.
  QString procTimeStr = "Run completed in " + QString::number(float(time.elapsed()) / 1e3) +  " seconds.";
  QMessageBox::information(this, tr("Processing time"), procTimeStr);

  return true;
}