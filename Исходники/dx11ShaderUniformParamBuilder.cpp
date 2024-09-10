// Get semantic string back from enum:
MString& CUniformParameterBuilder::getLightParameterSemantic(int lightParameterType) {

	if (lightParameterType < 0 || lightParameterType >= eLastParameterType)
		lightParameterType = eUndefined;

	static MStringArray semanticNames;

	if (!semanticNames.length()) {
		semanticNames.append(dx11ShaderSemantic::kUndefined);
		semanticNames.append(dx11ShaderSemantic::kPosition);
		semanticNames.append(dx11ShaderSemantic::kDirection);
		semanticNames.append(dx11ShaderSemantic::kLightColor);
		semanticNames.append(dx11ShaderSemantic::kLightSpecularColor);
		semanticNames.append(dx11ShaderSemantic::kLightAmbientColor);
		semanticNames.append(dx11ShaderSemantic::kLightDiffuseColor);
		semanticNames.append(dx11ShaderSemantic::kLightRange);          // Not recognized!
		semanticNames.append(dx11ShaderSemantic::kFalloff);
		semanticNames.append(dx11ShaderSemantic::kLightAttenuation0);   // Not recognized!
		semanticNames.append(dx11ShaderSemantic::kLightAttenuation1);   // Not recognized!
		semanticNames.append(dx11ShaderSemantic::kLightAttenuation2);   // Not recognized!
		semanticNames.append(dx11ShaderSemantic::kLightTheta);   // Not recognized!
		semanticNames.append(dx11ShaderSemantic::kLightPhi);   // Not recognized!
		semanticNames.append(dx11ShaderSemantic::kShadowMap);
		semanticNames.append(dx11ShaderSemantic::kShadowMapBias);
		semanticNames.append(dx11ShaderSemantic::kShadowColor);
		semanticNames.append(dx11ShaderSemantic::kShadowMapMatrix);
		semanticNames.append(dx11ShaderSemantic::kShadowFlag);
		semanticNames.append(dx11ShaderSemantic::kLightIntensity);
		semanticNames.append(dx11ShaderSemantic::kHotspot);
		semanticNames.append(dx11ShaderSemantic::kLightEnable);
		semanticNames.append(dx11ShaderSemantic::kLightType);
		semanticNames.append(dx11ShaderSemantic::kDecayRate);
		semanticNames.append(dx11ShaderSemantic::kAreaPosition0);
		semanticNames.append(dx11ShaderSemantic::kAreaPosition1);
		semanticNames.append(dx11ShaderSemantic::kAreaPosition2);
		semanticNames.append(dx11ShaderSemantic::kAreaPosition3);
	}
	return semanticNames[lightParameterType];
}