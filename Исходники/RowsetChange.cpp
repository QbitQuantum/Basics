STDMETHODIMP CCUBRIDRowset::Update(HCHAPTER hReserved, DBCOUNTITEM cRows, const HROW rghRows[],
				DBCOUNTITEM *pcRows, HROW **prgRows, DBROWSTATUS **prgRowStatus)
{
	ATLTRACE(atlTraceDBProvider, 2, "CCUBRIDRowset::Update\n");

	ClearError();
	if(m_nStatus==1) return RaiseError(E_UNEXPECTED, 1, __uuidof(IRowsetUpdate), L"This object is in a zombie state");
	CHECK_RESTART(__uuidof(IRowsetUpdate));

	DBCOUNTITEM ulRows = 0; // update할 row 수
	bool bNotIgnore = true; // prgRows, prgRowStatus를 무시할지 여부를 나타냄

	// the following lines are used to fix the two _alloca calls below.  Those calls are risky 
	// because we may be allocating huge amounts of data.  So instead I'll allocate that data on heap.
	// But if you use _alloca you don't have to worry about cleaning this memory.  So we will use these
	// temporary variables to allocate memory on heap.  As soon as we exit the function, the memory will
	// be cleaned up, just as if we were using alloca. So now, instead of calling alloca, I'll alloc
	// memory on heap using the two smnart pointers below, and then assing it to the actual pointers.
	CHeapPtr<HROW> spTempRows;
	CHeapPtr<DBROWSTATUS> spTempRowStatus;

	if(cRows || pcRows)
	{
		if(prgRows) *prgRows = NULL;
		if(prgRowStatus) *prgRowStatus = NULL;		
	}
	else
	{
		bNotIgnore = false;		// Don't do status or row arrays
	}

	// Check to see how many changes we'll undo 
	if(pcRows)
	{
		*pcRows = NULL;
		if(prgRows==NULL) return E_INVALIDARG;
	}

	if(cRows)
	{
		if(rghRows==NULL) return E_INVALIDARG;
		ulRows = cRows;
	}
	else
		ulRows = (DBCOUNTITEM)m_rgRowHandles.GetCount();

	int hConn = GetSessionPtr()->GetConnection();
	UINT uCodepage = GetSessionPtr()->GetCodepage();
	// NULL out pointers
	{
		if(prgRows && ulRows && bNotIgnore)
		{
			// Make a temporary buffer as we may not fill up everything
			// in the case where cRows == 0
			if(cRows)
				*prgRows = (HROW*)CoTaskMemAlloc(ulRows * sizeof(HROW));
			else
			{
				spTempRows.Allocate(ulRows);
				*prgRows = spTempRows;
			}
			if (*prgRows==NULL) return E_OUTOFMEMORY;
		}

		if(prgRowStatus && ulRows && bNotIgnore)
		{
			if(cRows)
				*prgRowStatus = (DBROWSTATUS*)CoTaskMemAlloc(ulRows * sizeof(DBROWSTATUS));
			else
			{
				spTempRowStatus.Allocate(ulRows);
				*prgRowStatus = spTempRowStatus;
			}
			if(*prgRowStatus==NULL)
			{
				if(cRows) CoTaskMemFree(*prgRows);
				*prgRows = NULL;
				return E_OUTOFMEMORY;
			}
		}
	}

	bool bSucceeded = false;
	bool bFailed = false;
	ULONG ulCount = 0; // update된 row 수
	POSITION pos = m_rgRowHandles.GetStartPosition();
	for (ULONG ulRow = 0; ulRow < ulRows; ulRow++)
	{
		ULONG ulCurrentRow = ulCount;
		bool bDupRow = false; // 중복된 row
		ULONG ulAlreadyProcessed = 0; // 중복된 row의 handle의 위치

		HROW hRowUpdate = NULL; // 현재 update할 row의 handle
		{
			if(cRows)
			{	// row handle이 주어졌음
				hRowUpdate = rghRows[ulRow];
				for (ULONG ulCheckDup = 0; ulCheckDup < ulRow; ulCheckDup++)
				{
					if (hRowUpdate==rghRows[ulCheckDup] ||
						IsSameRow(hRowUpdate, rghRows[ulCheckDup]) == S_OK)
					{
						ulAlreadyProcessed = ulCheckDup;
						bDupRow = true;
						break;
					}
				}
			}
			else
			{	// 모든 row에 대해 update
				//ATLASSERT(ulRow < (ULONG)m_rgRowHandles.GetCount()); // delete된 row가 있으면 성립하지 않는다.
				ATLASSERT( pos != NULL );
				MapClass::CPair* pPair = m_rgRowHandles.GetNext(pos);
				ATLASSERT( pPair != NULL );
				hRowUpdate = pPair->m_key;
			}
		}

		if(prgRows && bNotIgnore)
			(*prgRows)[ulCurrentRow] = hRowUpdate;

		if(bDupRow)
		{
			// We've already set the row before, just copy status and
			// continue processing
			if(prgRowStatus && bNotIgnore)
				(*prgRowStatus)[ulCurrentRow] = (*prgRowStatus)[ulAlreadyProcessed];
			ulCount++;
			continue;
		}

		// Fetch the RowClass and determine if it is valid
		CCUBRIDRowsetRow *pRow;
		{
			bool bFound = m_rgRowHandles.Lookup((ULONG)hRowUpdate, pRow);
			if (!bFound || pRow == NULL)
			{
				if (prgRowStatus && bNotIgnore)
					(*prgRowStatus)[ulCurrentRow] = DBROWSTATUS_E_INVALID;
				bFailed = true;
				ulCount++;
				continue;
			}
		}

		// If cRows is zero we'll go through all rows fetched.  We
		// shouldn't increment the attempted count for rows that are
		// not changed
		if (cRows != 0 || (pRow != NULL &&
			pRow->m_status != 0 && pRow->m_status != DBPENDINGSTATUS_UNCHANGED
			&& pRow->m_status != DBPENDINGSTATUS_INVALIDROW))
			ulCount++;
		else
			continue;

		if(cRows==0)
			pRow->AddRefRow();

		switch (pRow->m_status)
		{
		case DBPENDINGSTATUS_INVALIDROW:	// Row is bad or deleted
			{
				if(prgRowStatus && bNotIgnore)
					(*prgRowStatus)[ulCurrentRow] = DBROWSTATUS_E_DELETED;
				bFailed = true;
			}
			break;
		case DBPENDINGSTATUS_UNCHANGED:
		case 0:
			{
				// If the row's status is not changed, then just put S_OK
				// and continue.  The spec says we should not transmit the
				// request to the data source (as nothing would change).
				if(prgRowStatus && bNotIgnore)
					(*prgRowStatus)[ulCurrentRow] = DBROWSTATUS_S_OK;
				bSucceeded = true;
			}
			break;
		default:
			{
				DBORDINAL cCols;
				ATLCOLUMNINFO *pColInfo = GetColumnInfo(this, &cCols);
				HRESULT hr = pRow->WriteData(hConn, uCodepage, GetRequestHandle(), m_strTableName);
				if(FAILED(hr))
				{
					DBROWSTATUS stat = DBROWSTATUS_E_FAIL;
					if(hr==DB_E_INTEGRITYVIOLATION) stat = DBROWSTATUS_E_INTEGRITYVIOLATION;
					if(prgRowStatus && bNotIgnore)
						(*prgRowStatus)[ulCurrentRow] = stat;
					bFailed = true;
				}
				else
				{
					//// m_iRowset을 적당히 조정한다.
					//if(pRow->m_status==DBPENDINGSTATUS_NEW)
					//{
					//	// NEW인 row는 항상 rowset의 뒤에 몰려있다.
					//	// 그 row 중 가장 작은 m_iRowset이 update 된 row의 m_iRowset이 되면 된다.
					//	CCUBRIDRowsetRow::KeyType key = pRow->m_iRowset;
					//	POSITION pos = m_rgRowHandles.GetStartPosition();
					//	while(pos)
					//	{
					//		CCUBRIDRowset::MapClass::CPair *pPair = m_rgRowHandles.GetNext(pos);
					//		ATLASSERT(pPair);
					//		CCUBRIDRowsetRow *pCheckRow = pPair->m_value;
					//		if( pCheckRow && pCheckRow->m_iRowset < key )
					//		{
					//			if(pCheckRow->m_iRowset<pRow->m_iRowset)
					//				pRow->m_iRowset = pCheckRow->m_iRowset;
					//			pCheckRow->m_iRowset++;
					//		}
					//	}

					//	// TODO: 북마크 업데이트가 필요한데 어떻게 해야 할지 모르겠다.

					//	// 새로 추가된 Row의 OID를 읽어들인다.
					//	pRow->ReadData(GetRequestHandle(), true);
					//}

					if(pRow->m_status==DBPENDINGSTATUS_DELETED)
						MakeRowInvalid(this, pRow);
					else
						pRow->m_status = DBPENDINGSTATUS_UNCHANGED;

					if(prgRowStatus && bNotIgnore)
						(*prgRowStatus)[ulCurrentRow] = DBROWSTATUS_S_OK;
					bSucceeded = true;

					// Check if we need to release the row because it's ref was 0
					// See the IRowset::ReleaseRows section in the spec for more
					// information
					if (pRow->m_dwRef == 0)
					{
						pRow->AddRefRow();	// Artifically bump this to remove it
						if( FAILED( RefRows(1, &hRowUpdate, NULL, NULL, false) ) )
							return E_FAIL;
					}
				}
			}
			break;
		}
	}

	// Set the output for rows undone.
	if(pcRows) *pcRows = ulCount;

	if(ulCount==0)
	{
		if(prgRows)
		{
			CoTaskMemFree(*prgRows);
			*prgRows = NULL;
		}

		if(prgRowStatus)
		{
			CoTaskMemFree(*prgRowStatus);
			*prgRowStatus = NULL;
		}
	}
	else if(cRows==0)
	{
		// In the case where cRows == 0, we need to allocate the final
		// array of data.
		if(prgRows && bNotIgnore)
		{
			HROW *prgRowsTemp = (HROW *)CoTaskMemAlloc(ulCount*sizeof(HROW));
			if(prgRowsTemp==NULL) return E_OUTOFMEMORY;
			memcpy(prgRowsTemp, *prgRows, ulCount*sizeof(HROW));
			*prgRows = prgRowsTemp;
		}

		if(prgRowStatus && bNotIgnore)
		{
			DBROWSTATUS *prgRowStatusTemp = (DBROWSTATUS *)CoTaskMemAlloc(ulCount*sizeof(DBROWSTATUS));
			if(prgRowStatusTemp==NULL)
			{
				CoTaskMemFree(*prgRows);
				*prgRows = NULL;
				return E_OUTOFMEMORY;
			}
			memcpy(prgRowStatusTemp, *prgRowStatus, ulCount*sizeof(DBROWSTATUS));
			*prgRowStatus = prgRowStatusTemp;
		}
	}

	DoCommit(this); // commit

	// Send the return value
	if(!bFailed)
		return S_OK;
	else
	{
		return bSucceeded ? DB_S_ERRORSOCCURRED : DB_E_ERRORSOCCURRED;
	}
}