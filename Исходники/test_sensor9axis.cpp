void Test_Sensor9Axis(void)
{
    uint8_t ch, dataVal;

    DEBUG_MSG_FUNC_START;

    while(1)
    {
        print_menu_command();

        if(false == UartQueue_Serial_Is_Empty())
        {
            ch = UartQueue_Serial_DeQueue();
            printf("%c is selected\n\n", (char)ch);

            switch((char)ch)
            {
            case '0':
                break;

            case '1':
                dataVal = g_MPU_9150.getDeviceID();
                printf("Device ID: 0x%02X\n", dataVal);
                break;

            case '2':
            	// read mag - set i2c bypass enable pin to true to access magnetometer
            	I2Cdev::writeByte(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_INT_PIN_CFG, 0x02);
            	Delay(50);
                // enable the magnetometer
            	I2Cdev::writeByte(MPU9150_RA_MAG_ADDRESS, 0x0A, 0x01);
            	Delay(50);
                I2Cdev::readByte(MPU9150_RA_MAG_ADDRESS, 0, &dataVal);
                printf("Device ID: 0x%02X\n", dataVal);
                break;

            case '3':
                {
                    int16_t ax, ay, az;
                    int16_t gx, gy, gz;
                    int16_t mx, my, mz;

                    g_MPU_9150.initialize();
                    printf("MPU9150 initialize done.\n");

                    while(1)
                    {
                        // read raw accel/gyro measurements from device
                        g_MPU_9150.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
                        printf("ax: %d, ay: %d, az: %d, gx: %d, gy: %d, gz: %d, mx: %d, my: %d, mz: %d\n",
                            ax, ay, az, gx, gy, gz, mx, my, mz);
                        Delay(300);
                    }
                }
                break;
            }

            g_print_menu_control_flag = true;

            if('x' == (char)ch)
            {
                break;
            }
        }
    }

    return;
}