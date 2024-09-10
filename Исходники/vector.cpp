		Vec3		 Vec3::Rotate(const Quaternion& rotation)
		{
			Quaternion conjugateQ = rotation.Conjugate();
			Quaternion q = rotation * (*this) * conjugateQ;

			Vec3 ret(q.x, q.y, q.z);

			return ret;
		}