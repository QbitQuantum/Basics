    bool operator() (const T* const q_coeffs, const T* const t_coeffs, const T* const s, T* residuals) const
    {
        T q_ceres[4] = {q_coeffs[3], q_coeffs[0], q_coeffs[1], q_coeffs[2]};
        Eigen::Matrix<T,3,3> R;
        ceres::QuaternionToRotation(q_ceres, ceres::ColumnMajorAdapter3x3(R.data()));

        Eigen::Matrix<T,4,4> H = Eigen::Matrix<T,4,4>::Identity();
        H.block(0,0,3,3) = *s * R;
        H(0,3) = t_coeffs[0];
        H(1,3) = t_coeffs[1];
        H(2,3) = t_coeffs[2];

        Eigen::Matrix<T,4,4> pred_H2 = H * m_H1.cast<T>() * H.inverse();

        Eigen::Matrix<T,4,4> err_H = m_H2.cast<T>().inverse() * pred_H2;
        Eigen::Matrix<T,3,3> err_R = err_H.block(0,0,3,3);

        T roll, pitch, yaw;
        mat2RPY(err_R, roll, pitch, yaw);

        residuals[0] = err_H(0,3);
        residuals[1] = err_H(1,3);
        residuals[2] = err_H(2,3);

        residuals[3] = roll;
        residuals[4] = pitch;
        residuals[5] = yaw;

        return true;
    }