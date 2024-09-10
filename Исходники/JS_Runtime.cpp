CJS_Runtime::CJS_Runtime(CPDFDoc_Environment * pApp) : 
	m_pApp(pApp),
	m_pDocument(NULL),
	m_bBlocking(FALSE),
	m_bRegistered(FALSE),
	m_pFieldEventPath(NULL)
{
	m_pArrayBufferAllocator.reset(new CJS_ArrayBufferAllocator());

	v8::Isolate::CreateParams params;
	params.array_buffer_allocator = m_pArrayBufferAllocator.get();
	m_isolate = v8::Isolate::New(params);

	InitJSObjects();

	CJS_Context * pContext = (CJS_Context*)NewContext();
	JS_InitialRuntime(*this, this, pContext, m_context);
	ReleaseContext(pContext);
}