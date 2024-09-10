    // onOrientationData() is called whenever the Myo device provides its current orientation, which is represented
    // as a unit quaternion.
    void onOrientationData(myo::Myo* myo, uint64_t timestamp, const myo::Quaternion<float>& quat)
    {
        using std::atan2;
        using std::asin;
        using std::sqrt;

        // Calculate Euler angles (roll, pitch, and yaw) from the unit quaternion.
        float roll = atan2(2.0f * (quat.w() * quat.x() + quat.y() * quat.z()),
                           1.0f - 2.0f * (quat.x() * quat.x() + quat.y() * quat.y()));
        float pitch = asin(2.0f * (quat.w() * quat.y() - quat.z() * quat.x()));
        float yaw = atan2(2.0f * (quat.w() * quat.z() + quat.x() * quat.y()),
                        1.0f - 2.0f * (quat.y() * quat.y() + quat.z() * quat.z()));
		
        // Convert the floating point angles in radians to a scale from 0 to 20.
        roll_w = static_cast<int>((roll + (float)M_PI)/(M_PI * 2.0f) * 18);
        pitch_w = static_cast<int>((pitch + (float)M_PI/2.0f)/M_PI * 18);
        yaw_w = static_cast<int>((yaw + (float)M_PI)/(M_PI * 2.0f) * 18);
		float drop = 1.1;
		roll = ((roll + (float)M_PI)/(M_PI * 2.0f) * 18);
        pitch = ((pitch + (float)M_PI/2.0f)/M_PI * 18);
		if(pitch > 10)
		{	if(pitch < 20)
			{	pitch *= (drop*(20-pitch));
			}
		}
		else
		{	if(pitch != 10)
			{	pitch *= (drop*(10-pitch));
			}
		}	
        yaw = ((yaw + (float)M_PI)/(M_PI * 2.0f) * 18);
		if(yaw > 10.0000)
		{	if(yaw < 20.0000)
			{	yaw *= (drop*(20-yaw));
			}
			else
			{	yaw = 19.9999;
			}
		}
		else
		{	if(yaw != 10.0000)
			{	yaw *= (drop*(10-yaw));
			}
		}	
		if(color_input == true)
		{	float x = (GetSystemMetrics(SM_CXSCREEN));
			float y = (GetSystemMetrics(SM_CYSCREEN));
			SetCursorPos((((((20)-yaw))/(20))*x), ((pitch/(20))*y));
		}
    }