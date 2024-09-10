string Func_sec_to_time::getStrVal(rowgroup::Row& row,
							FunctionParm& parm,
							bool& isNull,
							CalpontSystemCatalog::ColType& ct)
{
	
	int64_t val = 0;
	CalpontSystemCatalog::ColType curCt = parm[0]->data()->resultType();
	switch (parm[0]->data()->resultType().colDataType)
	{
		case execplan::CalpontSystemCatalog::BIGINT:
		case execplan::CalpontSystemCatalog::INT:
		case execplan::CalpontSystemCatalog::MEDINT:
		case execplan::CalpontSystemCatalog::TINYINT:
		case execplan::CalpontSystemCatalog::SMALLINT:
        case execplan::CalpontSystemCatalog::UBIGINT:
        case execplan::CalpontSystemCatalog::UINT:
        case execplan::CalpontSystemCatalog::UMEDINT:
        case execplan::CalpontSystemCatalog::UTINYINT:
        case execplan::CalpontSystemCatalog::USMALLINT:
		{
			val = parm[0]->data()->getIntVal(row, isNull);
		}
		break;

		case execplan::CalpontSystemCatalog::DOUBLE:
		{
			const string& valStr = parm[0]->data()->getStrVal(row, isNull);
			val = parm[0]->data()->getIntVal(row, isNull);
			size_t x = valStr.find(".");
			if ( x < string::npos)
			{
				string tmp = valStr.substr(x+1,1);
				char * ptr = &tmp[0];
				int i = atoi(ptr);
				if (i >= 5)
				{
					if (val > 0)
						val += 1;
					else 
						val -=1;
				}
			}
		}
		break;

		case execplan::CalpontSystemCatalog::FLOAT:
		{
			const string& valStr = parm[0]->data()->getStrVal(row, isNull);
			val = parm[0]->data()->getIntVal(row, isNull);
			size_t x = valStr.find(".");
			if ( x < string::npos)
			{
				string tmp = valStr.substr(x+1,1);
				char * ptr = &tmp[0];
				int i = atoi(ptr);
				if (i >= 5)
				{
					if (val > 0)
						val += 1;
					else 
						val -=1;
				}
			}
		}
		break;

		case execplan::CalpontSystemCatalog::DECIMAL:
		{
			const string& valStr = parm[0]->data()->getStrVal(row, isNull);
			
			val = parm[0]->data()->getIntVal(row, isNull);
			size_t x = valStr.find(".");
			if ( x < string::npos)
			{
				string tmp = valStr.substr(x+1,1);
				char * ptr = &tmp[0];
				int i = atoi(ptr);
				if (i >= 5)
				{
					if (val > 0)
						val += 1;
					else 
						val -=1;
				}
			}
		}
		break;
		
		case execplan::CalpontSystemCatalog::CHAR:
		case execplan::CalpontSystemCatalog::VARCHAR:
		{
			val = parm[0]->data()->getIntVal(row, isNull);
	        
			break;
		}

		default:
		{
			std::ostringstream oss;
			oss << "sec_to_time: datatype of " << execplan::colDataTypeToString(parm[0]->data()->resultType().colDataType);
			throw logging::IDBExcept(oss.str(), ERR_DATATYPE_NOT_SUPPORT);
		}
	}
	
	int64_t posVal = llabs(val);
	if (val >3020399)
		return ("838:59:59");
		
	if (val < -3020399)
		return ("-838:59:59");
		
	//Format the time
	uint32_t hour = 0;
	uint32_t minute = 0;
	uint32_t second = 0;
		
	hour = posVal / 3600;
	minute = (posVal - (hour * 3600)) / 60;
	second = posVal - (hour * 3600) - (minute * 60);
    
    const char* minus = "-";
    const char* nominus = "";
	
	const char* signstr = ( val < 0 ) ? minus : nominus;
   
	char buf[32]; // actual string either 9 or 10 characters
    snprintf( buf, 32, "%s%02d:%02d:%02d", signstr, hour, minute, second );
	return buf;
}