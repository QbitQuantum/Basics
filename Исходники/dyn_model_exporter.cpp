	bool DynModelExporter::getCenterAndScale(Plane<float> &plane, pcl::PointCloud<PointXYZRGB>::Ptr scene_cloud, PointXYZ &center, PointXYZ &scale)
		{
			center.x = 0.0;
			center.y = 0.0;
			center.z = 0.0;

			float size = 0.0;
			PointXYZ min(9999999.0, 9999999.0, 9999999.0);
			PointXYZ max(-9999999.0, -9999999.0, -9999999.0);

			for (pcl::PointCloud<PointXYZRGB>::iterator it = scene_cloud->begin(); it != scene_cloud->end(); ++it)
			{
				 // 1cm TODO - make as param
				 if (plane.distance(cv::Vec3f(it->x, it->y, it->z)) < 0.05)
				 {
					 center.x += it->x;
					 center.y += it->y;
					 center.z += it->z;
					 size += 1.0;

					 if (it->x < min.x) min.x = it->x;
					 if (it->y < min.y) min.y = it->y;
					 if (it->z < min.z) min.z = it->z;

					 if (it->x > max.x) max.x = it->x;
					 if (it->y > max.y) max.y = it->y;
					 if (it->z > max.z) max.z = it->z;
				 }
			}

			//std::cout << std::endl << std::endl << min << " " << max << std::endl << std::endl;
			if (size > 10)
			{
				center.x /= size;
				center.y /= size;
				center.z /= size;
				//center.z = -(center.x*plane.a + center.y*plane.b + plane.d)/plane.c;
			}
			else return false;

			scale.x = max.x - min.x;
			if (scale.x > 3)
				scale.x = 3;
			scale.y = max.y - min.y;
			if (scale.y > 3)
				scale.y = 3;
			scale.z = max.z - min.z;
			if (scale.z > 3)
				scale.z = 3;

			return true;
		}