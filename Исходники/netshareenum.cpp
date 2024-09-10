int smb_netshareenum(SMBHANDLE inConnection, CFDictionaryRef *outDict, 
					 int DiskAndPrintSharesOnly)
{
	int error = 0;
	NTSTATUS status;
	SMBServerPropertiesV1 properties;
	CFMutableDictionaryRef shareDict = NULL;
	uint32_t ii;
	CFStringRef shareName, comments;
	u_int16_t shareType;
	struct statfs *fs = NULL;
	int fs_cnt = 0;
	
	fs = smb_getfsstat(&fs_cnt);

	shareDict = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, 
										 &kCFTypeDictionaryKeyCallBacks, 
										 &kCFTypeDictionaryValueCallBacks);
	if (shareDict == NULL) {
		error = ENOMEM;
		goto done;
	}
	
	status = SMBGetServerProperties(inConnection, &properties, kPropertiesVersion, sizeof(properties));
	if (!NT_SUCCESS(status)) {
		/* Should never happen */
		error = errno;
		goto done;
	}
	/* Only use RPC if the server supports DCE/RPC and UNICODE */
	if (properties.capabilities & SMB_CAP_RPC_REMOTE_APIS) {
		PSHARE_ENUM_STRUCT InfoStruct = NULL;
		NET_API_STATUS api_status;
		
		/* Try getting a list of shares with the SRVSVC RPC service. */
		api_status = NetShareEnum(properties.serverName, 1, &InfoStruct);
		if (api_status == 0) {
			for (ii = 0; ii < InfoStruct->ShareInfo.Level1->EntriesRead; ii++) {
				shareType = OSSwapLittleToHostInt16(InfoStruct->ShareInfo.Level1->Buffer[ii].shi1_type);
				/* They only want the disk and printer shares */
				if (DiskAndPrintSharesOnly && (shareType != SMB_ST_DISK) && (shareType != SMB_ST_PRINTER))
					continue;
				shareName = convertToStringRef(InfoStruct->ShareInfo.Level1->Buffer[ii].shi1_netname, 1024, TRUE);
				if (shareName == NULL) {
					continue;
				}
				if (InfoStruct->ShareInfo.Level1->Buffer[ii].shi1_remark) {
					comments = convertToStringRef(InfoStruct->ShareInfo.Level1->Buffer[ii].shi1_remark, 1024, TRUE);
				} else {
					comments = NULL;
				}
				addShareToDictionary(inConnection, shareDict, shareName, comments, shareType, fs, fs_cnt);
				CFRelease(shareName);
				if (comments) {
					CFRelease(comments);
				}
			}
			NetApiBufferFree(InfoStruct);
			goto done;
		} 
		SMBLogInfo("Looking up shares with RPC failed api_status = %d", ASL_LEVEL_DEBUG, api_status);
	}
	/*
	 * OK, that didn't work - either they don't support RPC or we
	 * got an error in either case try RAP if enabled (lanman_on pref is set).
	 */
	if (properties.internalFlags & kLanmanOn) {
		void *rBuffer = NULL;
		unsigned char *endBuffer;
		uint32_t rBufferSize = 0;
		struct smb_share_info_1 *shareInfo1;
		uint32_t entriesRead = 0;
        
		SMBLogInfo("Looking up shares RAP", ASL_LEVEL_DEBUG);

		/* Try getting a list of shares with the RAP protocol. */
		error = RapNetShareEnum(inConnection, 1, &rBuffer, &rBufferSize, &entriesRead, NULL);
		if (error) {
			SMBLogInfo("Looking up shares with RAP failed, error=%d", ASL_LEVEL_DEBUG, error);
			goto done;		
		}
		endBuffer = (unsigned char *)rBuffer + rBufferSize;

		for (shareInfo1 = (struct smb_share_info_1 *)rBuffer, ii = 0;
			 (ii < entriesRead) && (((unsigned  char *)shareInfo1 + sizeof(smb_share_info_1)) <= endBuffer); 
			 ii++, shareInfo1++) {
			
			shareInfo1->shi1_pad = 0; /* Just to be safe */
			/* Note we need to swap this item */
			shareType = OSSwapLittleToHostInt16(shareInfo1->shi1_type);
			shareName = convertToStringRef(shareInfo1->shi1_netname,  sizeof(shareInfo1->shi1_netname), FALSE);
			if (shareName == NULL) {
				continue;
			}
			/* Assume we have no comments for this entry */ 
			comments = NULL;
			/* 
			 * The shi1_remark gets swapped in the rap processing, someday we just
			 * take another look at this an make it work the same for all values.
			 */
			if ((shareInfo1->shi1_remark != 0) && (shareInfo1->shi1_remark < rBufferSize)) {
				unsigned char *remarks = (unsigned char *)rBuffer + shareInfo1->shi1_remark;
				
				/*
				 * Make sure the comments don't start pass the end of the buffer
				 * and we have a comment. 
				 */
				if ((remarks < endBuffer) && *remarks) {
					size_t maxlen = endBuffer - remarks;
					/* Now make sure the comment is a null terminate string */
					maxlen = smb_strnlen((const char *)remarks, maxlen);
					remarks[maxlen] = 0;
					comments = convertToStringRef(remarks, maxlen, FALSE);
				}

			}
			addShareToDictionary(inConnection, shareDict, shareName, comments, shareType, fs, fs_cnt);
			CFRelease(shareName);
			if (comments) {
				CFRelease(comments);
			}
		}
		RapNetApiBufferFree(rBuffer);
	}
done:
	if (fs) {
		free(fs);
	}
	if (error) {
		*outDict = NULL;
		if (shareDict) {
			CFRelease(shareDict);
		}
	} else {
		*outDict = shareDict;
	}
	return error;
}