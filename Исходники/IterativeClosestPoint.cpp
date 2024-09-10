void IterativeClosestPoint::execute() {
    float error = std::numeric_limits<float>::max(), previousError;
    uint iterations = 0;

    // Get access to the two point sets
    PointSetAccess::pointer accessFixedSet = ((PointSet::pointer)getStaticInputData<PointSet>(0))->getAccess(ACCESS_READ);
    PointSetAccess::pointer accessMovingSet = ((PointSet::pointer)getStaticInputData<PointSet>(1))->getAccess(ACCESS_READ);

    // Get transformations of point sets
    AffineTransformation::pointer fixedPointTransform2 = SceneGraph::getAffineTransformationFromData(getStaticInputData<PointSet>(0));
    Eigen::Affine3f fixedPointTransform;
    fixedPointTransform.matrix() = fixedPointTransform2->matrix();
    AffineTransformation::pointer initialMovingTransform2 = SceneGraph::getAffineTransformationFromData(getStaticInputData<PointSet>(1));
    Eigen::Affine3f initialMovingTransform;
    initialMovingTransform.matrix() = initialMovingTransform2->matrix();

    // These matrices are Nx3
    MatrixXf fixedPoints = accessFixedSet->getPointSetAsMatrix();
    MatrixXf movingPoints = accessMovingSet->getPointSetAsMatrix();

    Eigen::Affine3f currentTransformation = Eigen::Affine3f::Identity();

    // Want to choose the smallest one as moving
    bool invertTransform = false;
    if(false && fixedPoints.cols() < movingPoints.cols()) {
        reportInfo() << "switching fixed and moving" << Reporter::end;
        // Switch fixed and moving
        MatrixXf temp = fixedPoints;
        fixedPoints = movingPoints;
        movingPoints = temp;
        invertTransform = true;

        // Apply initial transformations
        //currentTransformation = fixedPointTransform.getTransform();
        movingPoints = fixedPointTransform*movingPoints.colwise().homogeneous();
        fixedPoints = initialMovingTransform*fixedPoints.colwise().homogeneous();
    } else {
        // Apply initial transformations
        //currentTransformation = initialMovingTransform.getTransform();
        movingPoints = initialMovingTransform*movingPoints.colwise().homogeneous();
        fixedPoints = fixedPointTransform*fixedPoints.colwise().homogeneous();
    }
    do {
        previousError = error;
        MatrixXf movedPoints = currentTransformation*(movingPoints.colwise().homogeneous());

        // Match closest points using current transformation
        MatrixXf rearrangedFixedPoints = rearrangeMatrixToClosestPoints(
                fixedPoints, movedPoints);

        // Get centroids
        Vector3f centroidFixed = getCentroid(rearrangedFixedPoints);
        //reportInfo() << "Centroid fixed: " << Reporter::end;
        //reportInfo() << centroidFixed << Reporter::end;
        Vector3f centroidMoving = getCentroid(movedPoints);
        //reportInfo() << "Centroid moving: " << Reporter::end;
        //reportInfo() << centroidMoving << Reporter::end;

        Eigen::Transform<float, 3, Eigen::Affine> updateTransform = Eigen::Transform<float, 3, Eigen::Affine>::Identity();

        if(mTransformationType == IterativeClosestPoint::RIGID) {
            // Create correlation matrix H of the deviations from centroid
            MatrixXf H = (movedPoints.colwise() - centroidMoving)*
                    (rearrangedFixedPoints.colwise() - centroidFixed).transpose();

            // Do SVD on H
            Eigen::JacobiSVD<Eigen::MatrixXf> svd(H, Eigen::ComputeFullU | Eigen::ComputeFullV);

            // Estimate rotation as R=V*U.transpose()
            MatrixXf temp = svd.matrixV()*svd.matrixU().transpose();
            Matrix3f d = Matrix3f::Identity();
            d(2,2) = sign(temp.determinant());
            Matrix3f R = svd.matrixV()*d*svd.matrixU().transpose();

            // Estimate translation
            Vector3f T = centroidFixed - R*centroidMoving;

            updateTransform.linear() = R;
            updateTransform.translation() = T;
        } else {
            // Only translation
            Vector3f T = centroidFixed - centroidMoving;
            updateTransform.translation() = T;
        }

        // Update current transformation
        currentTransformation = updateTransform*currentTransformation;

        // Calculate RMS error
        MatrixXf distance = rearrangedFixedPoints - currentTransformation*(movingPoints.colwise().homogeneous());
        error = 0;
        for(uint i = 0; i < distance.cols(); i++) {
            error += pow(distance.col(i).norm(),2);
        }
        error = sqrt(error / distance.cols());

        iterations++;
        reportInfo() << "Error: " << error << Reporter::end;
        // To continue, change in error has to be above min error change and nr of iterations less than max iterations
    } while(previousError-error > mMinErrorChange && iterations < mMaxIterations);


    if(invertTransform){
        currentTransformation = currentTransformation.inverse();
    }

    mError = error;
    mTransformation->matrix() = currentTransformation.matrix();
}