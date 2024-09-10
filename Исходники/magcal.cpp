void MagCal::calcMagComp()
{
    /*
     * Inspired by
     * http://davidegironi.blogspot.it/2013/01/magnetometer-calibration-helper-01-for.html#.UriTqkMjulM
     *
     * Ellipsoid fit from:
     * http://www.mathworks.com/matlabcentral/fileexchange/24693-ellipsoid-fit
     *
     * To use Eigen to convert matlab code, have a look at Eigen/AsciiQuickReference.txt
     */

    if (mMagSamples.size() < 9) {
        QMessageBox::warning(this, "Magnetometer compensation",
                             "Too few points.");
        return;
    }

    int samples = mMagSamples.size();
    Eigen::VectorXd ex(samples);
    Eigen::VectorXd ey(samples);
    Eigen::VectorXd ez(samples);

    for (int i = 0;i < samples;i++) {
        ex(i) = mMagSamples.at(i).at(0);
        ey(i) = mMagSamples.at(i).at(1);
        ez(i) = mMagSamples.at(i).at(2);
    }

    Eigen::MatrixXd eD(samples, 9);

    for (int i = 0;i < samples;i++) {
        eD(i, 0) = ex(i) * ex(i);
        eD(i, 1) = ey(i) * ey(i);
        eD(i, 2) = ez(i) * ez(i);
        eD(i, 3) = 2.0 * ex(i) * ey(i);
        eD(i, 4) = 2.0 * ex(i) * ez(i);
        eD(i, 5) = 2.0 * ey(i) * ez(i);
        eD(i, 6) = 2.0 * ex(i);
        eD(i, 7) = 2.0 * ey(i);
        eD(i, 8) = 2.0 * ez(i);
    }

    Eigen::MatrixXd etmp1 = eD.transpose() * eD;
    Eigen::MatrixXd etmp2 = eD.transpose() * Eigen::MatrixXd::Ones(samples, 1);
    Eigen::VectorXd eV = etmp1.lu().solve(etmp2);

    Eigen::MatrixXd eA(4, 4);
    eA(0,0)=eV(0);   eA(0,1)=eV(3);   eA(0,2)=eV(4);   eA(0,3)=eV(6);
    eA(1,0)=eV(3);   eA(1,1)=eV(1);   eA(1,2)=eV(5);   eA(1,3)=eV(7);
    eA(2,0)=eV(4);   eA(2,1)=eV(5);   eA(2,2)=eV(2);   eA(2,3)=eV(8);
    eA(3,0)=eV(6);   eA(3,1)=eV(7);   eA(3,2)=eV(8);   eA(3,3)=-1.0;

    Eigen::MatrixXd eCenter = -eA.topLeftCorner(3, 3).lu().solve(eV.segment(6, 3));
    Eigen::MatrixXd eT = Eigen::MatrixXd::Identity(4, 4);
    eT(3, 0) = eCenter(0);
    eT(3, 1) = eCenter(1);
    eT(3, 2) = eCenter(2);

    Eigen::MatrixXd eR = eT * eA * eT.transpose();

    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eEv(eR.topLeftCorner(3, 3) * (-1.0 / eR(3, 3)));
    Eigen::MatrixXd eVecs = eEv.eigenvectors();
    Eigen::MatrixXd eVals = eEv.eigenvalues();

    Eigen::MatrixXd eRadii(3, 1);
    eRadii(0) = sqrt(1.0 / eVals(0));
    eRadii(1) = sqrt(1.0 / eVals(1));
    eRadii(2) = sqrt(1.0 / eVals(2));

    Eigen::MatrixXd eScale = eRadii.asDiagonal().inverse() * eRadii.minCoeff();
    Eigen::MatrixXd eComp = eVecs * eScale * eVecs.transpose();

    mMagComp.resize(9);
    mMagComp[0] = eComp(0, 0);
    mMagComp[1] = eComp(0, 1);
    mMagComp[2] = eComp(0, 2);

    mMagComp[3] = eComp(1, 0);
    mMagComp[4] = eComp(1, 1);
    mMagComp[5] = eComp(1, 2);

    mMagComp[6] = eComp(2, 0);
    mMagComp[7] = eComp(2, 1);
    mMagComp[8] = eComp(2, 2);

    mMagCompCenter.resize(3);
    mMagCompCenter[0] = eCenter(0, 0);
    mMagCompCenter[1] = eCenter(1, 0);
    mMagCompCenter[2] = eCenter(2, 0);

    QVector<double> magX, magY, magZ;

    for (int i = 0;i < mMagSamples.size();i++) {
        double mx = mMagSamples.at(i).at(0);
        double my = mMagSamples.at(i).at(1);
        double mz = mMagSamples.at(i).at(2);

        mx -= mMagCompCenter.at(0);
        my -= mMagCompCenter.at(1);
        mz -= mMagCompCenter.at(2);

        magX.append(mx * mMagComp.at(0) + my * mMagComp.at(1) + mz * mMagComp.at(2));
        magY.append(mx * mMagComp.at(3) + my * mMagComp.at(4) + mz * mMagComp.at(5));
        magZ.append(mx * mMagComp.at(6) + my * mMagComp.at(7) + mz * mMagComp.at(8));
    }

    ui->magSampXyPlot->graph(1)->setData(magX, magY);
    ui->magSampXzPlot->graph(1)->setData(magX, magZ);
    ui->magSampYzPlot->graph(1)->setData(magY, magZ);

    updateMagPlots();
}