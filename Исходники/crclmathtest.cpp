tf::Matrix3x3 GetTfRotationMatrix(tf::Vector3 xaxis, tf::Vector3 zaxis) {
    tf::Matrix3x3 m;
    tf::Vector3 yaxis = zaxis.cross(xaxis);
    m.setValue(xaxis.getX(), yaxis.getX(), zaxis.getX(),
            xaxis.getY(), yaxis.getY(), zaxis.getY(),
            xaxis.getZ(), yaxis.getZ(), zaxis.getZ());
    return m;
}