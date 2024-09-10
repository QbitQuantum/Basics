// Compute a rotation required to transform "estimated" into "measured"
// Returns an approximation of the goal rotation in the Simultaneous Orthogonal Rotations Angle representation
// (vector direction is the axis of rotation, norm is the angle)
Vector3f SensorFusion_ComputeCorrection(Vector3f measured, Vector3f estimated)
{
    measured.Normalize();
    estimated.Normalize();
    Vector3f correction = measured.Cross(estimated);
    float cosError = measured.Dot(estimated);
    // from the def. of cross product, correction.Length() = sin(error)
    // therefore sin(error) * sqrt(2 / (1 + cos(error))) = 2 * sin(error / 2) ~= error in [-pi, pi]
    // Mathf::Tolerance is used to avoid div by 0 if cos(error) = -1
    return correction * sqrt(2 / (1 + cosError + Mathf::Tolerance));
}