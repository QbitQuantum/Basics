void inverseTransform(Eigen::Vector3d &src, cspace config, Eigen::Vector3d &dest)
{
    Eigen::Matrix3d rotationC;
    rotationC << cos(config[5]), -sin(config[5]), 0,
               sin(config[5]), cos(config[5]), 0,
               0, 0, 1;
    Eigen::Matrix3d rotationB;
    rotationB << cos(config[4]), 0 , sin(config[4]),
               0, 1, 0,
               -sin(config[4]), 0, cos(config[4]);
    Eigen::Matrix3d rotationA;
    rotationA << 1, 0, 0 ,
               0, cos(config[3]), -sin(config[3]),
               0, sin(config[3]), cos(config[3]);
    Eigen::Vector3d transitionV(config[0], config[1], config[2]);
    Eigen::Matrix3d rotationM = rotationC * rotationB * rotationA;
    dest = rotationM.inverse() * (src - transitionV);
}