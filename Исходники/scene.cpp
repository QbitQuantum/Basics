void Scene::focusSceneUpdate(CloudPtr &pc_in, tf::Transform &transform_camFromBase, tf::Transform &transform_baseFromfocus, MatrixXf boundBox, Eigen::Matrix4f eigen_virtualFromFocus_old)
{
    pc_scene.reset (new Cloud);
    pc_scene_focus.reset (new Cloud);
    pc_scene_base.reset(new Cloud);
    pc_scene_focus_back.reset(new Cloud);

    CloudPtr pc_scene_focus_temp;
    pc_scene_focus_temp.reset (new Cloud);

    Eigen::Matrix4f eigen_camFromBase;
    transformAsMatrix (transform_camFromBase, eigen_camFromBase);
    if(DEBUG_ALGORITHM) cout<<"-------------camupdated"<<endl;
    if(DEBUG_ALGORITHM) cout<<eigen_camFromBase<<endl;

    pcl_ros::transformPointCloud(*pc_in, *pc_scene_base, transform_camFromBase);
    pcl_ros::transformPointCloud(*pc_scene_base, *pc_scene_focus_temp, transform_baseFromfocus);

    for(int i=0;i<pc_in->points.size();i++){
        PointT point_in = pc_in->points[i];
        PointT point_transformed = pc_scene_focus_temp->points[i];
        // cut off
        if(point_transformed.x<boundBox(0,0) && point_transformed.x>boundBox(0,1) && point_transformed.y<boundBox(1,0) && point_transformed.y>boundBox(1,1) && point_transformed.z<boundBox(2,0) && point_transformed.z>boundBox(2,1)){
            pc_scene->points.push_back(point_in);
            pc_scene_focus->points.push_back(point_transformed);
        }
    }

    // return back pc_scene to the original cam pos
    Eigen::Matrix4f inv = eigen_virtualFromFocus_old.inverse();
    for(int i=0;i<pc_scene_focus->points.size();i++){
        PointT point = pc_scene_focus->points[i];
        PointT point_back;
        point_back.x = inv(0,0)*point.x + inv(0,1)*point.y + inv(0,2)*point.z + inv(0,3);
        point_back.y = inv(1,0)*point.x + inv(1,1)*point.y + inv(1,2)*point.z + inv(1,3);
        point_back.z = inv(2,0)*point.x + inv(2,1)*point.y + inv(2,2)*point.z + inv(2,3);
        pc_scene_focus_back->points.push_back(point_back);
    }

//    if(USENORM) calcNormal();
}