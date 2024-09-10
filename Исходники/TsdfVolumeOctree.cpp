    pcl::PointCloud<pcl::PointNormal>::Ptr TSDFVolumeOctree::renderView (const Eigen::Affine3d& trans, int downsampleBy) const {
        int new_width = image_width_ / downsampleBy;
        int new_height = image_height_ / downsampleBy;
        double new_fx = focal_length_x_ / downsampleBy;
        double new_fy = focal_length_y_ / downsampleBy;
        double new_cx = principal_point_x_ / downsampleBy;
        double new_cy = principal_point_y_ / downsampleBy;
        pcl::PointCloud<pcl::PointNormal>::Ptr cloud (new pcl::PointCloud<pcl::PointNormal> (new_width, new_height));
        cloud->is_dense = false;

        float min_step = max_dist_neg_ * 3/4.;
    #pragma omp parallel for
        for (size_t i = 0; i < cloud->size (); ++i) {
            size_t x = i % new_width;
            size_t y = i / new_width;
            //Raytrace
            pcl::PointNormal& pt = cloud->operator() (x,y);
            bool found_crossing = false;
            Eigen::Vector3f du ( (x - new_cx)/new_fx,
                                 (y - new_cy)/new_fy,
                                 1);
            du.normalize ();
            //Apply transform -- rotate the ray, start at the offset
            du = trans.rotation ().cast<float> () * du;
            Eigen::Vector3f p = trans.translation ().cast<float> ();
            //Preallocate
            int x_i, y_i, z_i;
            float d;
            float w;
            float last_w = 0;
            float last_d = 0;
            float t = min_sensor_dist_;
            p += t*du;
            float step = min_step;
            //Check if ray intersects cube
            //Initially we haven't ever hit a voxel
            bool hit_voxel = false;
            int niter = 0;
            while (t < max_sensor_dist_) {
                const OctreeNode* voxel = octree_->getContainingVoxel (p (0), p(1), p(2));
                if (voxel) {
                    hit_voxel = true;
                    voxel->getData (d, w);
                    if (((d < 0 && last_d > 0) || (d > 0 && last_d < 0)) && last_w && w) {
                        found_crossing = true;
                        float old_t = t - step;
                        step = (zsize_/zres_)/2;
                        float new_d;
                        float new_w;
                        float last_new_d = d;
                        float last_new_w = w;
                        while (t >= old_t) {
                            t -= step;
                            p -= step*du;
                            voxel = octree_->getContainingVoxel (p (0), p(1), p(2));
                            if (!voxel)
                                break;
                            voxel->getData (new_d, new_w);
                            if ((last_d > 0 && new_d > 0) || (last_d < 0 && new_d < 0)) {
                                last_d = new_d;
                                last_w = new_w;
                                d = last_new_d;
                                w = last_new_w;
                                t += step;
                                p += step*du;
                                break;
                            }
                            last_new_d = d;
                            last_new_w = w;
                        }
                        break;
                    }
                    last_d = d;
                    last_w = w;
                    //Update step
                    step = std::max (voxel->getMinSize () / 4., fabs (d)*max_dist_neg_);
                }
                else {
                    if (hit_voxel)
                        break;
                }
                t += step;
                p += step*du;
                niter++;
            }
            if (!found_crossing) {
                pt.x = pt.y = pt.z =std::numeric_limits<float>::quiet_NaN();
            }
            else {
                //Get optimal t
                bool has_data = true;
                float tcurr = t;
                float tprev = t-step;
                last_d = getTSDFValue (trans.translation ().cast<float> () + (tprev) * du,
                                       &has_data);
                d = getTSDFValue (trans.translation ().cast<float> () + tcurr * du, &has_data);
                if (!has_data || pcl_isnan (d) || pcl_isnan (last_d)) {
                    pt.x = pt.y = pt.z = std::numeric_limits<float>::quiet_NaN();
                }
                float t_star = t + step * (-1 + fabs (last_d / (last_d -d)));
                pt.getVector3fMap () = trans.translation().cast<float> () + tcurr * du;
                //Get normals by looking at adjacent voxels
                const OctreeNode* voxel = octree_->getContainingVoxel (pt.x, pt.y, pt.z);
                if (!voxel) {
                    pt.normal_x = pt.normal_y = pt.normal_z = std::numeric_limits<float>::quiet_NaN();
                    continue;
                }
                float xsize, ysize, zsize;
                voxel->getSize (xsize, ysize, zsize);
                bool valid = true;
                float d_xm = getTSDFValue (pt.x-xsize, pt.y, pt.z, &valid);
                float d_xp = getTSDFValue (pt.x+xsize, pt.y, pt.z, &valid);
                float d_ym = getTSDFValue (pt.x, pt.y-ysize, pt.z, &valid);
                float d_yp = getTSDFValue (pt.x, pt.y+ysize, pt.z, &valid);
                float d_zm = getTSDFValue (pt.x, pt.y, pt.z-zsize, &valid);
                float d_zp = getTSDFValue (pt.x, pt.y, pt.z+zsize, &valid);
                if (!valid) {
                    pt.normal_x = pt.normal_y = pt.normal_z = std::numeric_limits<float>::quiet_NaN();
                    continue;
                }
                Eigen::Vector3f dF;
                dF (0) = (d_xp - d_xm)*max_dist_neg_/ (2*xsize);
                dF (1) = (d_yp - d_ym)*max_dist_neg_/ (2*ysize);
                dF (2) = (d_zp - d_zm)*max_dist_neg_/ (2*zsize);
                dF.normalize();
                pt.normal_x = dF(0);
                pt.normal_y = dF(1);
                pt.normal_z = dF(2);
            }
        }
        pcl::transformPointCloudWithNormals (*cloud, *cloud, trans.inverse());
        return (cloud);
    }