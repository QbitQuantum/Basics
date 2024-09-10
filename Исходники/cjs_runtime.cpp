CJS_Runtime::CJS_Runtime(CPDFSDK_FormFillEnvironment* pFormFillEnv)
    : m_pFormFillEnv(pFormFillEnv),
      m_bBlocking(false),
      m_isolateManaged(false) {
  v8::Isolate* pIsolate = nullptr;

  IPDF_JSPLATFORM* pPlatform = m_pFormFillEnv->GetFormFillInfo()->m_pJsPlatform;
  if (pPlatform->version <= 2) {
    unsigned int embedderDataSlot = 0;
    v8::Isolate* pExternalIsolate = nullptr;
    if (pPlatform->version == 2) {
      pExternalIsolate = reinterpret_cast<v8::Isolate*>(pPlatform->m_isolate);
      embedderDataSlot = pPlatform->m_v8EmbedderSlot;
    }
    FXJS_Initialize(embedderDataSlot, pExternalIsolate);
  }
  m_isolateManaged = FXJS_GetIsolate(&pIsolate);
  SetIsolate(pIsolate);

#ifdef PDF_ENABLE_XFA
  v8::Isolate::Scope isolate_scope(pIsolate);
  v8::HandleScope handle_scope(pIsolate);
#endif

  if (m_isolateManaged || FXJS_GlobalIsolateRefCount() == 0)
    DefineJSObjects();

  CJS_Context* pContext = (CJS_Context*)NewContext();
  InitializeEngine();
  ReleaseContext(pContext);

  SetFormFillEnvToDocument();
}