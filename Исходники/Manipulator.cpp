		void Manipulator::calcRotationArgs(osg::Vec3d& axis, float& angle, 
			float p1x, float p1y,float p2x, float p2y) {
			osg::Matrixd rotation_matrix(_rotation);

			osg::Vec3d uv = osg::Vec3d(0.0f,1.0f,0.0f)*rotation_matrix;
			osg::Vec3d sv = osg::Vec3d(1.0f,0.0f,0.0f)*rotation_matrix;
			osg::Vec3d lv = osg::Vec3d(0.0f,0.0f,-1.0f)*rotation_matrix;

			osg::Vec3d p1 = sv * p1x + uv * p1y - lv * tb_project_to_sphere(_trackball_size, p1x, p1y);
			osg::Vec3d p2 = sv * p2x + uv * p2y - lv * tb_project_to_sphere(_trackball_size, p2x, p2y);

			axis = p2^p1;
			axis.normalize();

			float t = (p2 - p1).length() / (2.0 * _trackball_size);

			if (t > 1.0) t = 1.0;
			if (t < -1.0) t = -1.0;
			angle = osg::inRadians(asin(t));
			//2014/4/28
			//2014/10/26,0.1
			angle = 0.02 * angle;
		}