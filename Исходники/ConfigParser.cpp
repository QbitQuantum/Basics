/*
** Gets the value of a section variable. Returns true if strValue is set.
** The selector is stripped from strVariable.
**
*/
bool ConfigParser::GetSectionVariable(std::wstring& strVariable, std::wstring& strValue)
{
	size_t colonPos = strVariable.find_last_of(L':');
	if (colonPos == std::wstring::npos)
	{
		return false;
	}

	const std::wstring selector = strVariable.substr(colonPos + 1);
	const WCHAR* selectorSz = selector.c_str();
	strVariable.resize(colonPos);

	bool isKeySelector = (!selector.empty() && iswalpha(selectorSz[0]));

	if (isKeySelector)
	{
		// [Meter:X], [Meter:Y], [Meter:W], [Meter:H]
		Meter* meter = m_Skin->GetMeter(strVariable);
		if (meter)
		{
			WCHAR buffer[32];
			if (_wcsicmp(selectorSz, L"X") == 0)
			{
				_itow_s(meter->GetX(), buffer, 10);
			}
			else if (_wcsicmp(selectorSz, L"Y") == 0)
			{
				_itow_s(meter->GetY(), buffer, 10);
			}
			else if (_wcsicmp(selectorSz, L"W") == 0)
			{
				_itow_s(meter->GetW(), buffer, 10);
			}
			else if (_wcsicmp(selectorSz, L"H") == 0)
			{
				_itow_s(meter->GetH(), buffer, 10);
			}
			else
			{
				return false;
			}

			strValue = buffer;
			return true;
		}
	}

	// Number: [Measure:], [Measure:dec]
	// Percentual: [Measure:%], [Measure:%, dec]
	// Scale: [Measure:/scale], [Measure:/scale, dec]
	// Max/Min: [Measure:MaxValue], [Measure:MaxValue:/scale, dec] ('%' cannot be used)
	// EscapeRegExp: [Measure:EscapeRegExp] (Escapes regular expression syntax, used for 'IfMatch')
	// EncodeUrl: [Measure:EncodeUrl] (Escapes URL reserved characters)
	// TimeStamp: [TimeMeasure:TimeStamp] (ONLY for Time measures, returns the Windows timestamp of the measure)
	enum class ValueType
	{
		Raw,
		Percentual,
		Max,
		Min,
		EscapeRegExp,
		EncodeUrl,
		TimeStamp
	} valueType = ValueType::Raw;

	if (isKeySelector)
	{
		if (_wcsicmp(selectorSz, L"MaxValue") == 0)
		{
			valueType = ValueType::Max;
		}
		else if (_wcsicmp(selectorSz, L"MinValue") == 0)
		{
			valueType = ValueType::Min;
		}
		else if (_wcsicmp(selectorSz, L"EscapeRegExp") == 0)
		{
			valueType = ValueType::EscapeRegExp;
		}
		else if (_wcsicmp(selectorSz, L"EncodeUrl") == 0)
		{
			valueType = ValueType::EncodeUrl;
		}
		else if (_wcsicmp(selectorSz, L"TimeStamp") == 0)
		{
			valueType = ValueType::TimeStamp;
		}
		else
		{
			return false;
		}

		selectorSz = L"";
	}
	else
	{
		colonPos = strVariable.find_last_of(L':');
		if (colonPos != std::wstring::npos)
		{
			do
			{
				const WCHAR* keySelectorSz = strVariable.c_str() + colonPos + 1;

				if (_wcsicmp(keySelectorSz, L"MaxValue") == 0)
				{
					valueType = ValueType::Max;
				}
				else if (_wcsicmp(keySelectorSz, L"MinValue") == 0)
				{
					valueType = ValueType::Min;
				}
				else
				{
					// Section name contains ':' ?
					break;
				}

				strVariable.resize(colonPos);
			}
			while (0);
		}
	}

	Measure* measure = m_Skin->GetMeasure(strVariable);
	if (measure)
	{
		if (valueType == ValueType::EscapeRegExp)
		{
			strValue = measure->GetStringValue();
			StringUtil::EscapeRegExp(strValue);
			return true;
		}
		else if (valueType == ValueType::EncodeUrl)
		{
			strValue = measure->GetStringValue();
			StringUtil::EncodeUrl(strValue);
			return true;
		}
		else if (measure->GetTypeID() == TypeID<MeasureTime>() && valueType == ValueType::TimeStamp)
		{
			MeasureTime* time = (MeasureTime*)measure;
			strValue = std::to_wstring(time->GetTimeStamp().QuadPart / 10000000);
			return true;
		}

		int scale = 1;

		const WCHAR* decimalsSz = wcschr(selectorSz, L',');
		if (decimalsSz)
		{
			++decimalsSz;
		}

		if (*selectorSz == L'%')  // Percentual
		{
			if (valueType == ValueType::Max || valueType == ValueType::Min)
			{
				// '%' cannot be used with Max/Min values.
				return false;
			}

			valueType = ValueType::Percentual;
		}
		else if (*selectorSz == L'/')  // Scale
		{
			errno = 0;
			scale = _wtoi(selectorSz + 1);
			if (errno == EINVAL || scale == 0)
			{
				// Invalid scale value.
				return false;
			}
		}
		else
		{
			if (decimalsSz)
			{
				return false;
			}

			decimalsSz = selectorSz;
		}

		const double value =
			(valueType == ValueType::Percentual) ? measure->GetRelativeValue() * 100.0 :
			(valueType == ValueType::Max)        ? measure->GetMaxValue() / scale :
			(valueType == ValueType::Min)        ? measure->GetMinValue() / scale :
			                                       measure->GetValue() / scale;
		int decimals = 10;
		if (decimalsSz)
		{
			while (iswspace(*decimalsSz)) ++decimalsSz;

			if (*decimalsSz)
			{
				decimals = _wtoi(decimalsSz);
				decimals = max(0, decimals);
				decimals = min(32, decimals);
			}
			else
			{
				decimalsSz = nullptr;
			}
		}

		WCHAR format[32];
		WCHAR buffer[128];
		_snwprintf_s(format, _TRUNCATE, L"%%.%if", decimals);
		int bufferLen = _snwprintf_s(buffer, _TRUNCATE, format, value);
			
		if (!decimalsSz)
		{
			// Remove trailing zeros if decimal count was not specified.
			measure->RemoveTrailingZero(buffer, bufferLen);
			bufferLen = (int)wcslen(buffer);
		}

		strValue.assign(buffer, bufferLen);
		return true;
	}
	
	return false;
}