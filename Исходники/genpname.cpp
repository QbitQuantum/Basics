int main(int argc, char *argv[]) {
    UErrorCode status = U_ZERO_ERROR;
    u_init(&status);
    if (U_FAILURE(status) && status != U_FILE_ACCESS_ERROR) {
        // Note: u_init() will try to open ICU property data.
        //       failures here are expected when building ICU from scratch.
        //       ignore them.
        fprintf(stderr, "genpname: can not initialize ICU.  Status = %s\n",
            u_errorName(status));
        exit(1);
    }

    genpname app;
    U_MAIN_INIT_ARGS(argc, argv);
    int retVal = app.MMain(argc, argv);
    u_cleanup();
    return retVal;
}