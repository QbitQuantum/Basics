static void
write_calibration_parameter(
    const Eigen::Vector3f &in_vector,
    PSMoveProtocol::FloatVector *out_vector)
{
    out_vector->set_i(in_vector.x());
    out_vector->set_j(in_vector.y());
    out_vector->set_k(in_vector.z());
}