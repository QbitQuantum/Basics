        // Original code from the ROS vslam package pe3d.cpp
        // uses the SVD procedure for aligning point clouds
        //   SEE: Arun, Huang, Blostein: Least-Squares Fitting of Two 3D Point Sets
        Eigen::Matrix4d threePointSvd(Eigen::MatrixXd const & p0, Eigen::MatrixXd const & p1)
        {
            using namespace Eigen;

            SM_ASSERT_EQ_DBG(std::runtime_error, p0.rows(), 3, "p0 must be a 3xK matrix");
            SM_ASSERT_EQ_DBG(std::runtime_error, p1.rows(), 3, "p1 must be a 3xK matrix");
            SM_ASSERT_EQ_DBG(std::runtime_error, p0.cols(), p1.cols(), "p0 and p1 must have the same number of columns");

            Vector3d c0 = p0.rowwise().mean();
            Vector3d c1 = p1.rowwise().mean();

            Matrix3d H(Matrix3d::Zero());
            // subtract out
            // p0a -= c0;
            // p0b -= c0;
            // p0c -= c0;
            // p1a -= c1;
            // p1b -= c1;
            // p1c -= c1;

            // Matrix3d H = p1a*p0a.transpose() + p1b*p0b.transpose() +
            // 	p1c*p0c.transpose();
            for(int i = 0; i < p0.cols(); ++i)
            {
                H += (p0.col(i) - c0) * (p1.col(i) - c1).transpose();
            }
      

            // do the SVD thang
            JacobiSVD<Matrix3d> svd(H,ComputeFullU | ComputeFullV);
            Matrix3d V = svd.matrixV();
            Matrix3d R = V * svd.matrixU().transpose();          
            double det = R.determinant();
        
            if (det < 0.0)
            {
                V.col(2) = V.col(2) * -1.0;
                R = V * svd.matrixU().transpose();
            }
            Vector3d tr = c0-R.transpose()*c1;    // translation 
      
            // transformation matrix, 3x4
            Matrix4d tfm(Matrix4d::Identity());
            //        tfm.block<3,3>(0,0) = R.transpose();
            //        tfm.col(3) = -R.transpose()*tr;
            tfm.topLeftCorner<3,3>() = R.transpose();
            tfm.topRightCorner<3,1>() = tr;
      
            return tfm;
      
        }