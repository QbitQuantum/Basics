Eigen::Matrix3d Bd970::getPositionUncertainty(void)
{
    Eigen::Matrix3d position_uncertainty;

    Eigen::Vector3d eigenvalues; // eigen values are the square of the std deviation
    eigenvalues << m_current_nmea.data_gst.semi_major_axis_sigma_error *
                m_current_nmea.data_gst.semi_major_axis_sigma_error,
                m_current_nmea.data_gst.semi_minor_axis_sigma_error *
                m_current_nmea.data_gst.semi_minor_axis_sigma_error,
                m_current_nmea.data_gst.height_sigma_error *
                m_current_nmea.data_gst.height_sigma_error;

    Eigen::Matrix3d U = this->getOrientation().matrix();
    position_uncertainty = U * eigenvalues.array().matrix().asDiagonal() * U.transpose();

    return position_uncertainty;
}