bool VaultTextNoteNode::GetVisitInfo (plAgeInfoStruct * info) {

    wchar_t * mem;
    const wchar_t * str = mem = wcsdup(GetNoteText());
    
    for (unsigned i = 0; i < kNumAgeInfoFields; ++i) {
        
        wchar_t token[1024];
        switch (i) {
            case kAgeFilename: {
                StrTokenize(&str, token, arrsize(token), L"|", 1);
                if (StrLen(token) > 0) {
                    char ansi[1024];
                    StrToAnsi(ansi, token, arrsize(ansi));
                    info->SetAgeFilename(ansi);
                }
            }
            break;
            
            case kAgeInstName: {
                StrTokenize(&str, token, arrsize(token), L"|", 1);
                if (StrLen(token) > 0) {
                    char ansi[1024];
                    StrToAnsi(ansi, token, arrsize(ansi));
                    info->SetAgeInstanceName(ansi);
                }
            }
            break;
            
            case kAgeUserName: {
                StrTokenize(&str, token, arrsize(token), L"|", 1);
                if (StrLen(token) > 0) {
                    char ansi[1024];
                    StrToAnsi(ansi, token, arrsize(ansi));
                    info->SetAgeUserDefinedName(ansi);
                }
            }
            break;
            
            case kAgeDesc: {
                StrTokenize(&str, token, arrsize(token), L"|", 1);
                if (StrLen(token) > 0) {
                    char ansi[1024];
                    StrToAnsi(ansi, token, arrsize(ansi));
                    info->SetAgeDescription(ansi);
                }
            }
            break;
            
            case kAgeInstGuid: {
                StrTokenize(&str, token, arrsize(token), L"|", 1);
                if (StrLen(token) > 0) {
                    plUUID uuid(plString::FromWchar(token));
                    info->SetAgeInstanceGuid(&uuid);
                }
            }
            break;
            
            case kAgeLanguage: {
                StrTokenize(&str, token, arrsize(token), L"|", 1);
                if (StrLen(token) > 0) {
                    info->SetAgeLanguage(StrToUnsigned(token, nil, 10));
                }
            }
            break;
            
            case kAgeSequence: {
                StrTokenize(&str, token, arrsize(token), L"|", 1);
                if (StrLen(token) > 0) {
                    info->SetAgeSequenceNumber(StrToUnsigned(token, nil, 10));
                }
            }
            break;

            DEFAULT_FATAL(i);
        }
    }

    free(mem);
    return true;
}