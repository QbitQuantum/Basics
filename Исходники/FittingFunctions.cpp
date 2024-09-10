// ------------------------------------------------------------------------
void startingPlane(const std::vector<MatrixType> &pointsData, VectorType &point, VectorType &normal)
{
    // put into a big matrix
    unsigned int count = 0;
    std::vector<MatrixType> flattened;
    for(unsigned int i = 0; i < pointsData.size(); i++)
    {

        std::cout << pointsData[i].cols() << std::endl;
        if(pointsData[i].cols() == 6)
        {
            MatrixType flat = MatrixType(1, 6*3);
            for(unsigned int j = 0; j < 3; j++)
            {
                for(unsigned int k = 0; k < 6; k++)
                {
                    flat(0, k*3+j) = pointsData[i](k, j);
                }

            }
            flattened.push_back(flat);
            count++;
        }

    }



    MatrixType allPlanes = MatrixType(count, 6*3);
    for(unsigned int i = 0; i < count; i++)
    {
        allPlanes.row(i) = flattened[i].row(0);
    }


    allPlanes = allPlanes.colwise() - allPlanes.rowwise().mean();

    // get the mean
    MatrixType mean = allPlanes.colwise().mean();

    // reshape into P
    MatrixType P = MatrixType(3,6);
    for(unsigned int i = 0; i < 3; i++)
    {
        for(unsigned int j = 0; j < 6; j++)
        {
            P(i,j) = mean(0,j*3+i);
        }
    }




    // subtract the mean from the points
    MatrixType centroid = P.rowwise().mean();
    P = P.colwise() - P.rowwise().mean();
    MatrixType C = P*P.transpose();

    // get the eigen vectors
    Eigen::SelfAdjointEigenSolver<MatrixType> solver(C);

    normal = solver.eigenvectors().col(0);
    point = centroid.transpose();
}