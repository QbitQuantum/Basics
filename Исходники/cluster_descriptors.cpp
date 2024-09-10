void CloudOrienter::_compute() {
    assert(input_cloud_);
    assert(input_intensities_);
    assert(!output_cloud_);
    //cout << input_intensities_->rows() << " " << input_cloud_->rows() << endl;
    assert(input_cloud_->rows() == input_intensities_->rows());
    assert(input_cloud_->rows() > 2);

    // -- Subtract off the mean of the points.
    MatrixXf& points = *input_cloud_;
    VectorXf pt_mean = points.colwise().sum() / (float)points.rows();
    for(int i=0; i<points.rows(); ++i)
        points.row(i) -= pt_mean.transpose();

    // -- Flatten to z == 0.
    MatrixXf X = points;
    X.col(2) = VectorXf::Zero(X.rows());
    MatrixXf Xt = X.transpose();

    // -- Find the long axis.
    // Start with a random vector.
    VectorXf pc = VectorXf::Zero(3);
    pc(0) = 1; //Chosen by fair dice roll.
    pc(1) = 1;
    pc.normalize();

    // Power method.
    VectorXf prev = pc;
    double thresh = 1e-4;
    int ctr = 0;
    while(true) {
        prev = pc;
        pc =  Xt * (X * pc);
        pc.normalize();
        ctr++;
        if((pc - prev).norm() < thresh)
            break;
        // -- In some degenerate cases, it is possible for the vector
        //    to never settle down to the first PC.
        if(ctr > 100)
            break;

    }
    assert(abs(pc(2)) < 1e-4);

    // -- Find the short axis.
    VectorXf shrt = VectorXf::Zero(3);
    shrt(1) = -pc(0);
    shrt(0) = pc(1);
    assert(abs(shrt.norm() - 1) < 1e-4);
    assert(abs(shrt.dot(pc)) < 1e-4);

    // -- Build the basis of normalized coordinates.
    MatrixXf basis = MatrixXf::Zero(3,3);
    basis.col(0) = pc;
    basis.col(1) = shrt;
    basis(2,2) = 1.0;
    assert(abs(basis.col(0).dot(basis.col(1))) < 1e-4);
    assert(abs(basis.col(0).norm() - 1) < 1e-4);
    assert(abs(basis.col(1).norm() - 1) < 1e-4);
    assert(abs(basis.col(2).norm() - 1) < 1e-4);

    // -- Rotate and set the output_cloud_.
    output_cloud_ = shared_ptr<MatrixXf>(new MatrixXf);
    *output_cloud_ = points * basis;
    assert(output_cloud_->rows() == input_cloud_->rows());
}