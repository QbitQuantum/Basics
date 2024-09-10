bool Pcl_grabing::isBlock()
{
    update_kinect_points();
    int npts = transformed_pclKinect_clr_ptr_->points.size();
    Eigen::Vector3f pt;
    Eigen::Vector3f dist;
    vector<int> index;
    index.clear();
    double distance = 1;
    BlockColor<<0,0,0;
    for (int i = 0; i < npts; i++) 
    {
        pt = transformed_pclKinect_clr_ptr_->points[i].getVector3fMap();
        dist = pt - TableCentroid;
        dist[2]=0;
        distance = dist.norm();
        if(distance < TableRadius)
            if(pt[2]>(TableHeight+0.003) && pt[2]<BlockMaxHeight)
            {
                index.push_back(i);
                BlockColor(0)+=transformed_pclKinect_clr_ptr_->points[i].r;
                BlockColor(1)+=transformed_pclKinect_clr_ptr_->points[i].g;
                BlockColor(2)+=transformed_pclKinect_clr_ptr_->points[i].b;
            }
    }
    int n_block_points = index.size();
    if(n_block_points<10)
    {
        ROS_INFO("There is no block on the stool.");
        return 0;
    }
    ROS_INFO("There is a block with %d points", n_block_points);
    BlockColor/=n_block_points;
    ROS_INFO_STREAM("The block color:"<<BlockColor.transpose());
    
    display_ptr_->header = transformed_pclKinect_clr_ptr_->header;
    display_ptr_->is_dense = transformed_pclKinect_clr_ptr_->is_dense;
    display_ptr_->width = n_block_points; //transformed_pclKinect_clr_ptr_->width;
    display_ptr_->height = transformed_pclKinect_clr_ptr_->height;
    display_ptr_->points.resize(n_block_points);
    for (int i = 0; i < n_block_points; i++) 
    {
        display_ptr_->points[i].getVector3fMap() = transformed_pclKinect_clr_ptr_->points[index[i]].getVector3fMap();
    }
    display_points(*display_ptr_);
    
    Eigen::Vector3f BlockCentroid;
    BlockCentroid =pcl_wsn.compute_centroid(display_ptr_);
    ROS_INFO_STREAM("The centroid of the block:"<<BlockCentroid.transpose());


    vector<int> block_index;
    block_index.clear();
    for (int i = 0; i < n_block_points; i++) 
    {
        pt=display_ptr_->points[i].getVector3fMap();
        dist = pt - BlockCentroid;
        dist[2]=0;
        distance = dist.norm();
        if(distance < BlockTopRadius)
        {
            block_index.push_back(i);
        }
    }
    int n_block_top = block_index.size();
    ROS_INFO("There are %d points around the block's top center",n_block_top);
    pcl::PointCloud<pcl::PointXYZ>::Ptr block_ptr_(new PointCloud<pcl::PointXYZ>);
    block_ptr_->header=display_ptr_->header;
    block_ptr_->is_dense=display_ptr_->is_dense;
    block_ptr_->width=n_block_top;
    block_ptr_->height=display_ptr_->height;
    block_ptr_->points.resize(n_block_top);   
    for (int i = 0; i < n_block_top; i++) 
    {
        block_ptr_->points[i].getVector3fMap()=display_ptr_->points[block_index[i]].getVector3fMap();
    }

    BlockTopCentroid = pcl_wsn.compute_centroid(block_ptr_);
    ROS_INFO_STREAM("The centroid of the block's top:"<<BlockTopCentroid.transpose());
    //display_points(*block_ptr_);


    block_index.clear();
    for(int i = 0; i < n_block_points; i++)
    {
        pt=display_ptr_->points[i].getVector3fMap();
        if(abs(pt[2]-BlockTopCentroid[2])<0.002)
        {
            block_index.push_back(i);
        }
    }
    n_block_top = block_index.size();
    block_ptr_->header=display_ptr_->header;
    block_ptr_->is_dense=display_ptr_->is_dense;
    block_ptr_->width=n_block_top;
    block_ptr_->height=display_ptr_->height;
    block_ptr_->points.resize(n_block_top);   
    for (int i = 0; i < n_block_top; i++) 
    {
        block_ptr_->points[i].getVector3fMap()=display_ptr_->points[block_index[i]].getVector3fMap();
    }
    
    double block_dist;
    pcl_wsn.fit_points_to_plane(block_ptr_,Block_Normal,block_dist);
    Block_Major = pcl_wsn.get_major_axis();
    ROS_INFO_STREAM("The major vector of the block's top:"<<Block_Major.transpose());
    //display_points(*block_ptr_);

    return true;
}