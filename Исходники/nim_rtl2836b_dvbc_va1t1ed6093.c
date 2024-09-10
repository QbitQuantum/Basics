/**

@see   QAM_NIM_FP_INITIALIZE

*/
int
rtl2836b_dvbc_va1t1ed6093_Initialize(
	QAM_NIM_MODULE *pNim
	)
{
	typedef struct
	{
		int RegBitName;
		unsigned long Value;
	}
	REG_VALUE_ENTRY;


	static const REG_VALUE_ENTRY AdditionalInitRegValueTable[RTL2836B_DVBC_VA1T1ED6093_ADDITIONAL_INIT_REG_TABLE_LEN] =
	{
		// RegBitName,					Value
		{QAM_AGC_DRIVE_LV,				0x0		},
		{QAM_OPT_RF_AAGC_DRIVE,			0x0		},
		{QAM_OPT_IF_AAGC_DRIVE,			0x0		},
		{QAM_OPT_RF_AAGC_OE,			0x0		},
		{QAM_OPT_IF_AAGC_OE,			0x1		},
		{QAM_PAR_RF_SD_IB,				0x1		},
		{QAM_PAR_IF_SD_IB,				0x1		},
		{QAM_RF_AAGC_MAX,				0x80	},
		{QAM_RF_AAGC_MIN,				0x80	},
		{QAM_IF_AAGC_MAX,				0xff	},
		{QAM_IF_AAGC_MIN,				0x0		},
		{QAM_VTOP,						0x80	},
		{QAM_KRF_MSB,					0x1		},
		{QAM_KRF_LSB,					0x1		},
		{QAM_AAGC_MODE_SEL,				0x0		},
	};


	QAM_DEMOD_MODULE *pDemod;
	TUNER_MODULE *pTuner;

	int i;

	int RegBitName;
	unsigned long Value;


	// Get demod module and tuner module.
	pDemod = pNim->pDemod;
	pTuner = pNim->pTuner;


	// Enable demod QAM_I2CT_EN_CTRL.
	if(pDemod->RegAccess.Addr16Bit.SetRegBits(pDemod, QAM_I2CT_EN_CTRL, 0x1) != FUNCTION_SUCCESS)
		goto error_status_set_registers;

	// Initialize tuner.
	if(pTuner->Initialize(pTuner) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Disable demod QAM_I2CT_EN_CTRL.
	if(pDemod->RegAccess.Addr16Bit.SetRegBits(pDemod, QAM_I2CT_EN_CTRL, 0x0) != FUNCTION_SUCCESS)
		goto error_status_set_registers;


	// Initialize demod.
	if(pDemod->Initialize(pDemod) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Set demod IF frequency with 36 MHz.
	if(pDemod->SetIfFreqHz(pDemod, IF_FREQ_36000000HZ) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Set demod spectrum mode with SPECTRUM_NORMAL.
	// Note: RTL2836B DVB-C demod hardware will detect spectrum mode automatically,
	//       even if one uses SetSpectrumMode() to set spectrum mode.
	if(pDemod->SetSpectrumMode(pDemod, SPECTRUM_NORMAL) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Set demod AAGC registers.
	// Note: SetParameters() will set QAM_AAGC_TARGET and QAM_VTOP according to parameters.
	for(i = 0; i < RTL2836B_DVBC_VA1T1ED6093_ADDITIONAL_INIT_REG_TABLE_LEN; i++)
	{
		// Get register bit name and its value.
		RegBitName = AdditionalInitRegValueTable[i].RegBitName;
		Value      = AdditionalInitRegValueTable[i].Value;

		// Set demod registers
		if(pDemod->RegAccess.Addr16Bit.SetRegBits(pDemod, RegBitName, Value) != FUNCTION_SUCCESS)
			goto error_status_set_registers;
	}


	return FUNCTION_SUCCESS;


error_status_set_registers:
error_status_execute_function:
	return FUNCTION_ERROR;
}