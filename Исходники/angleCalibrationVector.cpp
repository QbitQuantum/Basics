 // onOrientationData() is called whenever the Myo device provides its current orientation, which is represented as a unit quaternion.
 // This function takes the position values from the quaternion and assign new values to roll_w, pitch_w and yaw_w every time new data are provided by the Myo.
 void onOrientationData(myo::Myo* myo, uint64_t timestamp, const myo::Quaternion<float>& quat)
 {
     using std::atan2;
     using std::asin;
     using std::sqrt;
     using std::max;
     using std::min;
     
     // Calculate Euler angles (roll, pitch, and yaw) from the unit quaternion.
     float roll = atan2(2.0f * (quat.w() * quat.x() + quat.y() * quat.z()),
                        1.0f - 2.0f * (quat.x() * quat.x() + quat.y() * quat.y()));
     
     // Convert the floating point angles in radians to a clockwise scale from 1 to 127 (good for PureData) with the zero angle in π.
     // Need to change the format of the angle? DO IT HERE!
     
     roll_tmp = static_cast<int>( ( roll * 180/M_PI) );   // the value of 200 ensures a positive value for the angle.
 }