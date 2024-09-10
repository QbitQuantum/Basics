		/**
		 * \brief	基本的相机坐标系，认为参考点的方向向量为z轴
		 *
		 * \param	center	参考点的位置
		 * \param	up	  	视点向上方向的向量.
		 *
		 * \return	世界坐标系转相机坐标系的矩阵
		 */
		Mat3 LookAt(const Vec3 &center, const Vec3 &up) {
			Vec3 zc = center.normalized();//向量n
			Vec3 xc = up.cross(zc).normalized();//向量u
			Vec3 yc = zc.cross(xc);//向量v
			Mat3 R;
			R.row(0) = xc;
			R.row(1) = yc;
			R.row(2) = zc;
			return R;
		}