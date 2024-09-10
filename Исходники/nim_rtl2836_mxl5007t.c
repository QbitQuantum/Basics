/**

@see   DTMB_NIM_FP_INITIALIZE

*/
s32
rtl2836_mxl5007t_Initialize(
	DTMB_NIM_MODULE *pNim
	)
{
	typedef struct
	{
		s32 RegBitName;
		u64 Value;
	}
	REG_VALUE_ENTRY;


	static const REG_VALUE_ENTRY AdditionalInitRegValueTable[RTL2836_MXL5007T_ADDITIONAL_INIT_REG_TABLE_LEN] =
	{
		// RegBitName,				Value
		{DTMB_TARGET_VAL,			0x38	},
	};


	TUNER_MODULE *pTuner;
	DTMB_DEMOD_MODULE *pDemod;

	MXL5007T_EXTRA_MODULE *pTunerExtra;

	s32 i;

	s32 RegBitName;
	u64 Value;



	// Get tuner module and demod module.
	pTuner = pNim->pTuner;
	pDemod = pNim->pDemod;

	// Get tuner extra module.
	pTunerExtra = &(pTuner->Extra.Mxl5007t);


	// Enable demod DTMB_I2CT_EN_CTRL.
	if(pDemod->RegAccess.Addr8Bit.SetRegBitsWithPage(pDemod, DTMB_I2CT_EN_CTRL, 0x1) != FUNCTION_SUCCESS)
		goto error_status_set_registers;

	// Initialize tuner.
	if(pTuner->Initialize(pTuner) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Set tuner bandwidth mode with 8 MHz.
	if(pTunerExtra->SetBandwidthMode(pTuner, MXL5007T_BANDWIDTH_8000000HZ) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Disable demod DTMB_I2CT_EN_CTRL.
	if(pDemod->RegAccess.Addr8Bit.SetRegBitsWithPage(pDemod, DTMB_I2CT_EN_CTRL, 0x0) != FUNCTION_SUCCESS)
		goto error_status_set_registers;


	// Initialize demod.
	if(pDemod->Initialize(pDemod) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Set demod IF frequency with NIM default.
	if(pDemod->SetIfFreqHz(pDemod, RTL2836_MXL5007T_IF_FREQ_HZ_DEFAULT) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Set demod spectrum mode with NIM default.
	if(pDemod->SetSpectrumMode(pDemod, RTL2836_MXL5007T_SPECTRUM_MODE_DEFAULT) != FUNCTION_SUCCESS)
		goto error_status_execute_function;


	// Set demod registers.
	for(i = 0; i < RTL2836_MXL5007T_ADDITIONAL_INIT_REG_TABLE_LEN; i++)
	{
		// Get register bit name and its value.
		RegBitName = AdditionalInitRegValueTable[i].RegBitName;
		Value      = AdditionalInitRegValueTable[i].Value;

		// Set demod registers
		if(pDemod->RegAccess.Addr8Bit.SetRegBitsWithPage(pDemod, RegBitName, Value) != FUNCTION_SUCCESS)
			goto error_status_set_registers;
	}


	return FUNCTION_SUCCESS;


error_status_execute_function:
error_status_set_registers:
	return FUNCTION_ERROR;
}