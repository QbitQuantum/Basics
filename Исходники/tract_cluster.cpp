TractCluster::TractCluster(const float* param):error_distance(param[3])
{
    image::vector<3,float> fdim(param);
    fdim /= error_distance;
    fdim += 1.0;
    fdim.floor();
    dim[0] = fdim[0];
    dim[1] = fdim[1];
    dim[2] = fdim[2];
    w = dim[0];
    wh = dim[0]*dim[1];
    voxel_connection.resize(dim.size());

}