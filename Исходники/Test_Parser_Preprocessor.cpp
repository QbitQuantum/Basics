	bool TryPreprocess(const char* code)
	{
		m_context.Clear();
		m_diag.ClearItems();
		m_fileCache = RefPtr<CompileUnitFile>::MakeRef();
		m_fileCache->Initialize(LN_LOCALFILE("test.c"));
		m_buffer = ByteBuffer(code);
		m_tokens = m_lex.Tokenize(m_buffer, &m_diag);

		EntityDatabase db;
		ReferenceTracker rt;
		rt.Initialize(&db);
		bool r = m_prepro.BuildPreprocessedTokenList(&m_context, m_fileCache, m_tokens, m_fileCache, &m_additionalIncludePaths, m_definedMacros, &rt, &m_diag) == ResultState::Success;
		return r;
	}