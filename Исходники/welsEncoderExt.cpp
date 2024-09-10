int CWelsH264SVCEncoder::InitializeExt (const SEncParamExt* argv) {
  if (m_pWelsTrace == NULL) {
    return cmMallocMemeError;
  }

  WelsLog (&m_pWelsTrace->m_sLogCtx, WELS_LOG_INFO, "CWelsH264SVCEncoder::InitEncoder(), openh264 codec version = %s",
           VERSION_NUMBER);

  if (NULL == argv) {
    WelsLog (&m_pWelsTrace->m_sLogCtx, WELS_LOG_ERROR, "CWelsH264SVCEncoder::InitializeExt(), invalid argv= 0x%p",
             argv);
    return cmInitParaError;
  }

  SWelsSvcCodingParam	sConfig;
  // Convert SEncParamExt into WelsSVCParamConfig here..
  if (sConfig.ParamTranscode (*argv)) {
    WelsLog (&m_pWelsTrace->m_sLogCtx, WELS_LOG_ERROR,
             "CWelsH264SVCEncoder::InitializeExt(), parameter_translation failed.");
    TraceParamInfo (&sConfig);
    Uninitialize();
    return cmInitParaError;
  }

  return InitializeInternal (&sConfig);
}