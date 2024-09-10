vector<CLogModel*> CHistoryItemLogParser::ParseLog(long& lPosition, long lLength, char* pBuffer)
{
	map<long long,string> mapHostMacDict;
	string strFormatLog;
	stringstream strErrorMess;
	int iZbxServerId, iValueType, iMaintenance;	
	string strHost, strKey_, strHostName, strIfAddress, strZbIpAddress, strSerialNumber;
	string strTemp;
	string strValue;
	HostInfo tagHostInfo;
	long long lItemId, lClock, lHostId, lServerId;

	
	vector<CLogModel*> vtHistoryItemModelPtr;

	while (lPosition < lLength) 
	{
		//	ResetHostInfo(tagHostInfo);
			// Init database fields
		lClock = iZbxServerId = lHostId = lItemId = iValueType = lServerId = iMaintenance = 0;
		strKey_ = strValue = strHost = strHostName = strIfAddress = strZbIpAddress = strSerialNumber = "";
		CLogModel* pLogModel = RegisterModel();

		//Parse Clock
		lClock = ParseLong((const char*)pBuffer, lPosition, lLength);

		//Parse ServerId
		iZbxServerId = ParseInt((const char*)pBuffer, lPosition, lLength);

		//Parse HostId
		lHostId = ParseLong((const char*)pBuffer, lPosition, lLength);
			
		// Calculate ServerId
		lServerId = ((lHostId - 10000) * 256) + iZbxServerId;

		//Parse Hostname
		strTemp = GetBlock((const char*)pBuffer, lPosition, lLength);
		if(strTemp.compare("") != 0)
		{
			strHostName = strTemp;
			strHostName = CUtilities::ReplaceBlockBracket(strHostName);
			strHost = strHostName;
		}

		//Parse zb IP Address
		strTemp = GetBlock((const char*)pBuffer, lPosition, lLength);
		if(strTemp.compare("") != 0)
		{
			strIfAddress = strTemp;
			strIfAddress = CUtilities::ReplaceBlockBracket(strIfAddress);
			strZbIpAddress = strIfAddress;
		}

		//Parse Maintenance Status
		iMaintenance = ParseInt((const char*)pBuffer, lPosition, lLength);

		//Parse ItemId
		lItemId = ParseLong((const char*)pBuffer, lPosition, lLength);			
			
		//Parse Key_
		strKey_ = GetItemKey((const char*)pBuffer, lPosition, lLength);
			
		//Parse Value Type
		iValueType = ParseInt((const char*)pBuffer, lPosition, lLength);			

		//Parse Value
		if (strKey_.compare(SYSTEM_INFO) == 0 
			|| strKey_.compare(VB_SYSTEM_INFO) == 0 
			|| strKey_.compare(OS_INFO) == 0)
		{
			try
			{
				//ParseSystemInfo((const char*)pBuffer, lPosition, lLength, lServerId, mapHostMacDict, tagHostInfo);
				strValue = GetValueBlock((const char*)pBuffer, lPosition, lLength);
			}
			catch(exception& ex)
			{
				strErrorMess << ex.what() << " " << __FILE__ << " " << __LINE__;
				strFormatLog = CUtilities::FormatLog(ERROR_MSG, "CHistoryItemLogParser", "ParseLog", strErrorMess.str());
				CUtilities::WriteErrorLog(strFormatLog);
			}
		}
		else if (strKey_.compare(SDK_READ_TEXT) == 0 || strKey_.compare(SDK_READ_TEXT_LINUX) == 0)
		{
			strTemp = GetToken((const char*)pBuffer, lPosition, lLength);
			if (strTemp.compare("") != 0)
			{
				strValue = strTemp;
				strSerialNumber = strValue;
				strSerialNumber.erase(std::find_if(tagHostInfo.strSerialNumber.rbegin(), tagHostInfo.strSerialNumber.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), tagHostInfo.strSerialNumber.end());
			}
		}

		else
			strValue = GetItemValue((const char*)pBuffer, lPosition, lLength);
		
		CHistoryItemModel *pHistoryItemModel = dynamic_cast<CHistoryItemModel*>(pLogModel);

		pHistoryItemModel->SetItemId(lItemId);
		pHistoryItemModel->SetKey_(strKey_);
		pHistoryItemModel->SetValueType(iValueType);
		pHistoryItemModel->SetValue(strValue);
		pHistoryItemModel->SetServerId(lServerId);
		pHistoryItemModel->SetZabbixServerId(iZbxServerId);
		pHistoryItemModel->SetHostId(lHostId);
		pHistoryItemModel->SetSerialNumber(strSerialNumber);
		pHistoryItemModel->SetHost(strHost);
		pHistoryItemModel->SetHostName(strHostName);
		pHistoryItemModel->SetZbIpAddress(strZbIpAddress);
		pHistoryItemModel->SetMaintenance(iMaintenance);
		pHistoryItemModel->SetClock(lClock);

		if (ExtractData(pHistoryItemModel))
		{
			vtHistoryItemModelPtr.push_back(pHistoryItemModel);
		}
		else
		{
			delete pHistoryItemModel;
		}
	}
	return vtHistoryItemModelPtr;
}