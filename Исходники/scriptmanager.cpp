    bool ScriptManager::compile (const std::string& name)
    {
        mParser.reset();
        mErrorHandler.reset();

        bool Success = true;

        if (const ESM::Script *script = mStore.scripts.find (name))
        {
            if (mVerbose)
                std::cout << "compiling script: " << name << std::endl;

            try
            {
                std::istringstream input (script->scriptText);

                Compiler::Scanner scanner (mErrorHandler, input, mCompilerContext.getExtensions());

                scanner.scan (mParser);

                if (!mErrorHandler.isGood())
                    Success = false;
            }
            catch (...)
            {
                Success = false;
            }

            if (!Success && mVerbose)
            {
                std::cerr
                    << "compiling failed: " << name << std::endl
                    << script->scriptText
                    << std::endl << std::endl;
            }

            if (Success)
            {
                std::vector<Interpreter::Type_Code> code;
                mParser.getCode (code);
                mScripts.insert (std::make_pair (name, code));

                // TODO sanity check on generated locals

                return true;
            }
        }

        return false;
    }