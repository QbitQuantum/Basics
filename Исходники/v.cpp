//////////
//
// Function: VAL()
// Returns a numeric or currency value from a expression.
//
//////
// Version 0.58
// Last update:
//     Mar.22.2015
//////
// Change log:
//     Mar.21.2015 - Initial creation by Stefano D'Amico
//////
// Parameters:
//     varExpr			-- Any, to convert
//	   varIgnoreList	-- Characters to ignore
//
//////
// Returns:
//    Numeric		--	VAL( ) returns the numbers in the character expression from left to right until a non-numeric character is encountered.
//						Leading blanks are ignored.
//						VAL( ) returns 0 if the first character of the character expression is not a number, a dollar sign ($), a plus sign (+), or minus sign (-).
//////
	void function_val(SReturnsParams* rpar)
	{
		SVariable*	varExpr			= rpar->ip[0];
		SVariable*	varIgnoreChars	= rpar->ip[1];

		s8			c, cCurrency, cPoint, cSeparator;
		s32			lnI, lnJ, lnBuffOffset;
		s64			lnValue;
		f64			lfValue;
		bool		llAsInteger, llStillGoing, llCurrency;
		SVariable*	varCurrency;
		SVariable*	varPoint;
		SVariable*	varSeparator;
		SVariable*	result;
		u32			errorNum;
        bool		error;
		s8			buffer[64];


		//////////
		// Parameter 1 must be valid
		//////
			rpar->rp[0] = NULL;
			if (!iVariable_isValid(varExpr))
			{
				iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varExpr), false);
				return;
			}


		//////////
		// If numeric, copy whatever's already there
		//////
			if (varExpr->varType >= _VAR_TYPE_NUMERIC_START && varExpr->varType <= _VAR_TYPE_NUMERIC_END)
			{
				// Copy The existing variable
				result = iVariable_copy(varExpr, false);
				if (!result)
					iError_report_byNumber(_ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(varExpr), false);

				// Success or failure, return our result
				rpar->rp[0] = result;
				return;
			}



		//////////
		// Determine what we're evaluating
		//////
			switch (varExpr->varType)
			{
				case _VAR_TYPE_NULL:
					iError_report_byNumber(_ERROR_P1_IS_INCORRECT, iVariable_get_relatedComp(varExpr), false);
					return;
					break;

				case _VAR_TYPE_LOGICAL:		// 0=.F., 1=.T.
				case _VAR_TYPE_DATE:		// YYYYMMDD
					result = iVariable_create(_VAR_TYPE_S32, NULL, true);
					if (result)
					{
						// Populate the s32
						*result->value.data_s32 = iiVariable_getAs_s32(varExpr, true, &error, &errorNum);
						if (error)
							iError_report_byNumber(errorNum, iVariable_get_relatedComp(varExpr), false);
					}
					break;

				case _VAR_TYPE_DATETIME:
					// YYYYMMDDHhMmSsMss as s64
				case _VAR_TYPE_DATETIMEX:
					// YYYYMMDDHhMmSsNssssssss
					result = iVariable_create(_VAR_TYPE_S64, NULL, true);
					if (result)
					{
						// Populate the s64
						*result->value.data_s64 = iiVariable_getAs_s64(varExpr, true, &error, &errorNum);
						if (error)
							iError_report_byNumber(errorNum, iVariable_get_relatedComp(varExpr), false);
					}
					break;

				case _VAR_TYPE_CHARACTER:

					//////////
					// If present, parameter 2 must be valid
					//////
						if (varIgnoreChars)
						{
							if (!iVariable_isValid(varIgnoreChars) || !iVariable_isTypeCharacter(varIgnoreChars))
							{
								iError_report_byNumber(_ERROR_P2_IS_INCORRECT, iVariable_get_relatedComp(varIgnoreChars), false);
								return;
							}
						}


					//////////
					// Prepare our characters
					//////
						varCurrency		= propGet_settings_Currency(_settings);
						varPoint		= propGet_settings_Point(_settings);
						varSeparator	= propGet_settings_Separator(_settings);
						if (!varCurrency || !varPoint || !varSeparator)
						{
							// Should never happen
							iError_report_byNumber(_ERROR_INTERNAL_ERROR, NULL, false);
							return;
						}


					//////////
					// Create single characters
					//////
						cCurrency	= varCurrency->value.data_s8[0];
						cPoint		= varPoint->value.data_s8[0];
						cSeparator	= varSeparator->value.data_s8[0];


					//////////
					// Iterate through each character
					//////
						for (lnI = 0, lnBuffOffset = 0, llStillGoing = true, llCurrency = false; llStillGoing && lnI < (s32)varExpr->value.length && lnBuffOffset < (s32)sizeof(buffer) - 1; lnI++)
						{

							//////////
							// Grab this character
							//////
								c = varExpr->value.data[lnI];


							//////////
							// Is it a character we're including in our buffer (a number, or natural number-related symbol)?
							//////
								if ((c >= '0' && c <= '9' ) || c == '+' || c == '-' || c == cPoint)
								{
									// Yes, Copy this character
									buffer[lnBuffOffset++] = c;

								} else {
									// Are we still in a valid sequence of characters to skip?
									if (c == ' ' || c == cSeparator)
									{
										// It's a character we're skipping naturally (space, separator symbol)
										// We don't do anything here ... it's just more clear to keep this logic visible rather than inverting it. :-)

									} else if (c == cCurrency) {
										// We encountered the currency symbol, so the output will be currency
										llCurrency = true;

									} else if (varIgnoreChars) {
										// We won't continue unless we're sitting on a character in the varIgnoreChars
										for (lnJ = 0, llStillGoing = false; lnJ < varIgnoreChars->value.length; lnJ++)
										{
											// Is this one of our skip characters?
											if (c == varIgnoreChars->value.data_s8[lnJ])
											{
												llStillGoing = true;
												break;
											}
										}

									} else {
										// We're done
										break;
									}
								}

						}

						// NULL terminate
						buffer[lnBuffOffset] = 0;


					//////////
					// Convert to f64, and s64
					//////
						lfValue = atof(buffer);
#if defined(__GNUC__) || defined(__solaris__)
						lnValue = strtoll(buffer, NULL, 10);
#else
						lnValue = _strtoi64(buffer, NULL, 10);
#endif


					//////////
					// Is currency or not? If it's an integer value, store it as the same, otherwise use floating point
					//////
						if ((f64)lnValue == lfValue)
						{
							// We can return as an integer
							llAsInteger = true;
							if (llCurrency)
							{
								// Multiply by 10000 to obtain the 4 implied decimal places
								lnValue = lnValue * 10000;
								result	= iVariable_create(_VAR_TYPE_CURRENCY, NULL, true);

							} else {
								if (lnValue < (s64)_s32_max)
								{
									// We can create as an s32
									result = iVariable_create(_VAR_TYPE_S32, NULL, true);

								} else {
									// Create as an s64
									result = iVariable_create(_VAR_TYPE_S64, NULL, true);
								}
							}

						} else {
							// Must return as f64
							llAsInteger	= false;
							if (llCurrency)
							{
								// As currency
								lfValue	*= 10000.0;
								result	= iVariable_create(_VAR_TYPE_CURRENCY, NULL, true);

							} else {
								// As is
								result	= iVariable_create(_VAR_TYPE_F64, NULL, true);
							}
						}


					//////////
					// Store the result
					//////
						if (result)
						{
							if (llAsInteger)	iVariable_setNumeric_toNumericType(result, NULL, NULL, NULL, NULL, &lnValue, NULL);
							else				iVariable_setNumeric_toNumericType(result, NULL, &lfValue, NULL, NULL, NULL, NULL);
						}
						break;

				default:
					// Unrecognized type
					iError_report_byNumber(_ERROR_FEATURE_NOT_AVAILABLE, iVariable_get_relatedComp(varExpr), false);
					return;
			}


		//////////
		// Are we good?
		//////
			if (!result)
				iError_report_byNumber(_ERROR_INTERNAL_ERROR, iVariable_get_relatedComp(varExpr), false);


		//////////
        // Return our converted result
		//////
			rpar->rp[0] = result;

	}