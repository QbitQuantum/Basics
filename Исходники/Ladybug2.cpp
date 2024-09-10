/** Convert transform in local (camera) coordinates to global (ladybug) coordinates.
 * @param Eigen::Matrix4f transform in local coordinates
 * @param int index of the previous camera
 * @param int index of the current camera
 * @return Eigen::Matrix4f transform in global coordinates */
Eigen::Matrix4f Ladybug2::cam2LadybugRef(Eigen::Matrix4f TLocal, int camNoPrev, int camNoCurr)
{
    Eigen::Matrix4f TGlobal = extrinsics_[camNoPrev] * TLocal.inverse() * extrinsics_[camNoCurr].inverse();
    return TGlobal;
}