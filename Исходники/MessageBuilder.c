struct Header *BuildRequestFromHeader(MESSAGE *message, struct Dialog *dialog)
{
    struct UserAgent *ua = DialogGetUserAgent(dialog);
    URI *uri = CreateUri(URI_SCHEME_SIP, UaGetUserName(ua), UaGetProxy(ua), 0);
    CONTACT_HEADER *from = CreateFromHeader();
    struct Parameters *ps = ContactHeaderGetParameters(from);
    char tag[MAX_TAG_LENGTH +1] = {0};

    if (strlen(DialogGetLocalTag(dialog)) == 0){
        GenerateTag(tag);
        DialogSetLocalTag(dialog, tag);
    } else {
        strcpy(tag, DialogGetLocalTag(dialog));
    }

    AddParameter(ps, HEADER_PARAMETER_NAME_TAG, tag);
    ContactHeaderSetUri(from, uri);
    
    return (struct Header *)from;
}