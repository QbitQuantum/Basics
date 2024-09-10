/*
  * Updates function
  *
  */
extern "C" void sf_MPU6050_2xDriver_GxAyz_Update_wrapper(const int16_T *x_vel,
			const int16_T *y_acc,
			const int16_T *z_acc,
			const int16_T *x_vel_2,
			const int16_T *y_acc_2,
			const int16_T *z_acc_2,
			real_T *xD)
{
  /* %%%-SFUNWIZ_wrapper_Update_Changes_BEGIN --- EDIT HERE TO _END */
if(xD[0] != 1){
    # ifndef MATLAB_MEX_FILE     
        Wire.begin();
        accelgyro.initialize();
		accelgyro.setDLPFMode(MPU6050_DLPF_BW_42);
        accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_1000);

        accelgyro2.initialize();
        accelgyro2.setDLPFMode(MPU6050_DLPF_BW_42);
        accelgyro2.setFullScaleGyroRange(MPU6050_GYRO_FS_1000);
        
    #endif
    //done with initialization
    xD[0] = 1;           
}
/* %%%-SFUNWIZ_wrapper_Update_Changes_END --- EDIT HERE TO _BEGIN */
}