TADDR
DacGetTargetAddrForHostAddr(LPCVOID ptr, bool throwEx)
{
#ifdef _PREFIX_

    // Dac accesses are not interesting for PREfix and cause alot of PREfix noise
    // so we just return the unmodified pointer for our PREFIX builds
    return (TADDR) ptr;

#else // !_PREFIX_

    // Preserve special pointer values.
    if (ptr == NULL || ((TADDR) ptr == (TADDR)-1))
    {
        return 0;
    }
    else
    {
        TADDR addr = 0;
        HRESULT status = E_FAIL;

        EX_TRY
        {
            DAC_INSTANCE* inst = (DAC_INSTANCE*)ptr - 1;
            if (inst->sig == DAC_INSTANCE_SIG)
            {
                addr = inst->addr;
                status = S_OK;
            }
            else
            {
                status = E_INVALIDARG;
            }
        }
        EX_CATCH
        {
            status = E_INVALIDARG;
        }
        EX_END_CATCH(SwallowAllExceptions)

        if (status != S_OK)
        {
            if (g_dacImpl && g_dacImpl->m_debugMode)
            {
                DebugBreak();
            }

            if (throwEx)
            {
                // This means a pointer was supplied which doesn't actually point to the beginning of 
                // a marshalled DAC instance.
                _ASSERTE_MSG(false, "DAC coding error: Attempt to get target address from a host pointer "
                                    "which is not an instance marshalled by DAC!");
                DacError(status);
            }
        }

        return addr;
    }

#endif // !_PREFIX_
}