void GLCCompiler::ParseTechnique() {
	std::string namestr;

	Expect(kTokenIdent);
	const char *name = mLexer.GetToken();
	namestr.assign(name, name + mLexer.GetTokenLen());

	std::pair<Techniques::iterator, bool> result(mTechniques.insert(Techniques::value_type(namestr, Technique())));

	if (!result.second)
		mLexer.ThrowError("Technique '%s' already defined", namestr.c_str());

	Technique& tech = result.first->second;

	Expect('{');

	Expect(kTokenIdent);
	if (!mLexer.IsKeyword(sKeywordPass))
		Huh("pass declaration", kTokenIdent);

	Expect('{');

	for(;;) {
		int tok = mLexer.Token();

		if (tok == '\n')
			continue;
		else if (tok == '}')
			break;
		else if (tok == kTokenIdent) {
			if (mLexer.IsKeyword(sKeywordFragmentShader)) {
				Expect('=');
				Expect(kTokenIdent);
				if (mLexer.IsKeyword(sKeywordFragment_Shader)) {
					tok = mLexer.Token();

					if (tok != kTokenIdent)
						Huh("fragment shader profile", tok);

					enum {
						kProfileNVRC,
						kProfileNVRC2,
						kProfileATIFS,
						kProfileARBFS
					} profile;

					if (mLexer.IsKeyword(sKeywordNV_Register_Combiners))
						profile = kProfileNVRC;
					else if (mLexer.IsKeyword(sKeywordNV_Register_Combiners2))
						profile = kProfileNVRC2;
					else if (mLexer.IsKeyword(sKeywordATI_Fragment_Shader))
						profile = kProfileATIFS;
					else if (mLexer.IsKeyword(sKeywordARB_Fragment_Shader))
						profile = kProfileARBFS;
					else
						mLexer.ThrowError("Unknown shader profile '%.*s'", mLexer.GetTokenLen(), mLexer.GetToken());

					vdautoptr<IGLCFragmentShader> fshader;
					if (profile == kProfileARBFS) {
						Expect('{');
						mLexer.EnableForeignCode(true);
						Expect(kTokenForeignCode);
						mLexer.EnableForeignCode(false);
						fshader = new ARBFragmentShader(mLexer.GetToken(), mLexer.GetTokenLen());
						Expect('}');
					} else {
						GLCFragmentShader shader;
						ParseFragmentShader(shader);
						
						switch(profile) {
							case kProfileNVRC:
								fshader = CompileFragmentShaderNVRegisterCombiners(mLexer, shader, false);
								break;
							case kProfileNVRC2:
								fshader = CompileFragmentShaderNVRegisterCombiners(mLexer, shader, true);
								break;
							case kProfileATIFS:
								fshader = CompileFragmentShaderATIFragmentShader(mLexer, shader);
								break;
						}
					}

					tech.mpFragmentShader = fshader;

					mFragmentShaders.push_back(fshader.release());
				}
				Expect(';');
				continue;
			}
		}

		Huh("technique parameter", tok);
	}

	Expect('}');
}