  void Aligner::align() {
    assert(_projector && "Aligner: missing _projector");
    assert(_linearizer && "Aligner: missing _linearizer");
    assert(_correspondenceFinder && "Aligner: missing _correspondenceFinder");
    assert(_referenceCloud && "Aligner: missing _referenceCloud");
    assert(_currentCloud && "Aligner: missing _currentCloud");

    struct timeval tvStart, tvEnd;
    gettimeofday(&tvStart, 0);

    // The current points are seen from the frame of the sensor
    _projector->setTransform(_currentSensorOffset);
    _projector->project(_correspondenceFinder->currentIndexImage(),
			_correspondenceFinder->currentDepthImage(),
			_currentCloud->points());
    _T = _initialGuess;
        
    for(int i = 0; i < _outerIterations; i++) {
      /************************************************************************
       *                         Correspondence Computation                   *
       ************************************************************************/

      // Compute the indices of the current scene from the point of view of the sensor
      _T.matrix().row(3) << 0.0f, 0.0f, 0.0f, 1.0f;
      _projector->setTransform(_T * _referenceSensorOffset);
      _projector->project(_correspondenceFinder->referenceIndexImage(),
			  _correspondenceFinder->referenceDepthImage(),
			  _referenceCloud->points());
    
      // Correspondences computation.  
      _correspondenceFinder->compute(*_referenceCloud, *_currentCloud, _T.inverse());
 
      /************************************************************************
       *                            Alignment                                 *
       ************************************************************************/
      Eigen::Isometry3f invT = _T.inverse();
      for(int k = 0; k < _innerIterations; k++) {      
	invT.matrix().block<1, 4>(3, 0) << 0.0f, 0.0f, 0.0f, 1.0f;
	Matrix6f H;
	Vector6f b;

	_linearizer->setT(invT);
	_linearizer->update();
	H = _linearizer->H() + Matrix6f::Identity();
	b = _linearizer->b();
	H += Matrix6f::Identity() * 1000.0f;

	// Add the priors
	for(size_t j = 0; j < _priors.size(); j++) {
	  const SE3Prior *prior = _priors[j];
	  Vector6f priorError = prior->error(invT);
	  Matrix6f priorJacobian = prior->jacobian(invT);
	  Matrix6f priorInformationRemapped = prior->errorInformation(invT);

	  Matrix6f Hp = priorJacobian.transpose() * priorInformationRemapped * priorJacobian;
	  Vector6f bp = priorJacobian.transpose() * priorInformationRemapped * priorError;

	  H += Hp;
	  b += bp;
	}
      
	Vector6f dx = H.ldlt().solve(-b);
	Eigen::Isometry3f dT = v2t(dx);
	invT = dT * invT;
      }
      
      _T = invT.inverse();
      _T = v2t(t2v(_T));
      _T.matrix().block<1, 4>(3, 0) << 0.0f, 0.0f, 0.0f, 1.0f;
    }

    gettimeofday(&tvEnd, 0);
    double tStart = tvStart.tv_sec * 1000.0f + tvStart.tv_usec * 0.001f;
    double tEnd = tvEnd.tv_sec * 1000.0f + tvEnd.tv_usec * 0.001f;
    _totalTime = tEnd - tStart;
    _error = _linearizer->error();
    _inliers = _linearizer->inliers();

    _computeStatistics(_mean, _omega, _translationalEigenRatio, _rotationalEigenRatio);
    if (_rotationalEigenRatio > _rotationalMinEigenRatio || 
	_translationalEigenRatio > _translationalMinEigenRatio) {
      if (_debug) {
	cerr << endl;
	cerr << "************** WARNING SOLUTION MIGHT BE INVALID (eigenratio failure) **************" << endl;
	cerr << "tr: " << _translationalEigenRatio << " rr: " << _rotationalEigenRatio << endl;
	cerr << "************************************************************************************" << endl;
      }
    } 
    else {
      if (_debug) {
	cerr << "************** I FOUND SOLUTION VALID SOLUTION   (eigenratio ok) *******************" << endl;
	cerr << "tr: " << _translationalEigenRatio << " rr: " << _rotationalEigenRatio << endl;
	cerr << "************************************************************************************" << endl;
      }
    }
    if (_debug) {
      cout << "Solution statistics in (t, mq): " << endl;
      cout << "mean: " << _mean.transpose() << endl;
      cout << "Omega: " << endl;
      cout << _omega << endl;
    }
  }