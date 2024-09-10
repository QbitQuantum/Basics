void MyoDataCollector::onOrientationData(myo::Myo* myo, uint64_t timestamp, const myo::Quaternion<float>& quat)
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

	MyoFrameOrientationData & orient_data = m_orientation_data;

	orient_data.timestamp	= timestamp;
	orient_data.quaternion	= ofQuaternion( quat.x(), quat.y(), quat.z(), quat.w() );
    orient_data.euler_roll	= roll;
    orient_data.euler_pitch = pitch;
	orient_data.euler_yaw	= yaw;
}