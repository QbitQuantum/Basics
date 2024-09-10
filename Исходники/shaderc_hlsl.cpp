	static bool compile(bx::CommandLine& _cmdLine, uint32_t _version, const std::string& _code, bx::WriterI* _writer, bool _firstPass)
	{
		const char* profile = _cmdLine.findOption('p', "profile");
		if (NULL == profile)
		{
			fprintf(stderr, "Error: Shader profile must be specified.\n");
			return false;
		}

		s_compiler = load();

		bool result = false;
		bool debug = _cmdLine.hasArg('\0', "debug");

		uint32_t flags = D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY;
		flags |= debug ? D3DCOMPILE_DEBUG : 0;
		flags |= _cmdLine.hasArg('\0', "avoid-flow-control") ? D3DCOMPILE_AVOID_FLOW_CONTROL : 0;
		flags |= _cmdLine.hasArg('\0', "no-preshader") ? D3DCOMPILE_NO_PRESHADER : 0;
		flags |= _cmdLine.hasArg('\0', "partial-precision") ? D3DCOMPILE_PARTIAL_PRECISION : 0;
		flags |= _cmdLine.hasArg('\0', "prefer-flow-control") ? D3DCOMPILE_PREFER_FLOW_CONTROL : 0;
		flags |= _cmdLine.hasArg('\0', "backwards-compatibility") ? D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY : 0;

		bool werror = _cmdLine.hasArg('\0', "Werror");

		if (werror)
		{
			flags |= D3DCOMPILE_WARNINGS_ARE_ERRORS;
		}

		uint32_t optimization = 3;
		if (_cmdLine.hasArg(optimization, 'O') )
		{
			optimization = bx::uint32_min(optimization, BX_COUNTOF(s_optimizationLevelD3D11) - 1);
			flags |= s_optimizationLevelD3D11[optimization];
		}
		else
		{
			flags |= D3DCOMPILE_SKIP_OPTIMIZATION;
		}

		BX_TRACE("Profile: %s", profile);
		BX_TRACE("Flags: 0x%08x", flags);

		ID3DBlob* code;
		ID3DBlob* errorMsg;

		// Output preprocessed shader so that HLSL can be debugged via GPA
		// or PIX. Compiling through memory won't embed preprocessed shader
		// file path.
		std::string hlslfp;

		if (debug)
		{
			hlslfp = _cmdLine.findOption('o');
			hlslfp += ".hlsl";
			writeFile(hlslfp.c_str(), _code.c_str(), (int32_t)_code.size() );
		}

		HRESULT hr = D3DCompile(_code.c_str()
			, _code.size()
			, hlslfp.c_str()
			, NULL
			, NULL
			, "main"
			, profile
			, flags
			, 0
			, &code
			, &errorMsg
			);
		if (FAILED(hr)
		|| (werror && NULL != errorMsg) )
		{
			const char* log = (char*)errorMsg->GetBufferPointer();

			int32_t line   = 0;
			int32_t column = 0;
			int32_t start  = 0;
			int32_t end    = INT32_MAX;

			bool found = false
				|| 2 == sscanf(log, "(%u,%u):", &line, &column)
				|| 2 == sscanf(log, " :%u:%u: ", &line, &column)
				;

			if (found
			&&  0 != line)
			{
				start = bx::uint32_imax(1, line - 10);
				end   = start + 20;
			}

			printCode(_code.c_str(), line, start, end, column);
			fprintf(stderr, "Error: D3DCompile failed 0x%08x %s\n", (uint32_t)hr, log);
			errorMsg->Release();
			return false;
		}

		UniformArray uniforms;
		uint8_t numAttrs = 0;
		uint16_t attrs[bgfx::Attrib::Count];
		uint16_t size = 0;

		if (_version == 9)
		{
			if (!getReflectionDataD3D9(code, uniforms) )
			{
				fprintf(stderr, "Error: Unable to get D3D9 reflection data.\n");
				goto error;
			}
		}
		else
		{
			UniformNameList unusedUniforms;
			if (!getReflectionDataD3D11(code, profile[0] == 'v', uniforms, numAttrs, attrs, size, unusedUniforms) )
			{
				fprintf(stderr, "Error: Unable to get D3D11 reflection data.\n");
				goto error;
			}

			if (_firstPass
			&&  unusedUniforms.size() > 0)
			{
				const size_t strLength = strlen("uniform");

				// first time through, we just find unused uniforms and get rid of them
				std::string output;
				LineReader reader(_code.c_str() );
				while (!reader.isEof() )
				{
					std::string line = reader.getLine();
					for (UniformNameList::iterator it = unusedUniforms.begin(), itEnd = unusedUniforms.end(); it != itEnd; ++it)
					{
						size_t index = line.find("uniform ");
						if (index == std::string::npos)
						{
							continue;
						}

						// matching lines like:  uniform u_name;
						// we want to replace "uniform" with "static" so that it's no longer
						// included in the uniform blob that the application must upload
						// we can't just remove them, because unused functions might still reference
						// them and cause a compile error when they're gone
						if (!!bx::findIdentifierMatch(line.c_str(), it->c_str() ) )
						{
							line = line.replace(index, strLength, "static");
							unusedUniforms.erase(it);
							break;
						}
					}

					output += line;
				}

				// recompile with the unused uniforms converted to statics
				return compile(_cmdLine, _version, output.c_str(), _writer, false);
			}
		}

		{
			uint16_t count = (uint16_t)uniforms.size();
			bx::write(_writer, count);

			uint32_t fragmentBit = profile[0] == 'p' ? BGFX_UNIFORM_FRAGMENTBIT : 0;
			for (UniformArray::const_iterator it = uniforms.begin(); it != uniforms.end(); ++it)
			{
				const Uniform& un = *it;
				uint8_t nameSize = (uint8_t)un.name.size();
				bx::write(_writer, nameSize);
				bx::write(_writer, un.name.c_str(), nameSize);
				uint8_t type = uint8_t(un.type | fragmentBit);
				bx::write(_writer, type);
				bx::write(_writer, un.num);
				bx::write(_writer, un.regIndex);
				bx::write(_writer, un.regCount);

				BX_TRACE("%s, %s, %d, %d, %d"
					, un.name.c_str()
					, getUniformTypeName(un.type)
					, un.num
					, un.regIndex
					, un.regCount
					);
			}
		}

		{
			ID3DBlob* stripped;
			hr = D3DStripShader(code->GetBufferPointer()
				, code->GetBufferSize()
				, D3DCOMPILER_STRIP_REFLECTION_DATA
				| D3DCOMPILER_STRIP_TEST_BLOBS
				, &stripped
				);

			if (SUCCEEDED(hr) )
			{
				code->Release();
				code = stripped;
			}
		}

		{
			uint16_t shaderSize = (uint16_t)code->GetBufferSize();
			bx::write(_writer, shaderSize);
			bx::write(_writer, code->GetBufferPointer(), shaderSize);
			uint8_t nul = 0;
			bx::write(_writer, nul);
		}

		if (_version > 9)
		{
			bx::write(_writer, numAttrs);
			bx::write(_writer, attrs, numAttrs*sizeof(uint16_t) );

			bx::write(_writer, size);
		}

		if (_cmdLine.hasArg('\0', "disasm") )
		{
			ID3DBlob* disasm;
			D3DDisassemble(code->GetBufferPointer()
				, code->GetBufferSize()
				, 0
				, NULL
				, &disasm
				);

			if (NULL != disasm)
			{
				std::string disasmfp = _cmdLine.findOption('o');
				disasmfp += ".disasm";

				writeFile(disasmfp.c_str(), disasm->GetBufferPointer(), (uint32_t)disasm->GetBufferSize() );
				disasm->Release();
			}
		}

		if (NULL != errorMsg)
		{
			errorMsg->Release();
		}

		result = true;

	error:
		code->Release();
		unload();
		return result;
	}