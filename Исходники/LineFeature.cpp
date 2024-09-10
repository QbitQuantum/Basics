    /**
     * input needs at least 2 correspondences of non-parallel lines
     * the resulting R and t works as below: x'=Rx+t for point pair(x,x');
     * @param vLineA
     * @param vLineB
     * @param R
     * @param t
     */
    void
    LineExtract::ComputeRelativeMotion_svd(vector<Line3d> vLineA, vector<Line3d> vLineB, Matrix3d &R, Vector3d &t) {
        if (vLineA.size() < 2) {
            cerr << "Error in computeRelativeMotion_svd: input needs at least 2 pairs!\n";
            return;
        }
        // convert to the representation of Zhang's paper
        for (int i = 0; i < vLineA.size(); ++i) {
            Vector3d l, m;
            if (vLineA[i].u.norm() < 0.9) {
                l = vLineA[i].EndB - vLineA[i].EndA;
                m = (vLineA[i].EndA + vLineA[i].EndB) * 0.5;
                vLineA[i].u = l / l.norm();
                vLineA[i].d = vLineA[i].u.cross(m);
                //	cout<<"in computeRelativeMotion_svd compute \n";
            }
            if (vLineB[i].u.norm() < 0.9) {
                l = vLineB[i].EndB - vLineB[i].EndA;
                m = (vLineB[i].EndA + vLineB[i].EndB) * 0.5;
                vLineB[i].u = l * (1 / l.norm());
                vLineB[i].d = vLineB[i].u.cross(m);
            }
        }

        Matrix4d A = Matrix4d::Zero();
        for (int i = 0; i < vLineA.size(); ++i) {
            Matrix4d Ai = Matrix4d::Zero();
            Ai.block<1, 3>(0, 1) = vLineA[i].u - vLineB[i].u;
            Ai.block<3, 1>(1, 0) = vLineB[i].u - vLineA[i].u;

            Ai.bottomRightCorner<3, 3>(1, 1) = SO3d::hat((vLineA[i].u + vLineB[i].u)).matrix();
            A = A + Ai.transpose() * Ai;
        }
        Eigen::JacobiSVD<Matrix4d> svd(A, Eigen::ComputeFullV | Eigen::ComputeFullV);

        Vector4d q = svd.matrixU().col(3);
        R = Eigen::Quaterniond(q).matrix();

        Matrix3d uu = Matrix3d::Zero();
        Vector3d udr = Vector3d::Zero();
        for (int i = 0; i < vLineA.size(); ++i) {
            uu = uu + SO3d::hat(vLineB[i].u) * SO3d::hat(vLineB[i].u).matrix().transpose();
            udr = udr + SO3d::hat(vLineB[i].u).transpose() * (vLineB[i].d - R * vLineA[i].d);
        }
        t = uu.inverse() * udr;
    }