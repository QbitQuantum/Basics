struct dvb_frontend* dvb_d6158earda_attach(struct i2c_adapter* i2c, UINT8 system)
{
	struct dvb_d6158_fe_ofdm_state* state = NULL;
	struct nim_panic6158_private *priv;
	int ret;
	struct COFDM_TUNER_CONFIG_API  Tuner_API;

	/* allocate memory for the internal state */
	state = kzalloc(sizeof(struct dvb_d6158_fe_ofdm_state), GFP_KERNEL);
	if (state == NULL) goto error;

	priv = (PNIM_PANIC6158_PRIVATE)YWOS_Malloc(sizeof(struct nim_panic6158_private));
	if (NULL == priv)
	{
		goto error;
	}

	MEMSET(priv, 0, sizeof(struct nim_panic6158_private));

	/* create dvb_frontend */
	if (system == DEMO_BANK_T2)  //dvb-t
	{
		printk("DEMO_BANK_T2\n");
		memcpy(&state->frontend.ops, &dvb_d6158_fe_ofdm_ops, sizeof(struct dvb_frontend_ops));
	}

	else if (system == DEMO_BANK_C) //dvb-c
	{
		printk("DEMO_BANK_C\n");
		memcpy(&state->frontend.ops, &dvb_d6158_fe_qam_ops, sizeof(struct dvb_frontend_ops));
	}
	printf("[%s]%d\n", __FUNCTION__, __LINE__);

	state->frontend.ops.set_frontend = d6158earda_set_frontend;
	state->frontend.demodulator_priv = state;
	state->i2c = i2c;

	state->DeviceMap.Timeout    = IOREG_DEFAULT_TIMEOUT;
	state->DeviceMap.Registers = STV0367ofdm_NBREGS;
	state->DeviceMap.Fields = STV0367ofdm_NBFIELDS;
	state->DeviceMap.Mode       = IOREG_MODE_SUBADR_16;
	state->DeviceMap.RegExtClk = 27000000; //Demod External Crystal_HZ
	state->DeviceMap.RegMap = (TUNER_IOREG_Register_t *)
							  kzalloc(state->DeviceMap.Registers * sizeof(TUNER_IOREG_Register_t),
									  GFP_KERNEL);
	state->DeviceMap.priv = (void *)state;

	state->spark_nimdev.priv = priv;
	state->spark_nimdev.base_addr =  PANIC6158_T2_ADDR;

	//state->spark_nimdev.i2c_type_id= pConfig->ext_dm_config.i2c_type_id;
	//state->spark_nimdev.nim_idx = pConfig->ext_dm_config.nim_idx;//distinguish left or right

	priv->i2c_adap = i2c;
	priv->i2c_addr[0] = PANIC6158_T_ADDR;
	priv->i2c_addr[1] = PANIC6158_T2_ADDR;
	priv->i2c_addr[2] = PANIC6158_C_ADDR;
	priv->if_freq = DMD_E_IF_5000KHZ;
	priv->flag_id = OSAL_INVALID_ID;
	priv->i2c_mutex_id = OSAL_INVALID_ID;
	priv->system = system;   //T2 C
	priv->tuner_id = 2;

	YWOS_TaskSleep(50);

	nim_config_EARDATEK11658(&Tuner_API, 0, 0);
	Tuner_API.tuner_config.i2c_adap = (IOARCH_Handle_t*)i2c;
	MEMCPY((void*) & (priv->tc), (void*)&Tuner_API, sizeof(struct COFDM_TUNER_CONFIG_API));

	printf("[%s]%d\n", __FUNCTION__, __LINE__);

	if (NULL != Tuner_API.nim_Tuner_Init)
	{
		if (SUCCESS == Tuner_API.nim_Tuner_Init(&priv->tuner_id, &Tuner_API.tuner_config))
		{
			printf("[%s]%d\n", __FUNCTION__, __LINE__);
			DEM_WRITE_READ_TUNER ThroughMode;
			priv->tc.nim_Tuner_Init = Tuner_API.nim_Tuner_Init;
			priv->tc.nim_Tuner_Control = Tuner_API.nim_Tuner_Control;
			priv->tc.nim_Tuner_Status   = Tuner_API.nim_Tuner_Status;
			YWLIB_Memcpy(&priv->tc.tuner_config, &Tuner_API.tuner_config, sizeof(struct COFDM_TUNER_CONFIG_EXT));
			ThroughMode.nim_dev_priv = state->spark_nimdev.priv;
			printf("[%s]%d\n", __FUNCTION__, __LINE__);
			ThroughMode.Dem_Write_Read_Tuner = DMD_TCB_WriteRead;///////////////////////////////////
			nim_panic6158_ioctl_earda(&state->spark_nimdev, NIM_TUNER_SET_THROUGH_MODE, (UINT32)&ThroughMode);
			printf("[%s]%d\n", __FUNCTION__, __LINE__);
		}
	}

	printf("[%s]%d\n", __FUNCTION__, __LINE__);
	state->spark_nimdev.get_lock = nim_panic6158_get_lock;
	state->spark_nimdev.get_AGC = nim_panic6158_get_AGC_603;

	ret = nim_panic6158_open(&state->spark_nimdev);
	printk("[%s]%d,open result=%d \n", __FUNCTION__, __LINE__, ret);

	/* Setup init work mode */

	return &state->frontend;

error:
	kfree(state);
	return NULL;
}