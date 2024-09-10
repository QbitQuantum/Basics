  void Linearizer::update() {
    assert(_aligner && "Aligner: missing _aligner");
    
    // Variables initialization.
    _b = Vector6f::Zero();
    _H = Matrix6f::Zero();
    const InformationMatrixVector &pointOmegas = _aligner->currentCloud()->pointInformationMatrix();
    const InformationMatrixVector &normalOmegas = _aligner->currentCloud()->normalInformationMatrix();

    // Allocate the variables for the sum reduction;
    int numThreads = omp_get_max_threads();
    Matrix4f _Htt[numThreads], _Htr[numThreads], _Hrr[numThreads];
    Vector4f _bt[numThreads], _br[numThreads];
    int _inliers[numThreads];
    float _errors[numThreads];
    int iterationsPerThread = _aligner->correspondenceFinder()->numCorrespondences() / numThreads;
#pragma omp parallel
    {
      int threadId = omp_get_thread_num();
      int imin = iterationsPerThread * threadId;
      int imax = imin + iterationsPerThread;
      if(imax > _aligner->correspondenceFinder()->numCorrespondences())
	imax = _aligner->correspondenceFinder()->numCorrespondences();

      Eigen::Matrix4f &Htt = _Htt[threadId];
      Eigen::Matrix4f &Htr = _Htr[threadId];
      Eigen::Matrix4f &Hrr = _Hrr[threadId];
      Eigen::Vector4f &bt = _bt[threadId];
      Eigen::Vector4f &br = _br[threadId];
      Htt = Matrix4f::Zero(); 
      Htr = Matrix4f::Zero(); 
      Hrr = Matrix4f::Zero();
      bt = Vector4f::Zero();
      br = Vector4f::Zero();
      
      int &inliers = _inliers[threadId];
      float &error = _errors[threadId];
      error = 0;
      inliers = 0;
      for(int i = imin; i < imax; i++) {
	const Correspondence &correspondence = _aligner->correspondenceFinder()->correspondences()[i];
	const Point referencePoint = _T * _aligner->referenceCloud()->points()[correspondence.referenceIndex];
	const Normal referenceNormal = _T * _aligner->referenceCloud()->normals()[correspondence.referenceIndex];
	const Point &currentPoint = _aligner->currentCloud()->points()[correspondence.currentIndex];
	const Normal &currentNormal = _aligner->currentCloud()->normals()[correspondence.currentIndex];
	const InformationMatrix &omegaP = pointOmegas[correspondence.currentIndex];
	const InformationMatrix &omegaN = normalOmegas[correspondence.currentIndex];
      
	const Vector4f pointError = referencePoint - currentPoint;
	const Vector4f normalError = referenceNormal - currentNormal;
	const Vector4f ep = omegaP * pointError;
	const Vector4f en = omegaN * normalError;

	float localError = pointError.dot(ep) + normalError.dot(en);
	float kscale = 1;
	if(localError > _inlierMaxChi2) {
	  if (_robustKernel) {
	    kscale = sqrt(_inlierMaxChi2 / localError);
	  } 
	  else {
	    continue;
	  }
	}
	inliers++;
	error += kscale * localError;
	Matrix4f Sp = skew(referencePoint);
	Matrix4f Sn = skew(referenceNormal);
	Htt.noalias() += omegaP;
	Htr.noalias() += omegaP * Sp;
	Hrr.noalias() += Sp.transpose() * omegaP * Sp + Sn.transpose() * omegaN * Sn;
	bt.noalias() += kscale * ep;
	br.noalias() += kscale * (Sp.transpose() * ep + Sn.transpose() * en);
      }
    }

    // Now do the reduce
    Eigen::Matrix4f Htt = Eigen::Matrix4f::Zero();
    Eigen::Matrix4f Htr = Eigen::Matrix4f::Zero();
    Eigen::Matrix4f Hrr = Eigen::Matrix4f::Zero();
    Eigen::Vector4f bt = Eigen::Vector4f::Zero();
    Eigen::Vector4f br = Eigen::Vector4f::Zero();
    this->_inliers = 0;
    this->_error = 0;
    for(int t = 0; t < numThreads; t++) {
      Htt += _Htt[t];
      Htr += _Htr[t];
      Hrr += _Hrr[t];
      bt += _bt[t];
      br += _br[t];
      this->_inliers += _inliers[t];
      this->_error += _errors[t];
    }
    _H.block<3, 3>(0, 0) = Htt.block<3, 3>(0, 0);
    _H.block<3, 3>(0, 3) = Htr.block<3, 3>(0, 0);
    _H.block<3, 3>(3, 3) = Hrr.block<3, 3>(0, 0);
    _H.block<3, 3>(3, 0) = _H.block<3, 3>(0, 3).transpose();
    _b.block<3, 1>(0, 0) = bt.block<3, 1>(0, 0);
    _b.block<3, 1>(3, 0) = br.block<3, 1>(0, 0);
  }