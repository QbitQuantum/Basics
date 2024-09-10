static unsigned int __stdcall ioThread(void* inst)
{
	rDeviceERHandPeakCAN* devCAN = (rDeviceERHandPeakCAN*)inst;

	HANDLE hEvents[2];
	int eventIdx;
	char id_des;
	char id_cmd;
	char id_src;
	int len;
	unsigned char data[8];
	unsigned char data_return = 0;
    
    // Configure events to be listened on
    hEvents[0] = devCAN->_ioQuitEvent;
	hEvents[1] = devCAN->_ioEvent;
	

	while (devCAN->_ioThreadRun)
	{
		eventIdx = WaitForMultipleObjects(sizeof(hEvents)/sizeof(hEvents[0]), hEvents, FALSE, 300); 

		switch (eventIdx)
		{
		case 0:
			return 0;//break;

		case 1:
			{
				while (0 == CANAPI::get_message(devCAN->_CAN_Ch, &id_cmd, &id_src, &id_des, &len, data, FALSE))
				{
					switch (id_cmd)
					{
					case ID_CMD_QUERY_CONTROL_DATA:
						{
							if (id_src >= ID_DEVICE_SUB_01 && id_src <= ID_DEVICE_SUB_04)
							{
								devCAN->_lock.lock();
								{
									devCAN->_vars->enc_actual[(id_src-ID_DEVICE_SUB_01)*4 + 0] = (int)(data[0] | (data[1] << 8));
									devCAN->_vars->enc_actual[(id_src-ID_DEVICE_SUB_01)*4 + 1] = (int)(data[2] | (data[3] << 8));
									devCAN->_vars->enc_actual[(id_src-ID_DEVICE_SUB_01)*4 + 2] = (int)(data[4] | (data[5] << 8));
									devCAN->_vars->enc_actual[(id_src-ID_DEVICE_SUB_01)*4 + 3] = (int)(data[6] | (data[7] << 8));
									data_return |= (0x01 << (id_src-ID_DEVICE_SUB_01));
								}
								devCAN->_lock.unlock();
							}
							if (data_return == (0x01 | 0x02 | 0x04 | 0x08))
							{
								devCAN->_lock.lock();
								{
									// send torques
									for (int i=0; i<4;i++)
									{
										CANAPI::write_current(devCAN->_CAN_Ch, i, &devCAN->_vars->pwm_demand[4*i]);
										for(int k=0; k<100000; k++);
									}
								}
								devCAN->_lock.unlock();

								data_return = 0;
							}
						}
						break;
					}
				}
			}
			break;
		}
	}

	return 0;
}