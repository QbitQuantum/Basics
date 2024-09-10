cloud_normal_t::Ptr
read_scan_with_normals(e57::Reader& reader, uint32_t scan_index,
                       const Eigen::Vector3d& demean_offset) {
    e57::Data3D header;
    reader.ReadData3D(scan_index, header);
    int64_t nColumn = 0, nRow = 0, nPointsSize = 0, nGroupsSize = 0,
            nCounts = 0;
    bool bColumnIndex = 0;
    reader.GetData3DSizes(scan_index, nRow, nColumn, nPointsSize, nGroupsSize,
                          nCounts, bColumnIndex);

    int64_t n_size = (nRow > 0) ? nRow : 1024;

    double* data_x = new double[n_size], * data_y = new double[n_size],
            * data_z = new double[n_size];
    double* nrm_x = new double[n_size], * nrm_y = new double[n_size],
            * nrm_z = new double[n_size];
    int8_t valid_normals = 0;
    auto block_read = reader.SetUpData3DPointsData(
        scan_index, n_size, data_x, data_y, data_z, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, nrm_x, nrm_y, nrm_z, &valid_normals);

    Eigen::Affine3d rotation;
    rotation =
        Eigen::Quaterniond(header.pose.rotation.w, header.pose.rotation.x,
                           header.pose.rotation.y, header.pose.rotation.z);
    Eigen::Affine3d registration;
    registration = Eigen::Translation<double, 3>(
                       header.pose.translation.x + demean_offset[0],
                       header.pose.translation.y + demean_offset[1],
                       header.pose.translation.z + demean_offset[2]) *
                   rotation;
    Eigen::Affine3d normal_transformation;
    normal_transformation = rotation.matrix().inverse().transpose();

    unsigned long size = 0;
    cloud_normal_t::Ptr scan(new cloud_normal_t());
    while ((size = block_read.read()) > 0) {
        for (unsigned long i = 0; i < size; i++) {
            point_normal_t p;
            Eigen::Vector3d pos(data_x[i], data_y[i], data_z[i]);
            pos = registration * pos;
            p.x = static_cast<float>(pos[0]);
            p.y = static_cast<float>(pos[1]);
            p.z = static_cast<float>(pos[2]);
            Eigen::Vector3d nrm(nrm_x[i], nrm_y[i], nrm_z[i]);
            nrm = normal_transformation * nrm;
            p.normal[0] = static_cast<float>(nrm[0]);
            p.normal[1] = static_cast<float>(nrm[1]);
            p.normal[2] = static_cast<float>(nrm[2]);
            scan->push_back(p);
        }
    }
    block_read.close();

    delete[] data_x;
    delete[] data_y;
    delete[] data_z;
    delete[] nrm_x;
    delete[] nrm_y;
    delete[] nrm_z;

    // get origin position
    scan->sensor_origin_ =
        Eigen::Vector4f(header.pose.translation.x + demean_offset[0],
                        header.pose.translation.y + demean_offset[1],
                        header.pose.translation.z + demean_offset[2], 1.0);

    return scan;
}