void DecoderParseSyntaxTest::TestSpecificBs() {
  int32_t iRet = ERR_NONE;
  m_sDecParam.bParseOnly = true;
  m_sDecParam.eEcActiveIdc = ERROR_CON_DISABLE;
  iRet = m_pDec->Initialize (&m_sDecParam);
  ASSERT_EQ (iRet, ERR_NONE);
  ASSERT_TRUE (ParseBs ("res/jm_1080p_allslice.264", CorrectParseOnly));
  m_pDec->Uninitialize();
}