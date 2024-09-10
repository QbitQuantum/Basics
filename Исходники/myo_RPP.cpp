		// onOrientationData() is called whenever the Myo device provides its current orientation, which is represented
		// as a unit quaternion.
		void onOrientationData(Myo* myo, uint64_t timestamp, const Quaternion<float>& quat)
		{
			using std::atan2;
			using std::asin;
			using std::sqrt;
			using std::max;
			using std::min;
			// Calculate Euler angles (roll, pitch, and yaw) from the unit quaternion.
			float roll = atan2(2.0f * (quat.w() * quat.x() + quat.y() * quat.z()),
							   1.0f - 2.0f * (quat.x() * quat.x() + quat.y() * quat.y()));
			float pitch = asin(max(-1.0f, min(1.0f, 2.0f * (quat.w() * quat.y() - quat.z() * quat.x()))));
			float yaw = atan2(2.0f * (quat.w() * quat.z() + quat.x() * quat.y()),
							1.0f - 2.0f * (quat.y() * quat.y() + quat.z() * quat.z()));
			// Convert the floating point angles in radians to a scale from 0 to 18.
		  //  roll_w = static_cast<int>((roll + (float)M_PI)/(M_PI * 2.0f) * 18);
		  //  pitch_w = static_cast<int>((pitch + (float)M_PI/2.0f)/M_PI * 18);
		  //  yaw_w = static_cast<int>((yaw + (float)M_PI)/(M_PI * 2.0f) * 18);

		}