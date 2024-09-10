bool cConfigItem_integer::setParamFromValueStr(string value_str) {
	if(value_str.empty()) {
		return(false);
	}
	int ok = 0;
	const char *value = value_str.c_str();
	if(value) {
		int _value;
		if(getValueFromMapValues(value, &_value)) {
			if(param_int) {
				*param_int = _value;
				++ok;
			}
			if(param_uint) {
				*param_uint = _value;
				++ok;
			}
			if(param_int64) {
				*param_int64 = _value;
				++ok;
			}
			if(param_uint64) {
				*param_uint64 = _value;
				++ok;
			}
			return(ok > 0);
		}
		if(param_int) {
			*param_int = atoi(value);
			if(maximum && *param_int > maximum) {
				*param_int = maximum;
			}
			if(minimum && *param_int < minimum) {
				*param_int = minimum;
			}
			if(ifZeroOrNegative && *param_int <= 0) {
				*param_int = ifZeroOrNegative;
			}
			if(multiple) {
				*param_int *= multiple;
			}
			if(!*param_int && yesValue && yesno(value)) {
				*param_int = yesValue;
			}
			++ok;
		}
		if(param_uint) {
			if(ip) {
				struct sockaddr_in sa;
				inet_pton(AF_INET, value, &sa.sin_addr);
				*param_uint = sa.sin_addr.s_addr;
			} else  {
				*param_uint = atol(value);
				if(maximum && *param_uint > (unsigned)maximum) {
					*param_uint = maximum;
				}
				if(minimum && *param_uint < (unsigned)minimum) {
					*param_uint = minimum;
				}
				if(ifZeroOrNegative && *param_uint == 0) {
					*param_uint = ifZeroOrNegative;
				}
				if(multiple) {
					*param_uint *= multiple;
				}
				if(!*param_uint && yesValue && yesno(value)) {
					*param_uint = yesValue;
				}
			}
			++ok;
		}
		if(param_int64) {
			*param_int64 = atoll(value);
			if(maximum && *param_int64 > (unsigned)maximum) {
				*param_int64 = maximum;
			}
			if(minimum && *param_int64 < (unsigned)minimum) {
				*param_int64 = minimum;
			}
			if(ifZeroOrNegative && *param_int64 <= 0) {
				*param_int64 = ifZeroOrNegative;
			}
			if(multiple) {
				*param_int64 *= multiple;
			}
			if(!*param_int64 && yesValue && yesno(value)) {
				*param_int64 = yesValue;
			}
			++ok;
		}
		if(param_uint64) {
			*param_uint64 = atoll(value);
			if(maximum && *param_uint64 > (unsigned)maximum) {
				*param_uint64 = maximum;
			}
			if(minimum && *param_uint64 < (unsigned)minimum) {
				*param_uint64 = minimum;
			}
			if(ifZeroOrNegative && *param_uint64 <= 0) {
				*param_uint64 = ifZeroOrNegative;
			}
			if(multiple) {
				*param_uint64 *= multiple;
			}
			if(!*param_uint64 && yesValue && yesno(value)) {
				*param_uint64 = yesValue;
			}
			++ok;
		}
	}
	return(ok > 0);
}