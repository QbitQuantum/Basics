BOOLEAN
NTAPI
PasswordFilter(
    PUNICODE_STRING UserName,
    PUNICODE_STRING FullName,
    PUNICODE_STRING Password,
    BOOLEAN SetOperation
    )
/*++

Routine Description:

    This (optional) routine is notified of a password change.

Arguments:

    UserName - Name of user whose password changed

    FullName - Full name of the user whose password changed

    NewPassword - Cleartext new password for the user

    SetOperation - TRUE if the password was SET rather than CHANGED

Return Value:

    TRUE if the specified Password is suitable (complex, long, etc).
     The system will continue to evaluate the password update request
     through any other installed password change packages.

    FALSE if the specified Password is unsuitable. The password change
     on the specified account will fail.

--*/
{

    BOOLEAN bComplex = FALSE; // assume the password in not complex enough
    DWORD cchPassword;
    DWORD i;
    DWORD j;
    DWORD count;
    DWORD dwNum = 0;
    DWORD dwUpper = 0;
    DWORD dwLower = 0;
    DWORD dwSpecialChar = 0 ;
    PCHAR token ;
    CHAR _password[PWLEN+1];
    CHAR _username[UNLEN+1];
    PCHAR _fullname = NULL;
    WORD CharType[PWLEN+1];
    PCHAR TempString;

    //
    // If the password was explicitly set, allow it through.
    //

    if (SetOperation)
    {
        bComplex = TRUE;
        goto end;
    }

    //
    // Make sure the password and username will fit in our local buffers
    //

    if (Password->Length > PWLEN * sizeof(WCHAR))
    {
        goto end;
    }

    if (UserName->Length > UNLEN * sizeof(WCHAR))
    {
        goto end;
    }

    _fullname = HeapAlloc(GetProcessHeap(), 0, FullName->Length + sizeof(WCHAR));
    if (_fullname == NULL)
    {
        goto end;
    }


    //
    // check if the password is complex enough for our liking by
    // checking that at least two of the four character types are
    // present.
    //

    cchPassword = Password->Length / sizeof(WCHAR);


    if(GetStringTypeW(
        CT_CTYPE1,
        Password->Buffer,
        cchPassword,
        CharType
        )) {

        for(i = 0 ; i < cchPassword ; i++) {

            //
            // keep track of what type of characters we have encountered
            //

            if(CharType[i] & C1_DIGIT) {
                dwNum = 1;
                continue;
            }

            if(CharType[i] & C1_UPPER) {
                dwUpper = 1;
                continue;
            }

            if(CharType[i] & C1_LOWER) {
                dwLower = 1;
                continue;
            }

        } // for

        //
        // Indicate whether we encountered enough password complexity
        //

        if( (dwNum + dwLower + dwUpper) < 2) {

            bComplex = FALSE ;
            goto end ;

        } else {

            //
            // now we resort to more complex checking
            //
            wcstombs(_password, Password->Buffer, PWLEN+1) ;
            wcstombs(_username, UserName->Buffer, UNLEN+1) ;
            wcstombs(_fullname, FullName->Buffer, 1+FullName->Length/sizeof(WCHAR)) ;

            _strupr(_password) ;
            _password[Password->Length/sizeof(WCHAR)] = '\0' ;
            _strupr(_username) ;
            _username[UserName->Length/sizeof(WCHAR)] = '\0' ;
            _strupr(_fullname) ;
            _fullname[FullName->Length/sizeof(WCHAR)] = '\0' ;

            if (strpbrk (_password, "(`~!@#$%^&*_-+=|\\{}[]:;\"'<>,.?)") != NULL) {
                dwSpecialChar = 1 ;
            }

            if ((dwNum + dwLower + dwUpper + dwSpecialChar) < 3) {
                bComplex = FALSE ;
                goto end ;
            }

            if ((UserName->Length >= 3 * sizeof(WCHAR)) && strstr (_password, _username)) {

                bComplex = FALSE ;
                goto end ;
            }


            //
            // Tokenize the full name and check if the password is derived from it
            //

            token = LocalStrTok(_fullname, " ,.\t-_#",&TempString);
            while( token != NULL ) {

                if (lstrlenA(token) > 3 && strstr(_password, token)) {
                    bComplex = FALSE ;
                    goto end ;
                }

                token = LocalStrTok(NULL, " ,.\t-_#",&TempString);
            }

            bComplex = TRUE ;

        }


    } // if

end:

    ZeroMemory( CharType, Password->Length );
    ZeroMemory( _password, Password->Length );
    HeapFree(GetProcessHeap(), 0, _fullname);

    return bComplex;
}