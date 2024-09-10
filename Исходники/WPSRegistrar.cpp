int WPSRegistrar::ProcessDone()
{
	uint32 err;

	err = g_regProtocol.ProcessMessageDone(&m_regInfo, m_msgBuffer );
    if(WSC_SUCCESS != err)
    {
		return err_process_Done;
    }
	printf("\n*****  Successfully processed Message Done\n");
	if (m_regInfo.p_enrolleeInfo) {
		WPSDeviceWasAuthenticated(* ((GUID*) & (m_regInfo.p_enrolleeInfo->uuid)));
	}

	//****** Derivation of UPnP Protected Setup AuthKey and KeyWrapKey ******
    //1. declare and initialize the appropriate buffer objects
	BufferObj kdkBuf(m_regInfo.emsk.GetBuf(), SIZE_256_BITS);
    BufferObj pString((uint8 *)UPNP_PERSONALIZATION_STRING, 
                        strlen(UPNP_PERSONALIZATION_STRING));
    BufferObj keys;

    //2. call the key derivation function
    g_regProtocol.DeriveKey(kdkBuf, pString, 256 + 128, keys);

    //3. split the key into the component keys and store them
    keys.Rewind(keys.Length());
    m_regInfo.UPnPPSauthKey.Reset();
	m_regInfo.UPnPPSkeyWrapKey.Reset();

	m_regInfo.UPnPPSauthKey.Append(SIZE_256_BITS, keys.Pos());
    keys.Advance(SIZE_256_BITS);

    m_regInfo.UPnPPSkeyWrapKey.Append(SIZE_128_BITS, keys.Pos());
	// **** End of key derivation code

	return init;
}