    bool ScriptManager::compile (const std::string& name)
    {
        mParser.reset();
        mErrorHandler.reset();

        if (const ESM::Script *script = mStore.get<ESM::Script>().find (name))
        {
            mErrorHandler.setContext(name);

            bool Success = true;
            try
            {
                std::istringstream input (script->mScriptText);

                Compiler::Scanner scanner (mErrorHandler, input, mCompilerContext.getExtensions());

                scanner.scan (mParser);

                if (!mErrorHandler.isGood())
                    Success = false;
            }
            catch (const Compiler::SourceException&)
            {
                // error has already been reported via error handler
                Success = false;
            }
            catch (const std::exception& error)
            {
                Log(Debug::Error) << "Error: An exception has been thrown: " << error.what();
                Success = false;
            }

            if (!Success)
            {
                Log(Debug::Error) << "Error: script compiling failed: " << name;
            }

            if (Success)
            {
                std::vector<Interpreter::Type_Code> code;
                mParser.getCode (code);
                mScripts.insert (std::make_pair (name, std::make_pair (code, mParser.getLocals())));

                return true;
            }
        }

        return false;
    }