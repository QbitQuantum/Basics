			void setProjectionMatrix(const Mat4f &projmat)
			{
				this->projmat = projmat;
				Mat4f projmatinv = projmat.inverse();
				// Corners of the frustum in world space
				corners[0] = projmatinv.transformPoint(Vec3f(-1, 1, -1));
				corners[1] = projmatinv.transformPoint(Vec3f(1, 1, -1));
				corners[2] = projmatinv.transformPoint(Vec3f(1, -1, -1));
				corners[3] = projmatinv.transformPoint(Vec3f(-1, -1, -1));
				corners[4] = projmatinv.transformPoint(Vec3f(-1, 1, 1));
				corners[5] = projmatinv.transformPoint(Vec3f(1, 1, 1));
				corners[6] = projmatinv.transformPoint(Vec3f(1, -1, 1));
				corners[7] = projmatinv.transformPoint(Vec3f(-1, -1, 1));
				// Near plane
				planes[0] = Plane(corners[0], corners[1], corners[2]);
				// Left plane
				planes[1] = Plane(corners[0], corners[3], corners[4]);
				// Top plane
				planes[2] = Plane(corners[0], corners[1], corners[4]);
				// Right plane
				planes[3] = Plane(corners[1], corners[2], corners[5]);
				// Bottom plane
				planes[4] = Plane(corners[2], corners[3], corners[6]);
				// Far plane
				planes[5] = Plane(corners[4], corners[5], corners[6]);
				// TODO: Fix normal vectors to point inside!
			}