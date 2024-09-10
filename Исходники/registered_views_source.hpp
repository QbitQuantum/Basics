void
RegisteredViewsSource<Full3DPointT, PointInT, OutModelPointT>::loadModel (ModelT & model)
{
    const std::string training_view_path = path_ + model.class_ + "/" + model.id_ + "/views/";
    const std::string view_pattern = ".*" + view_prefix_ + ".*.pcd";
    model.view_filenames_ = io::getFilesInDirectory(training_view_path, view_pattern, false);
    std::cout << "Object class: " << model.class_ << ", id: " << model.id_ << ", views: " << model.view_filenames_.size() << std::endl;

    typename pcl::PointCloud<Full3DPointT>::Ptr modell (new pcl::PointCloud<Full3DPointT>);
    typename pcl::PointCloud<Full3DPointT>::Ptr modell_voxelized (new pcl::PointCloud<Full3DPointT>);
    pcl::io::loadPCDFile(path_ + model.class_ + "/" + model.id_ + "/3D_model.pcd", *modell);

    float voxel_grid_size = 0.003f;
    typename pcl::VoxelGrid<Full3DPointT> grid_;
    grid_.setInputCloud (modell);
    grid_.setLeafSize (voxel_grid_size, voxel_grid_size, voxel_grid_size);
    grid_.setDownsampleAllData (true);
    grid_.filter (*modell_voxelized);

    model.normals_assembled_.reset(new pcl::PointCloud<pcl::Normal>);
    model.assembled_.reset (new pcl::PointCloud<PointInT>);

    pcl::copyPointCloud(*modell_voxelized, *model.assembled_);
    pcl::copyPointCloud(*modell_voxelized, *model.normals_assembled_);

    if(load_into_memory_)
    {
        model.views_.resize( model.view_filenames_.size() );
        model.indices_.resize( model.view_filenames_.size() );
        model.poses_.resize( model.view_filenames_.size() );
        model.self_occlusions_.resize( model.view_filenames_.size() );

        for (size_t i=0; i<model.view_filenames_.size(); i++)
        {
            // load training view
            const std::string view_file = training_view_path + "/" + model.view_filenames_[i];
            model.views_[i].reset( new pcl::PointCloud<PointInT> () );
            pcl::io::loadPCDFile (view_file, *model.views_[i]);

            // read pose
            std::string pose_fn (view_file);
            boost::replace_last (pose_fn, view_prefix_, pose_prefix_);
            boost::replace_last (pose_fn, ".pcd", ".txt");
            Eigen::Matrix4f pose = io::readMatrixFromFile( pose_fn );
            model.poses_[i] = pose.inverse(); //the recognizer assumes transformation from M to CC - i think!

            // read object mask
            model.indices_[i].indices.clear();
            std::string obj_indices_fn (view_file);
            boost::replace_last (obj_indices_fn, view_prefix_, indices_prefix_);
            boost::replace_last (obj_indices_fn, ".pcd", ".txt");
            std::ifstream f ( obj_indices_fn.c_str() );
            int idx;
            while (f >> idx)
                model.indices_[i].indices.push_back(idx);
            f.close();

            model.self_occlusions_[i] = -1.f;
        }
    }
    else
    {