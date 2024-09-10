/****************************************************************************
Desc:
****************************************************************************/
RCODE JNIBackupClient::WriteData(
	const void *	pvBuffer,
	FLMUINT			uiBytesToWrite)
{
	RCODE				rc = NE_XFLM_OK;
	JNIEnv *			pEnv;
	jclass			Cls;
	jmethodID		MId;
	jbyteArray		jBuff = NULL;
	void *			pvBuff;
	FLMBOOL			bMustDetach = FALSE;
	
	if (m_pJvm->GetEnv( (void **)&pEnv, JNI_VERSION_1_2) != JNI_OK)
	{
		if (m_pJvm->AttachCurrentThread( (void **)&pEnv, NULL) != 0)
		{
			rc = RC_SET( NE_XFLM_FAILURE);	
			goto Exit;
		}
		
		bMustDetach = TRUE;
	}
	
	Cls = pEnv->GetObjectClass( m_jClient);
	MId = pEnv->GetMethodID( Cls, "WriteData", "([B)I");
	
	flmAssert( MId);
	
	if ((jBuff = pEnv->NewByteArray( (jsize)uiBytesToWrite)) == NULL)
	{
		rc = RC_SET( NE_XFLM_MEM);
		goto Exit;
	}
	pvBuff = pEnv->GetPrimitiveArrayCritical(jBuff, NULL);
	f_memcpy(pvBuff, pvBuffer, uiBytesToWrite);
	pEnv->ReleasePrimitiveArrayCritical( jBuff, pvBuff, 0);
	
	if( RC_BAD( rc = (RCODE)pEnv->CallIntMethod( m_jClient, MId, jBuff)))
	{
		goto Exit;
	}
		
Exit:

	if (jBuff)
	{
		pEnv->DeleteLocalRef( jBuff);
	}

	if (bMustDetach)
	{
		if (m_pJvm->DetachCurrentThread() != 0)
		{
			flmAssert( 0);
			rc = RC_SET( NE_XFLM_FAILURE);
		}
	}

	return( rc);
}