//Since we're precompiling the shaders, we dont need all the extra parameters
//Assume this is a function within the renderer thus we have access to private render members
Shader* CreateShader(
	const std::string& name,
	const std::string& vsFile,
	const std::string& psFile,
	const std::string& gsFile = "")
{
	Shader newShader = new Shader(name);
	ID3D11ShaderReflection *vsReflect(nullptr);
	ID3D11ShaderReflection *psReflect(nullptr);
	ID3D11ShaderReflection *gsReflect(nullptr);

	if(!vsFile.empty()) {
		auto vsFileRes = new WhaleFile(vsFile);
		if(!vsFileRes) {
			log_sxerror("Shader", "Error opening VS file %s. Cannot continue", vsFile.c_str());
			delete newShader;
			return nullptr;
		}
		auto vsFilePtr = vsFileRes->GetMem();
		HRESULT result = 
			device->CreateVertexShader(vsFilePtr, vsFileRes.Size(), NULL, &newShader->vertexShader);
		if(FAILED(result)) {
			log_sxerror("Shader", "Could not create Vertex shader from %s. Cannot continue!", vsFile.c_str());
			//Clean up after ourselves before returning
			delete vsFileRes;
			delete newShader;
			return nullptr;
		}
		//Grab the input signature from the vertex shader
		result = D3DGetInputSignatureBlob(vsFilePtr, vsFileRes.Size(), &newShader->inputSignature);	
		if(FAILED(result)) {
			log_sxerror("Shader", "Could not get Input signature from %s. Cannot continue!", vsFile.c_str());
			delete vsFileRes;
			delete newShader;
			return nullptr;
		}
		result = D3DReflect(vsFilePtr, vsFileRes.Size(), IID_ID3D11ShaderReflection, (void **)&vsReflect);
		if(FAILED(result)) {
			log_sxerror("Shader", "Could not get Reflection Interface from %s. Cannot continue!", vsFile.c_str());
			delete vsFileRes;
			delete newShader;
			return nullptr;
		}
		delete vsFileRes;
	}
	if(!psFile.empty()) {
		auto psFileRes = new WhaleFile(psFile);
		if(!psFileRes) {
			log_sxerror("Shader", "Error opening PS file %s. Cannot continue!", psFile.c_str());
			delete newShader;
			SAFE_RELEASE(vsReflect);
			return nullptr;
		}
		auto psFilePtr = psFileRes->GetMem();
		HRESULT result =
			device->CreatePixelShader(psFilePtr, psFileRes.Size(), NULL, &newShader->pixelShader);
		if(FAILED(result)) {
			log_sxerror("Shader", "Could not create Pixel shader from %s. Cannot continue!", psFile.c_str());
			delete psFileRes;
			SAFE_RELEASE(vsReflect);
			delete newShader;
			return nullptr;
		}
		result = D3DReflect(psFilePtr, psFileRes.Size(), IID_ID3D11ShaderReflection, (void **)&psReflect);
		if(FAILED(result)) {
			log_sxerror("Shader", "Could not get Reflection Interface from %s. Cannot continue!", psFile.c_str());
			delete psFileRes;
			SAFE_RELEASE(vsReflect);
			delete newShader;
			return nullptr;
		}
		delete psFileRes;
	}
	if(!gsFile.empty()) {
		auto gsFileRes = new WhaleFile(gsFile);
		if(!gsFileRes) {
			log_sxerror("Shader", "Error opening PS file %s. Cannot continue!", gsFile.c_str());
			delete newShader;
			SAFE_RELEASE(vsReflect);
			return nullptr;
		}
		auto gsFilePtr = gsFileRes->GetMem();
		HRESULT result =
			device->CreatePixelShader(gsFilePtr, gsFileRes.Size(), NULL, &newShader->geometryShader);
		if(FAILED(result)) {
			log_sxerror("Shader", "Could not create Pixel shader from %s. Cannot continue!", gsFile.c_str());
			delete gsFileRes;
			SAFE_RELEASE(vsReflect);
			SAFE_RELEASE(psReflect);
			delete newShader;
			return nullptr;
		}
		result = D3DReflect(gsFilePtr, gsFileRes.Size(), IID_ID3D11ShaderReflection, (void **)&gsReflect);
		if(FAILED(result)) {
			log_sxerror("Shader", "Could not get Reflection Interface from %s. Cannot continue!", gsFile.c_str());
			delete gsFileRes;
			SAFE_RELEASE(psReflect);
			SAFE_RELEASE(vsReflect);
			delete newShader;
			return nullptr;
		}
		delete gsFileRes;
	}
	bool res = GenerateShaderConstants(newShader, vsReflect, psReflect, gsReflect);
	if(!res) {
		log_sxerror("Shader", "Error Generating shader constants for shader %s.", name.c_str());
		SAFE_RELEASE(vsReflect);
		SAFE_RELEASE(psReflect);
		SAFE_RELEASE(gsReflect);
		delete newShader;
		return nullptr;
	}
	res = GenerateShaderSamplers(newShader, vsReflect, psReflect, gsReflect);
	if(!res) {
		log_sxerror("Shader", "Error Generating shader samplers for shader %s.", name.c_str());
		SAFE_RELEASE(vsReflect);
		SAFE_RELEASE(psReflect);
		SAFE_RELEASE(gsReflect);
		delete newShader;
		return nullptr;
	}
	res = ValidateShader(newShader, vsReflect, psReflect, gsReflect);
	if(!res) {
		log_sxerror("Shader", "Error validating shader %s", name.c_str());
		delete newShader;
		newShader = nullptr;	
	}
	SAFE_RELEASE(vsReflect);
	SAFE_RELEASE(psReflect);
	SAFE_RELEASE(gsReflect);
	return newShader;
}