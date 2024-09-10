	STDMETHOD(Assemble)(VARIANT varInput, IStream **ppOutput)
	{
		mode = m_dwOptions;

		if (V_VT(&varInput) == VT_BSTR)
		{
			mode |= MODE_NORMAL | MODE_COMMANDLINE;
			mode &= ~MODE_LIST;

			if (m_fFirstAssembly)
			{
				init_storage();
			}

			CW2CT szInput(V_BSTR(&varInput));
			input_contents = strdup(szInput);

			curr_input_file = strdup("COM Interface");
		}
		else
		{
			mode &= ~MODE_COMMANDLINE;
			mode |= MODE_NORMAL;

			curr_input_file = strdup(m_bstrInputFile);
			output_filename = strdup(m_bstrOutputFile);

			if (!m_fFirstAssembly)
			{
				free_storage();
			}

			init_storage();
		}

		// Set up the include directories
		CComPtr<IUnknown> pEnumUnk;
		HRESULT hr = m_pDirectories->get__NewEnum(&pEnumUnk);

		CComQIPtr<IEnumVARIANT> pEnum = pEnumUnk;

		CComVariant varItem;
		ULONG ulFetched;

		while (pEnum->Next(1, &varItem, &ulFetched) == S_OK)
		{
			include_dirs = list_prepend(include_dirs, (char *) strdup(_bstr_t(V_BSTR(&varItem))));
		}

		AddDefines();

		int error = run_assembly();

		list_free(include_dirs, true, NULL);
		include_dirs = NULL;

		ClearSPASMErrorSessions();

		long assembled_size = out_ptr - output_contents;

		HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, assembled_size);
		unsigned char *streambuf = (unsigned char *)GlobalLock(hGlobal);
		memcpy(streambuf, output_contents, assembled_size);
		GlobalUnlock(hGlobal);

		CComPtr<IStream> pStream;
		hr = CreateStreamOnHGlobal(hGlobal, TRUE, &pStream);
		ULARGE_INTEGER ul;
		ul.QuadPart = assembled_size;
		pStream->SetSize(ul);

		m_fFirstAssembly = FALSE;
		if (output_filename != NULL)
		{
			free(output_filename);
			output_filename = NULL;
		}
		if (curr_input_file)
		{
			free(curr_input_file);
			curr_input_file = NULL;
		}

		if (mode & MODE_COMMANDLINE)
		{
			free(input_contents);
			input_contents = NULL;
		}

		m_fLabelsAreValid = FALSE;
		return pStream->QueryInterface(ppOutput);
	}