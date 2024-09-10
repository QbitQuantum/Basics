//
//
//   makes an HRESULT with a code based on the DOM error code
//
HRESULT MakeHRESULT(DOMException& ex)
{
	ICreateErrorInfo* pCErr = NULL;
	HRESULT sc = CreateErrorInfo(&pCErr);
	if(SUCCEEDED(sc)) {
		const XMLCh* msg = ex.msg;
		if(msg == NULL)
		{
			if(ex.code >= DOMException::INDEX_SIZE_ERR &&
				ex.code <= DOMException::VALIDATION_ERR)
			{
				sc = pCErr->SetDescription(Msgs[ex.code]);
			}
			else
			{
				sc = pCErr->SetDescription(Msgs[0]);
			}
		}
		else
		{
			sc = pCErr->SetDescription(SysAllocString(ex.msg));
		}

		IErrorInfo* pErr = NULL;
		sc = pCErr->QueryInterface(IID_IErrorInfo,(void**) &pErr);
		if(SUCCEEDED(sc))
		{
			sc = SetErrorInfo(0,pErr);
			pErr->Release();
		}
		pCErr->Release();
	}
	return 0x80040600 + ex.code;
}