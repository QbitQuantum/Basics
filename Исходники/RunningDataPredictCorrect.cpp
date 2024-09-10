void VideoIMUFusion::RunningData::handleIMUVelocity(
    const OSVR_TimeValue &timestamp, const Eigen::Vector3d &angVel) {
#ifdef OSVR_FPE
    FPExceptionEnabler fpe;
#endif

    if (preReport(timestamp)) {

#if 0
        static int s = 0;
        if (s == 0) {
            static const Eigen::IOFormat fmt(3, 0, ", ", ";\n", "", "", "[",
                                             "]");
            OSVR_DEV_VERBOSE(
                "\nprediction: "
                << state().getAngularVelocity().transpose().format(fmt)
                << "\nMeasurement: " << angVel.transpose().format(fmt)
                << "\nVariance: "
                << state()
                       .errorCovariance()
                       .diagonal()
                       .tail<3>()
                       .transpose()
                       .format(fmt));
        }
        s = (s + 1) % 100;
#endif

        m_imuMeasVel.setMeasurement(angVel);
        osvr::kalman::correct(state(), processModel(), m_imuMeasVel);
    }
}