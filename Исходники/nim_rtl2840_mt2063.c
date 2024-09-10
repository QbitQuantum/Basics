/**

@see   QAM_NIM_FP_INITIALIZE

*/
int
rtl2840_mt2063_Initialize(
	QAM_NIM_MODULE *pNim
	)
{
	typedef struct
	{
		int RegBitName;
		unsigned long Value;
	}
	REG_VALUE_ENTRY;


	static const REG_VALUE_ENTRY AdditionalInitRegValueTable[RTL2840_MT2063_ADDITIONAL_INIT_REG_TABLE_LEN] =
	{
		// RegBitName,					Value
		{QAM_OPT_RF_AAGC_DRIVE,			0x1		},
		{QAM_OPT_IF_AAGC_DRIVE,			0x1		},
		{QAM_OPT_RF_AAGC_OEN,			0x1		},
		{QAM_OPT_IF_AAGC_OEN,			0x1		},
		{QAM_RF_AAGC_MAX,				0x80	},
		{QAM_RF_AAGC_MIN,				0x80	},
		{QAM_IF_AAGC_MAX,				0xff	},
		{QAM_IF_AAGC_MIN,				0x0		},
		{QAM_AAGC_MODE_SEL,				0x0		},
	};


	TUNER_MODULE *pTuner;
	QAM_DEMOD_MODULE *pDemod;
	MT2063_EXTRA_MODULE *pTunerExtra;
	RTL2840_MT2063_EXTRA_MODULE *pNimExtra;

	int i;

	int RegBitName;
	unsigned long Value;


	// Get modules.
	pTuner = pNim->pTuner;
	pDemod = pNim->pDemod;
	pTunerExtra = &(pTuner->Extra.Mt2063);
	pNimExtra = &(pNim->Extra.Rtl2840Mt2063);


	// Initialize tuner.
	if(pTuner->Initialize(pTuner) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Set tuner IF frequency in Hz.
	if(pTunerExtra->SetIfFreqHz(pTuner, pNimExtra->IfFreqHz) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Initialize demod.
	if(pDemod->Initialize(pDemod) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Set demod IF frequency in Hz.
	if(pDemod->SetIfFreqHz(pDemod, pNimExtra->IfFreqHz) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Set demod spectrum mode with SPECTRUM_INVERSE.
	if(pDemod->SetSpectrumMode(pDemod, SPECTRUM_INVERSE) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Set demod AAGC registers.
	// Note: SetParameters() will set QAM_AAGC_TARGET and QAM_VTOP according to parameters.
	for(i = 0; i < RTL2840_MT2063_ADDITIONAL_INIT_REG_TABLE_LEN; i++)
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