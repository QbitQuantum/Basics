bool DataTable_SetupReceiveTableFromSendTable( SendTable *sendTable, bool bNeedsDecoder )
{
	CClientSendTable *pClientSendTable = new CClientSendTable;
	SendTable *pTable = &pClientSendTable->m_SendTable;
	g_ClientSendTables.AddToTail( pClientSendTable );

	// Read the name.
	pTable->m_pNetTableName = COM_StringCopy( sendTable->m_pNetTableName );

	// Create a decoder for it if necessary.
	if ( bNeedsDecoder )
	{
		// Make a decoder for it.
		CRecvDecoder *pDecoder = new CRecvDecoder;
		g_RecvDecoders.AddToTail( pDecoder );
		
		RecvTable *pRecvTable = FindRecvTable( pTable->m_pNetTableName );
		if ( !pRecvTable )
		{
			DataTable_Warning( "No matching RecvTable for SendTable '%s'.\n", pTable->m_pNetTableName );
			return false;
		}

		pRecvTable->m_pDecoder = pDecoder;
		pDecoder->m_pTable = pRecvTable;

		pDecoder->m_pClientSendTable = pClientSendTable;
		pDecoder->m_Precalc.m_pSendTable = pClientSendTable->GetSendTable();
		pClientSendTable->GetSendTable()->m_pPrecalc = &pDecoder->m_Precalc;

		// Initialize array properties.
		SetupArrayProps_R<RecvTable, RecvTable::PropType>( pRecvTable );
	}

	// Read the property list.
	pTable->m_nProps = sendTable->m_nProps;
	pTable->m_pProps = pTable->m_nProps ? new SendProp[ pTable->m_nProps ] : 0;
	pClientSendTable->m_Props.SetSize( pTable->m_nProps );

	for ( int iProp=0; iProp < pTable->m_nProps; iProp++ )
	{
		CClientSendProp *pClientProp = &pClientSendTable->m_Props[iProp];
		SendProp *pProp = &pTable->m_pProps[iProp];
		const SendProp *pSendTableProp = &sendTable->m_pProps[ iProp ];

		pProp->m_Type = (SendPropType)pSendTableProp->m_Type;
		pProp->m_pVarName = COM_StringCopy( pSendTableProp->GetName() );
		pProp->SetFlags( pSendTableProp->GetFlags() );

		if ( pProp->m_Type == DPT_DataTable )
		{
			char *pDTName = pSendTableProp->m_pExcludeDTName; // HACK

			if ( pSendTableProp->GetDataTable() )
				pDTName = pSendTableProp->GetDataTable()->m_pNetTableName;

			Assert( pDTName && Q_strlen(pDTName) > 0 );

			pClientProp->SetTableName( COM_StringCopy( pDTName ) );
			
			// Normally we wouldn't care about this but we need to compare it against 
			// proxies in the server DLL in SendTable_BuildHierarchy.
			pProp->SetDataTableProxyFn( pSendTableProp->GetDataTableProxyFn() );
			pProp->SetOffset( pSendTableProp->GetOffset() );
		}
		else
		{
			if ( pProp->IsExcludeProp() )
			{
				pProp->m_pExcludeDTName = COM_StringCopy( pSendTableProp->GetExcludeDTName() );
			}
			else if ( pProp->GetType() == DPT_Array )
			{
				pProp->SetNumElements( pSendTableProp->GetNumElements() );
			}
			else
			{
				pProp->m_fLowValue = pSendTableProp->m_fLowValue;
				pProp->m_fHighValue = pSendTableProp->m_fHighValue;
				pProp->m_nBits = pSendTableProp->m_nBits;
			}
		}
	}

	return true;
}