static int Codec618CmdWrite(RK618_DEVICE_CLASS *dev,UINT16 RegAddr, UINT32 uData)
{
    uint8 cmd,data[4];
    I2C_CMD_ARG stArg;
    uint32 set_bit, read_value, new_value;
    int i;

    HDC hI2c = dev->hI2C;
    if(hI2c != NULL)
    {
        if (!Is_rk618_mfd_register(RegAddr) && !Is_rk618_codec_register(RegAddr))
        {
    		rk_printf("%s : reg error!\n", __func__);
    		return -EINVAL;
    	}

    	// set codec mask bit
    	i = rk618_mfd_codec_bit(RegAddr);
    	if (i >= 0)
        {
    		set_bit = rk618_mfd_codec_bit_list[i].value;
    		read_value = Codec618CmdRead(dev, RegAddr);
    		uData = (read_value & ~set_bit) | (uData & set_bit);
    	}
        else if (Is_rk618_mfd_mask_register(RegAddr))
        {
    		uData = ((0xffff0000 & rk618_read_reg_cache(RegAddr)) | (uData & 0x0000ffff));
    	}

        new_value = rk618_set_init_value(dev, RegAddr, uData);

//        data[0] = (0xff & uData);
//        data[1] = (0xff00 & uData) >> 8;
//        data[2] = (0xff0000 & uData)>>16;
//        data[3] = (0xff000000 & uData)>>24;
        MemCpy(data, (uint8 *)&uData, 4);

        stArg.SlaveAddress  = RK618_Codec_I2CAddr;
        stArg.RegAddr       = RegAddr;
        stArg.RWmode        = NormalMode;
        stArg.speed         = RK618_Codec_I2CSpeed;
        stArg.addr_reg_fmt  = I2C_7BIT_ADDRESS_16BIT_REG;

        I2cDev_SendData(hI2c,data,4,&stArg);

	    if (new_value != uData)
        {
            MemCpy(data, (uint8 *)&new_value, 4);
            I2cDev_SendData(hI2c,data,4,&stArg);
		    uData = new_value;
	    }

	    rk618_write_reg_cache(RegAddr, uData);
    }

    return 0;
}