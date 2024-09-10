unsigned int GpgSetExpiryTimeEditInteractor::nextState(unsigned int status, const char *args, Error &err) const
{

    static const Error GENERAL_ERROR  = Error::fromCode(GPG_ERR_GENERAL);
    static const Error INV_TIME_ERROR = Error::fromCode(GPG_ERR_INV_TIME);

    if (needsNoResponse(status)) {
        return state();
    }

    using namespace GpgSetExpiryTimeEditInteractor_Private;

    switch (state()) {
    case START:
        if (status == GPGME_STATUS_GET_LINE &&
                strcmp(args, "keyedit.prompt") == 0) {
            return COMMAND;
        }
        err = GENERAL_ERROR;
        return ERROR;
    case COMMAND:
        if (status == GPGME_STATUS_GET_LINE &&
                strcmp(args, "keygen.valid") == 0) {
            return DATE;
        }
        err = GENERAL_ERROR;
        return ERROR;
    case DATE:
        if (status == GPGME_STATUS_GET_LINE &&
                strcmp(args, "keyedit.prompt") == 0) {
            return QUIT;
        } else if (status == GPGME_STATUS_GET_LINE &&
                   strcmp(args, "keygen.valid")) {
            err = INV_TIME_ERROR;
            return ERROR;
        }
        err = GENERAL_ERROR;
        return ERROR;
    case QUIT:
        if (status == GPGME_STATUS_GET_BOOL &&
                strcmp(args, "keyedit.save.okay") == 0) {
            return SAVE;
        }
        err = GENERAL_ERROR;
        return ERROR;
    case ERROR:
        if (status == GPGME_STATUS_GET_LINE &&
                strcmp(args, "keyedit.prompt") == 0) {
            return QUIT;
        }
        err = lastError();
        return ERROR;
    default:
        err = GENERAL_ERROR;
        return ERROR;
    }
}