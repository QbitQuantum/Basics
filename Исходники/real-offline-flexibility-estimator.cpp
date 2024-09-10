int test (const IndexedMatrixArray & y, const IndexedMatrixArray & u)
{
    /// The number of samples
    const unsigned stateSize = 18;



    ///the initalization of an estimation of the initial state
    Vector xh0=Vector::Zero(stateSize,1);

    std::vector<Vector3, Eigen::aligned_allocator<Vector3> > contactPositions;

    contactPositions.push_back(Matrix::Zero(3,0));

    stateObservation::IndexedMatrixArray xh=
        stateObservation::examples::offlineEKFFlexibilityEstimation
        (y,u,xh0,1,contactPositions,dt);

    ///file of output
    std::ofstream f;
    f.open("trajectory.dat");

    double error;

    ///the reconstruction of the state
    for (unsigned i=y.getFirstIndex();i<=y.getLastIndex();++i)
    {
        ///display part, useless
        Vector3 g;
        {
            g = Vector(y[i]).head(3);
            g.normalize();
        }

        Vector3 gh;
        {
            Matrix3 Rh;

            Vector3 orientationV=Vector(xh[i]).segment(kine::ori,3);
            double angle=orientationV.norm();
            if (angle > cst::epsilonAngle)
                Rh = AngleAxis(angle, orientationV/angle).toRotationMatrix();
            else
                Rh = Matrix3::Identity();
            gh=Rh.transpose()*Vector3::UnitZ();
            gh.normalize();
        }

        error = acos(double(g.transpose()*gh)) * 180 / M_PI;


        f << i<< " \t "<< error << " \t\t\t "
          << g.transpose() << " \t\t\t " << gh.transpose() << " \t\t\t "
          << xh[i].transpose() << std::endl;
    }

    std::cout << "Error " << error << ", test: " ;

    if (error > 2)
    {
        std::cout << "FAILED !!!!!!!";
        return 1;
    }
    else
    {
        std::cout << "SUCCEEDED !!!!!!!";
        return 0;
    }
}