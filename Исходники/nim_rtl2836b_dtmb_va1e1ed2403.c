/**

@see   DTMB_NIM_FP_INITIALIZE

*/
int
rtl2836b_dtmb_va1e1ed2403_Initialize(
	DTMB_NIM_MODULE *pNim
	)
{
	typedef struct
	{
		int RegBitName;
		unsigned long Value;
	}
	REG_VALUE_ENTRY;


	static const REG_VALUE_ENTRY AdditionalInitRegValueTable[RTL2836B_DTMB_VA1E1ED2403_ADDITIONAL_INIT_REG_TABLE_LEN] =
	{
		// RegBitName,				Value
		{DTMB_AGC_DRIVE_LV,				0x0		},
		{DTMB_Z_AGC,					0x1		},
		{DTMB_EN_PGA_MODE,				0x0		},
		{DTMB_TARGET_VAL,				0x38	},
		{DTMB_AAGC_LOOPGAIN1,			0x15	},
		{DTMB_INTEGRAL_CNT_LEN,			0xc		},
		{DTMB_AAGC_LOCK_PGA_HIT_LEN,	0x1		},
		{DTMB_THD_LOCK_UP,				0x205	},
		{DTMB_THD_LOCK_DW,				0x1fb	},
		{DTMB_THD_UP1,					0x205	},
		{DTMB_THD_DW1,					0x1fb	},
		{DTMB_THD_UP2,					0x86	},
		{DTMB_THD_DW2,					0x7a	},
		{DTMB_GAIN_PULSE_SPACE_LEN,		0x1		},
		{DTMB_GAIN_PULSE_HOLD_LEN,		0x1		},
		{DTMB_GAIN_STEP_SUM_UP_THD,		0xb		},
		{DTMB_GAIN_STEP_SUM_DW_THD,		0x5		},
	};


	TUNER_MODULE *pTuner;
	DTMB_DEMOD_MODULE *pDemod;

	int i;

	int RegBitName;
	unsigned long Value;



	// Get tuner module and demod module.
	pTuner = pNim->pTuner;
	pDemod = pNim->pDemod;


	// Enable demod DTMB_I2CT_EN_CTRL.
	if(pDemod->RegAccess.Addr16Bit.SetRegBits(pDemod, DTMB_I2CT_EN_CTRL, 0x1) != FUNCTION_SUCCESS)
		goto error_status_set_registers;

	// Initialize tuner.
	if(pTuner->Initialize(pTuner) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Disable demod DTMB_I2CT_EN_CTRL.
	if(pDemod->RegAccess.Addr16Bit.SetRegBits(pDemod, DTMB_I2CT_EN_CTRL, 0x0) != FUNCTION_SUCCESS)
		goto error_status_set_registers;


	// Initialize demod.
	if(pDemod->Initialize(pDemod) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Set demod IF frequency with 36 MHz.
	if(pDemod->SetIfFreqHz(pDemod, IF_FREQ_36000000HZ) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Set demod spectrum mode with SPECTRUM_NORMAL.
	if(pDemod->SetSpectrumMode(pDemod, SPECTRUM_NORMAL) != FUNCTION_SUCCESS)
		goto error_status_execute_function;


	// Set demod registers.
	for(i = 0; i < RTL2836B_DTMB_VA1E1ED2403_ADDITIONAL_INIT_REG_TABLE_LEN; i++)
	{
		// Get register bit name and its value.
		RegBitName = AdditionalInitRegValueTable[i].RegBitName;
		Value      = AdditionalInitRegValueTable[i].Value;

		// Set demod registers
		if(pDemod->RegAccess.Addr16Bit.SetRegBits(pDemod, RegBitName, Value) != FUNCTION_SUCCESS)
			goto error_status_set_registers;
	}


	return FUNCTION_SUCCESS;


error_status_execute_function:
error_status_set_registers:
	return FUNCTION_ERROR;
}