//void Init_MPU6050(MPU6050Init_Typedef *MPU6050_Config)
void Init_MPU6050(void)
{
    unsigned char Rdata[5]={0};
    unsigned char MPU_ID=0;
    //  Single_read = MPU6050_Config->Read_Data;
    //  Single_write= MPU6050_Config->Write_Data;

    MPU_ID=getDeviceID();
    if(MPU_ID == 0x68)
        rt_kprintf("MPU6050 init OK!\n");
    else
        rt_kprintf("MPU6050 init ERROR!\n");
    //  MPU6050_swrite(PWR_MGMT_1,0x07);
    MPU6050_swrite(PWR_MGMT_1,0x00);
    MPU6050_swrite(SMPLRT_DIV,0x07);
    MPU6050_swrite(CONFIG,0x06);
    MPU6050_swrite(GYRO_CONFIG,0x08);
    MPU6050_swrite(ACCEL_CONFIG,0x08);
}