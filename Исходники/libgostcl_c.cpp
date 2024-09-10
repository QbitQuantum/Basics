//------------------------------------------------------------------------------
int LIBGOSTCLSHARED_EXPORT
    Decrypt (const char * data,
             char * result,
             int mode,
             char * errorStr)
{
    if ((0 == data) ||
        (0 == result) )
    {
        if (errorStr != 0)
        {
            std::string error = GetErrorMessage(5);
            std::copy (error.begin(), error.end(), errorStr);
        }
        return 1;
    }

    LibGostCL::ModeOfOperation operationMode;
    switch (mode)
    {
    case 0:
        operationMode = LibGostCL::ECB;
        break;
    case 1:
        operationMode = LibGostCL::CBC;
        break;
    case 2:
        operationMode = LibGostCL::OFB;
        break;
    case 3:
        operationMode = LibGostCL::CFB;
        break;
    default:
        if (errorStr != 0)
        {
            std::string error = GetErrorMessage(4);
            std::copy (error.begin(), error.end(), errorStr);
        }
        return 1;
        break;
    }

    Crypter gCrypter;

    gCrypter.SetModeOfOperation(operationMode);

    std::string output;
    bool success = gCrypter.Decrypt(std::string(data), output);

    std::copy (output.begin(), output.end(), result);

    if (0 != errorStr)
    {
        std::string error = GetErrorMessage(gCrypter.GetErrorCode());
        std::copy (error.begin(), error.end(), errorStr);
    }

    return ((success == true) ? 0 : 1) ;

}