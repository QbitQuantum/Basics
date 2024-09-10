        void ThrowLastSetupError()
        {
            DWORD code;
            char msg[BUFFER_SIZE];

            SQLInstallerError(1, &code, msg, sizeof(msg), NULL);

            std::stringstream buf;

            buf << "Message: \"" << msg << "\", Code: " << code;

            throw IgniteError(IgniteError::IGNITE_ERR_GENERIC, buf.str().c_str());
        }