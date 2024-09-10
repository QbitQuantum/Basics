void adjustNormalsToViewPoints(
		const pcl::PointCloud<pcl::PointXYZ>::Ptr & viewpoints,
		pcl::PointCloud<pcl::PointXYZRGBNormal> & cloud)
{
	if(viewpoints->size() && cloud.size())
	{
		pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ>);
		tree->setInputCloud (viewpoints);

		for(unsigned int i=0; i<cloud.size(); ++i)
		{
			std::vector<int> indices;
			std::vector<float> dist;
			tree->nearestKSearch(pcl::PointXYZ(cloud.points[i].x, cloud.points[i].y, cloud.points[i].z), 1, indices, dist);
			UASSERT(indices.size() == 1);

			Eigen::Vector3f v = viewpoints->at(indices[0]).getVector3fMap() - cloud.points[i].getVector3fMap();
			Eigen::Vector3f n(cloud.points[i].normal_x, cloud.points[i].normal_y, cloud.points[i].normal_z);

			float result = v.dot(n);
			if(result < 0)
			{
				//reverse normal
				cloud.points[i].normal_x *= -1.0f;
				cloud.points[i].normal_y *= -1.0f;
				cloud.points[i].normal_z *= -1.0f;
			}
		}
	}
}