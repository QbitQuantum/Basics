dx11ShaderProgram::dx11ShaderProgram(const char *vshader, const char *pshader,int flags,
		const ConstantDesc *uniforms, const DataDesc *attributes) {
	bool fromCode=(flags&ShaderProgram::Flag_FromCode);
	long VSLen, PSLen;
	void *VSFile = fromCode?NULL:LoadShaderFile(vshader, "cso", &VSLen);
	if (!VSFile) {
		void *src = fromCode?(void *)vshader:LoadShaderFile(vshader, "hlsl", &VSLen);
		ID3DBlob *pCode;
		ID3DBlob *pError;
		if (fromCode&&vshader)
			VSLen = strlen(vshader);
		D3DCompile(src, VSLen, vshader, NULL, NULL, "VShader",
			"vs_4_0_level_9_3", D3DCOMPILE_PREFER_FLOW_CONTROL, 0, &pCode, &pError);
		if (src&&(!fromCode))
			free(src);
		if (pError) {
			errorLog.append("VertexShader:\n");
			errorLog.append((char *) pError->GetBufferPointer(),
					pError->GetBufferSize());
			errorLog.append("\n");
			pError->Release();
		}
		if (pCode) {
			VSLen = pCode->GetBufferSize();
			VSFile = malloc(VSLen);
			memcpy(VSFile, pCode->GetBufferPointer(), VSLen);
			pCode->Release();
		}
	}
	void *PSFile = fromCode?NULL:LoadShaderFile(pshader, "cso", &PSLen);
	if (!PSFile) {
		void *src = fromCode?(void *)pshader:LoadShaderFile(pshader, "hlsl", &PSLen);
		ID3DBlob *pCode;
		ID3DBlob *pError;
		if (fromCode&&pshader)
			PSLen = strlen(pshader);
		D3DCompile(src, PSLen, pshader, NULL, NULL, "PShader",
			"ps_4_0_level_9_3", D3DCOMPILE_PREFER_FLOW_CONTROL, 0, &pCode, &pError);
		if (src&&(!fromCode))
			free(src);
		if (pError) {
			errorLog.append("PixelShader:\n");
			errorLog.append((char *) pError->GetBufferPointer(),
					pError->GetBufferSize());
			errorLog.append("\n");
			pError->Release();
		}
		if (pCode) {
			PSLen = pCode->GetBufferSize();
			PSFile = malloc(PSLen);
			memcpy(PSFile, pCode->GetBufferPointer(), PSLen);
			pCode->Release();
		}
	}
	buildShaderProgram(VSFile, VSLen, PSFile, PSLen, flags, uniforms, attributes);
	if (VSFile)
		free(VSFile);
	if (PSFile)
		free(PSFile);
}