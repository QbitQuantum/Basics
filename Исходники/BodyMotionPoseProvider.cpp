bool BodyMotionPoseProvider::getBaseLinkPosition(Position& out_T) const
{
    out_T.linear() = R_waist;
    out_T.translation() = p_waist;
    return true;
}