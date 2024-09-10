bool COpenGL::SetShadersGLSL_OLD(const TCHAR *glslFileName)
{
	char *fragment = NULL, *vertex = NULL;
	IXMLDOMDocument * pXMLDoc = NULL;
	IXMLDOMElement * pXDE = NULL;
	IXMLDOMNode * pXDN = NULL;
	HRESULT hr;
	BSTR queryString, nodeContent;

	TCHAR errorMsg[MAX_PATH + 50];

	if (fragmentShader) {
		glDetachShader(shaderProgram, fragmentShader);
		glDeleteShader(fragmentShader);
		fragmentShader = 0;
	}
	if (vertexShader) {
		glDetachShader(shaderProgram, vertexShader);
		glDeleteShader(vertexShader);
		vertexShader = 0;
	}
	if (shaderProgram) {
		glUseProgram(0);
		glDeleteProgram(shaderProgram);
		shaderProgram = 0;
	}

	if (glslFileName == NULL || *glslFileName == TEXT('\0'))
		return true;

	if (!LoadShaderFunctions()) {
		MessageBox(NULL, TEXT("Unable to load OpenGL shader functions"), TEXT("Shader Loading Error"),
			MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	hr = CoCreateInstance(CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pXMLDoc));

	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("Error creating XML Parser"), TEXT("Shader Loading Error"),
			MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	VARIANT fileName;
	VARIANT_BOOL ret;
	fileName.vt = VT_BSTR;
#ifdef UNICODE
	fileName.bstrVal = SysAllocString(glslFileName);
#else
	wchar_t tempfilename[MAX_PATH];
	MultiByteToWideChar(CP_UTF8, 0, glslFileName, -1, tempfilename, MAX_PATH);
	fileName.bstrVal = SysAllocString(tempfilename);
#endif
	hr = pXMLDoc->load(fileName, &ret);
	SysFreeString(fileName.bstrVal);

	if (FAILED(hr) || hr == S_FALSE) {
		_stprintf(errorMsg, TEXT("Error loading GLSL shader file:\n%s"), glslFileName);
		MessageBox(NULL, errorMsg, TEXT("Shader Loading Error"), MB_OK | MB_ICONEXCLAMATION);
		pXMLDoc->Release();
		return false;
	}

	VARIANT attributeValue;
	BSTR attributeName;

	hr = pXMLDoc->get_documentElement(&pXDE);
	if (FAILED(hr) || hr == S_FALSE) {
		_stprintf(errorMsg, TEXT("Error loading root element from file:\n%s"), glslFileName);
		MessageBox(NULL, errorMsg, TEXT("Shader Loading Error"), MB_OK | MB_ICONEXCLAMATION);
		pXMLDoc->Release();
		return false;
	}

	attributeName = SysAllocString(L"language");
	pXDE->getAttribute(attributeName, &attributeValue);
	SysFreeString(attributeName);
	pXDE->Release();

	if (attributeValue.vt != VT_BSTR || lstrcmpiW(attributeValue.bstrVal, L"glsl")) {
		_stprintf(errorMsg, TEXT("Shader language is <%s>, expected <GLSL> in file:\n%s"), attributeValue.bstrVal, glslFileName);
		MessageBox(NULL, errorMsg, TEXT("Shader Loading Error"), MB_OK | MB_ICONEXCLAMATION);
		if (attributeValue.vt == VT_BSTR) SysFreeString(attributeValue.bstrVal);
		pXMLDoc->Release();
		return false;
	}
	if (attributeValue.vt == VT_BSTR) SysFreeString(attributeValue.bstrVal);

	queryString = SysAllocString(L"/shader/fragment");
	hr = pXMLDoc->selectSingleNode(queryString, &pXDN);
	SysFreeString(queryString);

	if (hr == S_OK) {
		hr = pXDN->get_text(&nodeContent);
		if (hr == S_OK) {
			int requiredChars = WideCharToMultiByte(CP_ACP, 0, nodeContent, -1, fragment, 0, NULL, NULL);
			fragment = new char[requiredChars];
			WideCharToMultiByte(CP_UTF8, 0, nodeContent, -1, fragment, requiredChars, NULL, NULL);
		}
		SysFreeString(nodeContent);
		pXDN->Release();
		pXDN = NULL;
	}

	queryString = SysAllocString(L"/shader/vertex");
	hr = pXMLDoc->selectSingleNode(queryString, &pXDN);
	SysFreeString(queryString);

	if (hr == S_OK) {
		hr = pXDN->get_text(&nodeContent);
		if (hr == S_OK) {
			int requiredChars = WideCharToMultiByte(CP_ACP, 0, nodeContent, -1, vertex, 0, NULL, NULL);
			vertex = new char[requiredChars];
			WideCharToMultiByte(CP_UTF8, 0, nodeContent, -1, vertex, requiredChars, NULL, NULL);
		}
		SysFreeString(nodeContent);
		pXDN->Release();
		pXDN = NULL;
	}

	pXMLDoc->Release();

	if (!fragment && !vertex) {
		_stprintf(errorMsg, TEXT("No vertex or fragment program in file:\n%s"), glslFileName);
		MessageBox(NULL, errorMsg, TEXT("Shader Loading Error"), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	shaderProgram = glCreateProgram();
	if (vertex) {
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, (const GLchar **)&vertex, NULL);
		glCompileShader(vertexShader);
		glAttachShader(shaderProgram, vertexShader);
		delete[] vertex;
	}
	if (fragment) {
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, (const GLchar **)&fragment, NULL);
		glCompileShader(fragmentShader);
		glAttachShader(shaderProgram, fragmentShader);
		delete[] fragment;
	}

	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	shader_type = OGL_SHADER_GLSL_OLD;

	return true;
}