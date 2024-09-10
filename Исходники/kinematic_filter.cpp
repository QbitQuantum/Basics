void kinematic_filter::setWorld_StanceFoot(const KDL::Frame& World_StanceFoot)
{
    this->StanceFoot_World=World_StanceFoot.Inverse();
    this->World_StanceFoot=World_StanceFoot;
}