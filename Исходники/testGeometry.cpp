TEST(LIE_GROUP_OPERATORS, ADJOINT_MAPPINGS)
{
    int numTest = 100;

    // AdT(V) == T * V * InvT
    for (int i = 0; i < numTest; ++i)
    {
        Eigen::Vector6d t = Eigen::Vector6d::Random();
        Eigen::Isometry3d T = math::expMap(t);
        Eigen::Vector6d V = Eigen::Vector6d::Random();

        Eigen::Vector6d AdTV = AdT(T, V);

        // Ad(T, V) = T * [V] * InvT
        Eigen::Matrix4d T_V_InvT = T.matrix() * toMatrixForm(V) * T.inverse().matrix();
        Eigen::Vector6d T_V_InvT_se3 = fromMatrixForm(T_V_InvT);

        for (int j = 0; j < 6; ++j)
            EXPECT_NEAR(AdTV(j), T_V_InvT_se3(j), LIE_GROUP_OPT_TOL);

        // Ad(T, V) = [R 0; [p]R R] * V
        Eigen::Matrix6d AdTMatrix = Eigen::Matrix6d::Zero();
        AdTMatrix.topLeftCorner<3,3>() = T.linear();
        AdTMatrix.bottomRightCorner<3,3>() = T.linear();
        AdTMatrix.bottomLeftCorner<3,3>() = math::makeSkewSymmetric(T.translation()) * T.linear();
        Eigen::Vector6d AdTMatrix_V = AdTMatrix * V;
        for (int j = 0; j < 6; ++j)
            EXPECT_NEAR(AdTV(j), AdTMatrix_V(j), LIE_GROUP_OPT_TOL);
    }

    // AdR == AdT([R 0; 0 1], V)
    for (int i = 0; i < numTest; ++i)
    {
        Eigen::Vector6d t = Eigen::Vector6d::Random();
        Eigen::Isometry3d T = math::expMap(t);
        Eigen::Isometry3d R = Eigen::Isometry3d::Identity();
        R = T.linear();
        Eigen::Vector6d V = Eigen::Vector6d::Random();

        Eigen::Vector6d AdTV = AdT(R, V);
        Eigen::Vector6d AdRV = AdR(T, V);

        for (int j = 0; j < 6; ++j)
            EXPECT_NEAR(AdTV(j), AdRV(j), LIE_GROUP_OPT_TOL);
    }

    // AdTAngular == AdT(T, se3(w, 0))
    for (int i = 0; i < numTest; ++i)
    {
        Eigen::Vector6d t = Eigen::Vector6d::Random();
        Eigen::Isometry3d T = math::expMap(t);
        Eigen::Vector3d w = Eigen::Vector3d::Random();
        Eigen::Vector6d V = Eigen::Vector6d::Zero();
        V.head<3>() = w;

        Eigen::Vector6d AdTV = AdT(T, V);
        Eigen::Vector6d AdTAng = AdTAngular(T, w);

        for (int j = 0; j < 6; ++j)
            EXPECT_NEAR(AdTV(j), AdTAng(j), LIE_GROUP_OPT_TOL);
    }

    // AdTLinear == AdT(T, se3(w, 0))
    for (int i = 0; i < numTest; ++i)
    {
        Eigen::Vector6d t = Eigen::Vector6d::Random();
        Eigen::Isometry3d T = math::expMap(t);
        Eigen::Vector3d v = Eigen::Vector3d::Random();
        Eigen::Vector6d V = Eigen::Vector6d::Zero();
        V.tail<3>() = v;

        Eigen::Vector6d AdTV = AdT(T, V);
        Eigen::Vector6d AdTLin = AdTLinear(T, v);

        for (int j = 0; j < 6; ++j)
            EXPECT_NEAR(AdTV(j), AdTLin(j), LIE_GROUP_OPT_TOL);
    }

    // AdTJac
    for (int i = 0; i < numTest; ++i)
    {
        Eigen::Vector6d t = Eigen::Vector6d::Random();
        Eigen::Isometry3d T = math::expMap(t);
        Eigen::Vector3d v = Eigen::Vector3d::Random();
        Eigen::Vector6d V = Eigen::Vector6d::Zero();
        V.tail<3>() = v;

        Eigen::Vector6d AdTV = AdT(T, V);
        Eigen::Vector6d AdTLin = AdTLinear(T, v);

        for (int j = 0; j < 6; ++j)
            EXPECT_NEAR(AdTV(j), AdTLin(j), LIE_GROUP_OPT_TOL);
    }

    // AdInvT
    for (int i = 0; i < numTest; ++i)
    {
        Eigen::Vector6d t = Eigen::Vector6d::Random();
        Eigen::Isometry3d T = math::expMap(t);
        Eigen::Isometry3d InvT = T.inverse();
        Eigen::Vector6d V = Eigen::Vector6d::Random();

        Eigen::Vector6d Ad_InvT = AdT(InvT, V);
        Eigen::Vector6d AdInv_T = AdInvT(T, V);

        for (int j = 0; j < 6; ++j)
            EXPECT_NEAR(Ad_InvT(j), AdInv_T(j), LIE_GROUP_OPT_TOL);
    }

    // AdInvRLinear
    for (int i = 0; i < numTest; ++i)
    {
        Eigen::Vector6d t = Eigen::Vector6d::Random();
        Eigen::Isometry3d T = math::expMap(t);
        Eigen::Vector3d v = Eigen::Vector3d::Random();
        Eigen::Vector6d V = Eigen::Vector6d::Zero();
        V.tail<3>() = v;
        Eigen::Isometry3d R = Eigen::Isometry3d::Identity();
        R = T.linear();

        Eigen::Vector6d AdT_ = AdT(R.inverse(), V);
        Eigen::Vector6d AdInvRLinear_ = AdInvRLinear(T, v);

        for (int j = 0; j < 6; ++j)
            EXPECT_NEAR(AdT_(j), AdInvRLinear_(j), LIE_GROUP_OPT_TOL);
    }

    // dAdT
    for (int i = 0; i < numTest; ++i)
    {
        Eigen::Vector6d t = Eigen::Vector6d::Random();
        Eigen::Isometry3d T = math::expMap(t);
        Eigen::Vector6d F = Eigen::Vector6d::Random();

        Eigen::Vector6d dAdTF = dAdT(T, F);

        // dAd(T, F) = [R 0; [p]R R]^T * F
        Eigen::Matrix6d AdTMatrix = Eigen::Matrix6d::Zero();
        AdTMatrix.topLeftCorner<3,3>() = T.linear();
        AdTMatrix.bottomRightCorner<3,3>() = T.linear();
        AdTMatrix.bottomLeftCorner<3,3>() = math::makeSkewSymmetric(T.translation()) * T.linear();
        Eigen::Vector6d AdTTransMatrix_V = AdTMatrix.transpose() * F;
        for (int j = 0; j < 6; ++j)
            EXPECT_NEAR(dAdTF(j), AdTTransMatrix_V(j), LIE_GROUP_OPT_TOL);
    }

    // dAdInvT
    for (int i = 0; i < numTest; ++i)
    {
        Eigen::Vector6d t = Eigen::Vector6d::Random();
        Eigen::Isometry3d T = math::expMap(t);
        Eigen::Isometry3d InvT = T.inverse();
        Eigen::Vector6d F = Eigen::Vector6d::Random();

        Eigen::Vector6d dAdInvT_F = dAdInvT(T, F);

        //
        Eigen::Vector6d dAd_InvTF = dAdT(InvT, F);

        for (int j = 0; j < 6; ++j)
            EXPECT_NEAR(dAdInvT_F(j), dAd_InvTF(j), LIE_GROUP_OPT_TOL);

        // dAd(T, F) = [R 0; [p]R R]^T * F
        Eigen::Matrix6d AdInvTMatrix = Eigen::Matrix6d::Zero();
        AdInvTMatrix.topLeftCorner<3,3>() = InvT.linear();
        AdInvTMatrix.bottomRightCorner<3,3>() = InvT.linear();
        AdInvTMatrix.bottomLeftCorner<3,3>() = math::makeSkewSymmetric(InvT.translation()) * InvT.linear();
        Eigen::Vector6d AdInvTTransMatrix_V = AdInvTMatrix.transpose() * F;
        for (int j = 0; j < 6; ++j)
            EXPECT_NEAR(dAdInvT_F(j), AdInvTTransMatrix_V(j), LIE_GROUP_OPT_TOL);
    }

    // dAdInvR
    for (int i = 0; i < numTest; ++i)
    {
        Eigen::Vector6d t = Eigen::Vector6d::Random();
        Eigen::Isometry3d T = math::expMap(t);
        Eigen::Isometry3d InvT = T.inverse();
        Eigen::Isometry3d InvR = Eigen::Isometry3d::Identity();
        InvR = InvT.linear();
        Eigen::Vector6d F = Eigen::Vector6d::Random();

        Eigen::Vector6d dAdInvR_F = dAdInvR(T, F);

        //
        Eigen::Vector6d dAd_InvTF = dAdT(InvR, F);

        for (int j = 0; j < 6; ++j)
            EXPECT_NEAR(dAdInvR_F(j), dAd_InvTF(j), LIE_GROUP_OPT_TOL);
    }

    // ad
    for (int i = 0; i < numTest; ++i)
    {
        Eigen::Vector6d V = Eigen::Vector6d::Random();
        Eigen::Vector6d W = Eigen::Vector6d::Random();

        Eigen::Vector6d ad_V_W = ad(V, W);

        //
        Eigen::Matrix6d adV_Matrix = Eigen::Matrix6d::Zero();
        adV_Matrix.topLeftCorner<3,3>() = math::makeSkewSymmetric(V.head<3>());
        adV_Matrix.bottomRightCorner<3,3>() = math::makeSkewSymmetric(V.head<3>());
        adV_Matrix.bottomLeftCorner<3,3>() = math::makeSkewSymmetric(V.tail<3>());
        Eigen::Vector6d adV_Matrix_W = adV_Matrix * W;

        for (int j = 0; j < 6; ++j)
            EXPECT_NEAR(ad_V_W(j), adV_Matrix_W(j), LIE_GROUP_OPT_TOL);
    }

    // dad
    for (int i = 0; i < numTest; ++i)
    {
        Eigen::Vector6d V = Eigen::Vector6d::Random();
        Eigen::Vector6d F = Eigen::Vector6d::Random();

        Eigen::Vector6d dad_V_F = dad(V, F);

        //
        Eigen::Matrix6d dadV_Matrix = Eigen::Matrix6d::Zero();
        dadV_Matrix.topLeftCorner<3,3>() = math::makeSkewSymmetric(V.head<3>());
        dadV_Matrix.bottomRightCorner<3,3>() = math::makeSkewSymmetric(V.head<3>());
        dadV_Matrix.bottomLeftCorner<3,3>() = math::makeSkewSymmetric(V.tail<3>());
        Eigen::Vector6d dadV_Matrix_F= dadV_Matrix.transpose() * F;

        for (int j = 0; j < 6; ++j)
            EXPECT_NEAR(dad_V_F(j), dadV_Matrix_F(j), LIE_GROUP_OPT_TOL);
    }
}