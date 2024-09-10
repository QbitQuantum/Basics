FeatureModel::FeatureModel(	const CamModel & _camera,
								const MotionModel & _motion,
								const FeaturesState & _featuresState,
								const Mat & frame,
								const Point2f & pf,
								int patchSize,
								float rho_0,
								float sigma_rho):
								camera(_camera),
								motion(_motion),
								features(_featuresState)
	{
    Mat newPatch(cv::Mat(frame, cv::Rect(pf.x-patchSize/2, pf.y-patchSize/2, patchSize,patchSize)));
    this->imageLocation << pf.x, pf.y;

    this->Patch = newPatch.clone();


    Vector2f hd = (Vector2f << (float)pf.x, (float)pf.y);

    // TODO: convert using motionmodel
    Vector3f r = motion->get_r();
    Quatenionf q = motion->get_q();


    Vector3f hC = this->camera.unproject(hd, true);
    Matrix3f Jac_hCHd = this->camera.getUnprojectionJacobian();

    Matrix3f Rot = quat2rot(q);

    Vector3f hW = Rot*hC;

    float hx = hW(0);
    float hy = hW(1);
    float hz = hW(2);



    float theta = atan2(hx,hz);
    float phi = atan2(-hy, sqrt(hx*hx+hz*hz));

	// Updating state and Sigma
    MatrixXf Jx = this->computeJx();
	MatrixXf Jm = this->computeJm();
	Matrix2f Sigma_mm = this->computeSigma_mm(sigma_pixel, sigma_pixel);

	this->f = (VectorXf(6) << r, theta, phi, rho_0);
	this->Sigma_ii = Jm*Sigma_mm*Jm.transpose() + Jx*motion->getSigma_xx()*Jx.transpose();

	this->motion->updateVariaceBlocks(Jx);
	this->features->updateVariaceBlocks(Jx);
	this->features.push_back((*this));
    return 1;

}