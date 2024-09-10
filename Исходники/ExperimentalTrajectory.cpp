void ExperimentalTrajectory::calculateRbfnWeights()
{
    int nC = kernelCenters.rows();
    Eigen::MatrixXd rbfnDesignMatrix = rbfnKernelFunction(kernelCenters);
    // rbfnWeights = Eigen::MatrixXd::Zero(nDoF, nC);
    Eigen::MatrixXd wayTrans = waypoints.transpose();

    // std::cout << "phi = " << rbfnDesignMatrix.rows() << " x " << rbfnDesignMatrix.cols() << std::endl;
    // std::cout << "way = " << wayTrans.rows()<< " x " << wayTrans.cols() << std::endl;
    Eigen::MatrixXd A = rbfnDesignMatrix * rbfnDesignMatrix.transpose();
    // std::cout << "A = " << A.rows()<< " x " << A.cols() << std::endl;

    Eigen::MatrixXd b = rbfnDesignMatrix * wayTrans;

    // std::cout << "b = " << b.rows()<< " x " << b.cols() << std::endl;


    // rbfnWeights = (A.inverse() * b).transpose(); // the transpose makes weights = nDoF x nCenters which is better for the output function.

    // rbfnWeights = A.fullPivLu().solve(b).transpose();
    rbfnWeights = rbfnDesignMatrix.fullPivLu().solve(wayTrans).transpose();
    // std::cout << "rbfn weights:\n" << rbfnWeights << std::endl;

}