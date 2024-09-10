// Return the name of the handrail that intersects with the given pose.
std::string getHandrailAtPose(const ISSWorld& world, const Eigen::Affine3d& pose)
{
    unsigned int handrail_idx = world.findHandrail(pose.translation());
    if (handrail_idx < world.numHandrails())
        return world.getHandrail(handrail_idx)->name;

    return "";  // no handrail at pose
}