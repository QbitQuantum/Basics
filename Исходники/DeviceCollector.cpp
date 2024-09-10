void DeviceCollector::onOrientationData(myo::Myo* myo, uint64_t timestamp, const myo::Quaternion<float>& quat)
{
    Device * device = findDevice(myo);
    if ( device ) {
        using std::atan2;
        using std::asin;
        using std::sqrt;
        
        // Calculate Euler angles (roll, pitch, and yaw) from the unit quaternion.
        float roll = atan2(2.0f * (quat.w() * quat.x() + quat.y() * quat.z()),
                           1.0f - 2.0f * (quat.x() * quat.x() + quat.y() * quat.y()));
        float pitch = asin(2.0f * (quat.w() * quat.y() - quat.z() * quat.x()));
        float yaw = atan2(2.0f * (quat.w() * quat.z() + quat.x() * quat.y()),
                          1.0f - 2.0f * (quat.y() * quat.y() + quat.z() * quat.z()));
        
        device->q = quat;//set(quat.x(), quat.y(), quat.z(), quat.w());
        
        
        device->roll = roll;
        device->pitch = pitch;
        device->yaw = yaw;
        
        
        // Convert the floating point angles in radians to a scale from 0 to 20.
        device->roll_w = static_cast<int>((roll + (float)M_PI)/(M_PI * 2.0f) * 18);
        device->pitch_w = static_cast<int>((pitch + (float)M_PI/2.0f)/M_PI * 18);
        device->yaw_w = static_cast<int>((yaw + (float)M_PI)/(M_PI * 2.0f) * 18);
        
        float gyoro_g = sqrt(device->gyro.x()*device->gyro.x() + device->gyro.y()*device->gyro.y() + device->gyro.z()*device->gyro.z());
        float g = sqrt(device->accel.x()*device->accel.x() + device->accel.y()*device->accel.y() + device->accel.z()*device->accel.z());
        //            cout << gyoro_g << endl;
        //            cout << g << endl;
        if ( gyoro_g <= 0.2 ) device->gravity = g;
        
//        Quaternion4f q;
//        q = quat;
//        //.set(quat.x(), quat.z(), quat.y(), quat.w());
//        Vector3f linear_accel;
//        ofMatrix4x4 mat;
//        mat.translate(ofVec3f(0,device->gravity,0));
//        mat.rotate(q);
//        ofVec3f trans = mat.getTranslation();
//        
//        linear_accel = device->getAccel();
//        linear_accel.x = linear_accel.x - trans.x;
//        linear_accel.y = linear_accel.y - trans.z;
//        linear_accel.z = linear_accel.z - trans.y;
//
//        device->linear_accel.set(linear_accel);
        //            cout << device->getAccel() << endl;
        //            cout << mat.getTranslation() << endl;
        //            cout << linear_accel << endl;
    }
}