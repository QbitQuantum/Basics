bool Ellipsoid::containsPoint(const RefArrayXd pointCoordinates)
{
    // Construct translation matrix

    MatrixXd T = MatrixXd::Identity(Ndimensions+1,Ndimensions+1);
    
    T.bottomLeftCorner(1,Ndimensions) = (-1.) * centerCoordinates.transpose();


    // Construct ellipsoid matrix in homogeneous coordinates

    MatrixXd A = MatrixXd::Zero(Ndimensions+1,Ndimensions+1);
    A(Ndimensions,Ndimensions) = -1;
    
    MatrixXd C = MatrixXd::Zero(Ndimensions, Ndimensions);


    // Compute the covariance matrix

    C =  eigenvectors.matrix() * enlargedEigenvalues.matrix().asDiagonal() 
                               * eigenvectors.matrix().transpose(); 
    A.topLeftCorner(Ndimensions,Ndimensions) = C.inverse();


    // Translate to the ellipsoid center

    MatrixXd AT = T * A * T.transpose(); 

    VectorXd X(Ndimensions+1);
    X.head(Ndimensions) = pointCoordinates.matrix();
    X(Ndimensions) = 1;


    // Check if the point belongs to this ellipsoid

    bool pointBelongsToThisEllipsoid;

    if (X.transpose() * AT * X <= 0)
    {
        pointBelongsToThisEllipsoid = true;
    }
    else
    {
        pointBelongsToThisEllipsoid = false;
    }
        
    return pointBelongsToThisEllipsoid;
}