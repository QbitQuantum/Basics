  void ViewerState::processCommands(){
    _meHasNewFrame = false;
    refreshFlags();
    updateDrawableParameters();
    if(!wasInitialGuess && !newCloudAdded && drawableFrameVector.size() > 1 && *initialGuessViewer) {
      initialGuessSelected();
      continuousMode = false;
    } else if(newCloudAdded && drawableFrameVector.size() > 1 && *optimizeViewer && !(*stepByStepViewer)) {
      optimizeSelected();
      continuousMode = false;
    }
    // Add cloud was pressed.
    else if(*addCloud) {
      addCloudSelected();
      continuousMode = false;
    }
    // clear buttons pressed.
    else if(*clearAll) {
      clear();
      *clearAll = 0;
      continuousMode = false;
    }
    else if(*clearLast) {
      clearLastSelected();
      continuousMode = false;
    } 
    else if(continuousMode){
      addNextAndOptimizeSelected();
    }
    // To avoid memorized commands to be managed.
    *initialGuessViewer = 0;
    *optimizeViewer = 0;
    *addCloud = 0; 
    *clearAll = 0;
    *clearLast = 0;

    if (0 && drawableFrameVector.size()){
      Eigen::Isometry3f globalT = drawableFrameVector.front()->transformation();
      qglviewer::Vec robotPose(globalT.translation().x(), globalT.translation().y(), globalT.translation().z());
      qglviewer::Vec robotAxisX(globalT.linear()(0,0), globalT.linear()(1,0), globalT.linear()(2,0));
      qglviewer::Vec robotAxisZ(globalT.linear()(0,2), globalT.linear()(1,2), globalT.linear()(2,2));
      pwnGMW->viewer_3d->camera()->setPosition(robotPose+.5*robotAxisZ+.5*robotAxisX);
      pwnGMW->viewer_3d->camera()->setUpVector(robotAxisX+robotAxisZ);
      pwnGMW->viewer_3d->camera()->setViewDirection(robotPose+.5*robotAxisZ+.5*robotAxisX);
    }


    pwnGMW->viewer_3d->updateGL();
  }