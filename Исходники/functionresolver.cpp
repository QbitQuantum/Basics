    void FunctionResolver::resolveParameters(const ULONG64& functionAddress, const ULONG64& modBase, const ULONG& typeIndex, std::vector<FunctionParameter>& resolvedParameters)
    {
        IMAGEHLP_STACK_FRAME sf;

        sf.InstructionOffset = functionAddress;

        if (!SymSetContext(this->m_hProcess, &sf, 0))
        {
            throw;
        }

        // Retrieve all parameters of this function.
        SymEnumSymbols(this->m_hProcess, NULL, NULL, EnumParamsCallback, &resolvedParameters);
    }