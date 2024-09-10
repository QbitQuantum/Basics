void
Normalizer2DataBuilder::setUnicodeVersion(const char *v) {
    UVersionInfo nullVersion= { 0, 0, 0, 0 };
    UVersionInfo version;
    u_versionFromString(version, v);
    if( 0!=memcmp(version, unicodeVersion, U_MAX_VERSION_LENGTH) &&
            0!=memcmp(nullVersion, unicodeVersion, U_MAX_VERSION_LENGTH)
      ) {
        char buffer[U_MAX_VERSION_STRING_LENGTH];
        u_versionToString(unicodeVersion, buffer);
        fprintf(stderr, "gennorm2 error: multiple inconsistent Unicode version numbers %s vs. %s\n",
                buffer, v);
        exit(U_ILLEGAL_ARGUMENT_ERROR);
    }
    memcpy(unicodeVersion, version, U_MAX_VERSION_LENGTH);
}