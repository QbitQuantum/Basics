/**

@see   QAM_NIM_FP_INITIALIZE

*/
s32
rtl2840_max3543_Initialize(
	QAM_NIM_MODULE *pNim
	)
{
	typedef struct
	{
		s32 RegBitName;
		u64 Value;
	}
	REG_VALUE_ENTRY;


	static const REG_VALUE_ENTRY AdditionalInitRegValueTable[RTL2840_MAX3543_ADDITIONAL_INIT_REG_TABLE_LEN] =
	{
		// RegBitName,					Value
		{QAM_OPT_RF_AAGC_DRIVE,			0x1		},
		{QAM_OPT_IF_AAGC_DRIVE,			0x1		},
		{QAM_OPT_RF_AAGC_OEN,			0x1		},
		{QAM_OPT_IF_AAGC_OEN,			0x1		},
		{QAM_RF_AAGC_MAX,				0xff	},
		{QAM_RF_AAGC_MIN,				0x0		},
		{QAM_IF_AAGC_MAX,				0xff	},
		{QAM_IF_AAGC_MIN,				0x0		},
		{QAM_AAGC_MODE_SEL,				0x0		},
	};


	QAM_DEMOD_MODULE *pDemod;
	TUNER_MODULE *pTuner;

	s32 i;

	s32 RegBitName;
	u64 Value;


	// Get demod module and tuner module.
	pDemod = pNim->pDemod;
	pTuner = pNim->pTuner;


	// Initialize demod.
	if(pDemod->Initialize(pDemod) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Initialize tuner.
	if(pTuner->Initialize(pTuner) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Set demod IF frequency in Hz with NIM default.
	if(pDemod->SetIfFreqHz(pDemod, RTL2840_MAX3543_IF_FREQ_HZ_DEFAULT) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Set demod spectrum mode with NIM default.
	if(pDemod->SetSpectrumMode(pDemod, RTL2840_MAX3543_SPECTRUM_MODE_DEFAULT) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Set demod AAGC registers.
	// Note: SetParameters() will set QAM_AAGC_TARGET and QAM_VTOP according to parameters.
	for(i = 0; i < RTL2840_MAX3543_ADDITIONAL_INIT_REG_TABLE_LEN; i++)
	{
		// Get register bit name and its value.
		RegBitName = AdditionalInitRegValueTable[i].RegBitName;
		Value      = AdditionalInitRegValueTable[i].Value;

		// Set demod registers
		if(pDemod->RegAccess.Addr8Bit.SetRegBitsWithPage(pDemod, RegBitName, Value) != FUNCTION_SUCCESS)
			goto error_status_set_registers;
	}


	return FUNCTION_SUCCESS;


error_status_set_registers:
error_status_execute_function:
	return FUNCTION_ERROR;
}