//--------------------------------------------------------------------
// @mfunc COLEDB  
//
// @parm [IN] Test case name
//
//--------------------------------------------------------------------
COLEDB::COLEDB(WCHAR * pwszTestCaseName) : CTestCases(pwszTestCaseName) 
{

	// Init to S_OK and NULL
	m_hr		= S_OK;
	m_pIMalloc	= NULL;
	m_pExtError = NULL;
	m_fLocalize	= FALSE;

	// If we can't get our memory allocator, we're in trouble anyway, so assert
	CoGetMalloc(MEMCTX_TASK, &m_pIMalloc);
	ASSERT(m_pIMalloc);

	//Record if we are called within a TC or standalone object
	m_fInsideTestCase	= TRUE;
	if(pwszTestCaseName == INVALID(WCHAR*))
		m_fInsideTestCase = FALSE;
}