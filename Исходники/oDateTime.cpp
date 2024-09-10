// set the value of a property
qbool oDateTime::setProperty(qlong pPropID,EXTfldval &pNewValue,EXTCompInfo* pECI) {
	// most anum properties are managed by Omnis but some we need to do ourselves, no idea why...
	
	switch (pPropID) {
		case oDT_localtime: {
			datestamptype omnisstamp;
			qbool success;
			pNewValue.getDate(omnisstamp, dpFdtimeC, &success);
			
			if (success) {
				struct tm timestruct;
				
				OmnisToTimeStruct(omnisstamp, timestruct);
				
				setTimestamp(mktime(&timestruct));
			};
			return qtrue;
		}; break;
		case oDT_utctime: {
			datestamptype omnisstamp;
			qbool success;
			pNewValue.getDate(omnisstamp, dpFdtimeC, &success);
			
			if (success) {
				struct tm timestruct;
				
				OmnisToTimeStruct(omnisstamp, timestruct);
				
#ifdef iswin32
				setTimestamp(_mkgmtime(&timestruct));
#else
				setTimestamp(timegm(&timestruct));
#endif
			};
			return qtrue;
		}; break;
		default:
			return oBaseNVComponent::setProperty(pPropID, pNewValue, pECI);
			break;
	};
};