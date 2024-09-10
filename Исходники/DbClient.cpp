/*****************************************************************************
 * データベースに接続します。
 *****************************************************************************/
int DbSqlCeClient::open()
{
	HRESULT hr;
	ULONG  count = 0;
	ULONG i, j;

	IDBProperties *pProp = NULL;
	// CompactのConnectionStringの指定可能なオプション数は、3が最大なので固定で確保します。
	DBPROPSET arInitPropSet[PROPSET_MAX] = {0};
	DBPROP    arProp1[4]= {0}, arProp2[10] = {0};

	//
	try{
		// インタフェースの生成
		hr = CoCreateInstance( m_sqlceVerGUID, NULL, CLSCTX_INPROC_SERVER,
				IID_IDBInitialize, (LPVOID*)&m_pDBinit);
		if( FAILED( hr ) )		throw(1);

		// プロパティの取得
		hr = m_pDBinit->QueryInterface(IID_IDBProperties, (void **)&pProp);
		if( FAILED( hr ) )		throw(2);

		// 最大数とDBPROPの配列を設定。
		arInitPropSet[0].cProperties = ARRAYSIZE(arProp1);
		arInitPropSet[0].rgProperties = arProp1;
		arInitPropSet[0].guidPropertySet = DBPROPSET_DBINIT;
		for( i = 0; i < ARRAYSIZE(arProp1); i ++ ){
			VariantInit( &(arProp1[i].vValue) );
		}

		arInitPropSet[1].cProperties = ARRAYSIZE(arProp2);
		arInitPropSet[1].rgProperties = arProp2;
		arInitPropSet[1].guidPropertySet = DBPROPSET_SSCE_DBINIT;
		for( i = 0; i < ARRAYSIZE(arProp2); i ++ ){
			VariantInit( &(arProp2[i].vValue) );
		}

		// プロパティの作成
		count = create_open_prop( arInitPropSet, ARRAYSIZE(arInitPropSet) );
		if( 0 == count ){
			throw(3);
		}
		else{
			hr = pProp->SetProperties( count, arInitPropSet );
			// プロパティのメモリ開放
			for( i = 0; i < count; i ++ ){
				for( j = 0; j < arInitPropSet[i].cProperties; j ++ ){
					if( VT_BSTR == arInitPropSet[i].rgProperties[j].vValue.vt ){
						SysFreeString( arInitPropSet[i].rgProperties[j].vValue.bstrVal );
					}
				}
			}
			pProp->Release();

			if( FAILED( hr ) )		throw(4);
		}

		// データベースに接続します。
		hr = m_pDBinit->Initialize();
        if( FAILED( hr ) ){
            throw(5);
        }

		m_IsOpened = true;

		// 次に必要なインタフェースを取得します。
		hr = m_pDBinit->QueryInterface( IID_IDBCreateSession, (void**)&m_pSession);
		if( FAILED( hr ) )		throw(6);

		//
		hr = m_pSession->CreateSession( NULL, IID_IDBCreateCommand,(IUnknown**) &m_pCrtCmd);
		if( FAILED( hr ) )		throw(7);

		//
		hr = m_pCrtCmd->CreateCommand( NULL, IID_ICommandText,(IUnknown**) &m_pCmdtext );
		if( FAILED( hr ) )		throw(8);
	}
	catch(const int err){
		if( m_IsOpened ){
			m_pDBinit->Uninitialize();
            m_IsOpened = false;
		}
		if( m_pCmdtext ){
			m_pCmdtext->Release();
			m_pCmdtext =NULL;
		}
		if( m_pCrtCmd ){
			m_pCrtCmd->Release();
			m_pCrtCmd = NULL;
		}
		if( m_pSession ){
			m_pSession->Release();
			m_pSession = NULL;
		}
		if( pProp ){
			pProp->Release();
			pProp = NULL;
		}
		if( m_pDBinit ){
			m_pDBinit->Release();
			m_pDBinit = NULL;
		}

		return err;
	}

	return 0;
}