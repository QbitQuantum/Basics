void imu_callback(std::string name, imu_node::ImuData* imu, ros::Time t, void* f)
{
  FILE* file = (FILE*)f;

  fprintf(file, "%.5f %.5f %.5f %.5f %.5f %.5f %.5f %.5f\n",
          t.to_double(),
          imu->header.stamp.to_double(),
          imu->accel.ax, imu->accel.ay, imu->accel.az,
          imu->angrate.vx, imu->angrate.vy, imu->angrate.vz);
}