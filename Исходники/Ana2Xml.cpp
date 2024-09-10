///////////////////////////////////////////////////////////////////////////////
// NAME
//    CAna2Xml::ConvertFile
// DESCRIPTION
//    Parse the sentences found in the given input file, writing the results to
//    the given output file.
// RETURN VALUE
//    S_OK, or an appropriate COM error code
//
STDMETHODIMP CAna2Xml::ConvertFile(BSTR bstrInput, BSTR bstrOutput)
{
  // check for valid input
  if ((bstrInput == NULL) || (bstrOutput == NULL))
	{
	  return E_INVALIDARG;
	}
  // open the files
  HRESULT hr = ConvertBstrToString(bstrInput, CP_ACP,
				   &m_AnaData.pszInputFile);
  if (FAILED(hr))
	{
	  return hr;
	}
  m_AnaData.pInputFP = fopen(m_AnaData.pszInputFile, "r");
  if (m_AnaData.pInputFP == NULL)
	{
	  free(m_AnaData.pszInputFile);
	  return E_FAIL;
	}
  hr = ConvertBstrToString(bstrOutput, CP_ACP, &m_AnaData.pszOutputFile);
  if (FAILED(hr))
	{
	  free(m_AnaData.pszInputFile);
	  fclose(m_AnaData.pInputFP);
	  return hr;
	}
  m_AnaData.pOutputFP = fopen(m_AnaData.pszOutputFile, "w");
  if (m_AnaData.pOutputFP == NULL)
	{
	  free(m_AnaData.pszOutputFile);
	  free(m_AnaData.pszInputFile);
	  fclose(m_AnaData.pInputFP);
	  return E_FAIL;
	}
  if (m_AnaData.pszLogFile != NULL)
	{
	  m_AnaData.pLogFP = fopen(m_AnaData.pszLogFile, "w");
	  if (m_AnaData.pLogFP == NULL)
	{
	  free(m_AnaData.pszOutputFile);
	  free(m_AnaData.pszInputFile);
	  fclose(m_AnaData.pInputFP);
	  fclose(m_AnaData.pOutputFP);
	  return E_FAIL;
	}
	}

				//  allocate space for records
  pRecordBuffer_g	     = (char *)allocMemory( BIG_RECSIZE );
  uiRecordBufferSize_g = BIG_RECSIZE;

  performMapping(&m_AnaData);

  fclose(m_AnaData.pInputFP);
  free((void *)m_AnaData.pszInputFile);

  fclose(m_AnaData.pOutputFP);
  free((void *)m_AnaData.pszOutputFile);

  if (m_AnaData.pLogFP != NULL)
	{
	  fclose(m_AnaData.pLogFP);
	}

  freeMemory(pRecordBuffer_g);
  return S_OK;
}