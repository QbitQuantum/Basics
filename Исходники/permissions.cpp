    BOOST_LOG_ONCE_BLOCK()
    {
        if (!InitializeSecurityDescriptor(&g_unrestricted_security_descriptor, SECURITY_DESCRIPTOR_REVISION))
        {
            DWORD err = GetLastError();
            BOOST_LOG_THROW_DESCR_PARAMS(system_error, "Failed to initialize security descriptor", (err));
        }

        if (!SetSecurityDescriptorDacl(&g_unrestricted_security_descriptor, TRUE, NULL, FALSE))
        {
            DWORD err = GetLastError();
            BOOST_LOG_THROW_DESCR_PARAMS(system_error, "Failed to set null DACL to a security descriptor", (err));
        }

        g_unrestricted_security_attributes.nLength = sizeof(g_unrestricted_security_attributes);
        g_unrestricted_security_attributes.lpSecurityDescriptor = &g_unrestricted_security_descriptor;
        g_unrestricted_security_attributes.bInheritHandle = FALSE;
    }