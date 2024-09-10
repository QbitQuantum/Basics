void EpicNavCorePlugin::initialize(std::string name, costmap_2d::Costmap2DROS *costmap_ros)
{
    if (name.length() == 0 || costmap_ros == nullptr) {
        ROS_ERROR("Error[EpicNavCorePlugin::initialize]: Costmap2DROS object is not initialized.");
        return;
    }

    uninitialize();

    costmap = costmap_ros->getCostmap();

    harmonic.n = 2;
    harmonic.m = new unsigned int[2];
    harmonic.m[0] = costmap->getSizeInCellsY();
    harmonic.m[1] = costmap->getSizeInCellsX();

    harmonic.u = new float[costmap->getSizeInCellsX() * costmap->getSizeInCellsY()];
    harmonic.locked = new unsigned int[costmap->getSizeInCellsX() * costmap->getSizeInCellsY()];

    setCellsFromCostmap();
    setBoundariesAsObstacles();

    ros::NodeHandle privateNodeHandle("~/" + name);
    pub_plan = privateNodeHandle.advertise<nav_msgs::Path>("plan", 1);
    //pub_potential = privateNodeHandle.advertise<nav_msgs::OccupancyGrid>("potential", 1);

    initialized = true;
}