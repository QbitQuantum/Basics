// Get faster traversability
bool TensorMap::isEasilyTraversable(const CellKey& key) {
    TensorCell& cell((*this)[key]);
    // check cache
    if (cell.traversability!=UNKNOWN) {
        return (cell.traversability==OK);
    }
    // compute it
    const bool v = false;

    // getting parameters
    const TraversabilityParams& params = tensor_map_params->traversability;
    const float min_stick_sal = params.min_saliency;
    const float max_orientation_angle = params.max_slope;
    const int stick_sal_threshold = params.max_points_in_free_cell;
    const float min_free_cell_ratio = params.min_free_cell_ratio;
    const int nb_max_points = params.max_points_in_bounding_box;
    const int nb_min_support = params.min_support_points;
    const float diameter = params.diameter;
    const float d_2 = diameter/2. + params.inflation;
    const float r2 = d_2*d_2;
    const float height = params.height;
    const float ground_buffer = params.ground_buffer;
    const float buf2 = ground_buffer/2;
    const float h_2 = height/2;
    const float h0_2 = (height + buf2)/2;
    const float h1_2 = (height - buf2)/2;

    // check for enough saliency
    if (cell.stick_sal<min_stick_sal) {
        if (v) {
            cout << "Saliency too low: "<<cell.stick_sal<<"/"<<
                 min_stick_sal<<endl;
        }
        cell.traversability = NOT_SALIENCY;
        return false;
    }
    // check orientation is correct
    if (cell.angle_to_vertical>max_orientation_angle) {
        if (v) {
            cout << "Angle too steep: "<<cell.angle_to_vertical<<"/"<<
                 max_orientation_angle<<endl;
        }
        cell.traversability = NOT_ANGLE;
        return false;
    }
    /*
     * check absence of obstacle
     */
    // align orientation to surface
    Matrix3f alignedAxes;
    geometry_msgs::Quaternion quat;
    quat.x = quat.y = quat.z = 0;
    quat.w = 1;
    alignQuaternion(quat, cell.normal, alignedAxes);
    Vector3f x = alignedAxes.col(0);
    Vector3f y = alignedAxes.col(1);
    Vector3f z = alignedAxes.col(2);
    // generate bounding box
    Vector3f max_corner = d_2*x.array().abs()+\
                          d_2*y.array().abs()+\
                          h0_2*z.array().abs();
    Vector3f center = cell.position + h_2*z;
    CellKey min_key = positionToIndex(center - max_corner);
    CellKey max_key = positionToIndex(center + max_corner);
    // shifted up to separate support layer FIXME
    center += buf2/2*z;
    // look through bounding box for possible obstacles
    float nb_robot_cells = 0.;
    float nb_ok_robot_cells = 0.;
    int nb_points_in_cells = 0;
    int nb_support_points = 0;
    for (int i=min_key.i; i<max_key.i+1; ++i)
        for (int j=min_key.j; j<max_key.j+1; ++j)
            for (int k=min_key.k; k<max_key.k+1; ++k) {
                // check cell is in the robot
                TensorCell c = (*this)[CellKey(i, j, k)];
                Vector3f rel_pos = c.position - center;
                Vector3f rel_pos_aligned = alignedAxes.transpose()*rel_pos;
                float rel_x, rel_y, rel_z;
                rel_x = rel_pos_aligned(0);
                rel_y = rel_pos_aligned(1);
                rel_z = rel_pos_aligned(2);
                if (pow(rel_x, 2)+pow(rel_y, 2)>r2) {
                    continue;
                }
                if (fabs(rel_z)>h1_2) {
                    if (fabs(rel_z+h_2)<buf2) {
                        nb_support_points += c.nb_points;
                    }
                } else {
                    // check no obstacle
                    nb_robot_cells += 1;
                    if (c.nb_points<=stick_sal_threshold) {
                        nb_ok_robot_cells += 1;
                    } else if (c.angle_to_vertical <= max_orientation_angle) {
                        nb_ok_robot_cells += 1;
                        nb_points_in_cells += c.nb_points;
                    }
                }
            }
    // exit if not enough free cells
    if ((nb_ok_robot_cells/nb_robot_cells)<min_free_cell_ratio)
    {
        if (v) {
            cout << "not enough free cells: "<<
                 nb_ok_robot_cells<<"/"<<
                 min_free_cell_ratio*nb_robot_cells<<" ("<<
                 nb_robot_cells<<")"<<endl;
        }
        cell.traversability = NOT_OBSTACLE;
        return false;
    }
    if (nb_points_in_cells>nb_max_points) {
        if (v) {
            cout << "too many (ground) points in cells: "<<
                 nb_points_in_cells<<"/"<<nb_max_points<<endl;
        }
        cell.traversability = NOT_IN_GROUND;
        return false;
    }
    if (nb_support_points<nb_min_support) {
        if (v) {
            cout << "too few support points in cells: "<<
                 nb_support_points<<"/"<<nb_min_support<<endl;
        }
        cell.traversability = NOT_IN_AIR;
        return false;
    }
    // cell seems valid
    if (v) {
        cout << "valid" << endl;
    }
    cell.traversability = OK;
    return true;
}