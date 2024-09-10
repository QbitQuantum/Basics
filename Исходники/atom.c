ATOM
WINAPI
InternalAddAtom(BOOLEAN Local,
                BOOLEAN Unicode,
                LPCSTR AtomName)
{
    NTSTATUS Status;
    ANSI_STRING AnsiString;
    UNICODE_STRING UnicodeString;
    PUNICODE_STRING AtomNameString;
    ATOM Atom = INVALID_ATOM;

    /* Check if it's an integer atom */
    if ((ULONG_PTR)AtomName <= 0xFFFF)
    {
        /* Convert the name to an atom */
        Atom = (ATOM)PtrToShort((PVOID)AtomName);
        if (Atom >= MAXINTATOM)
        {
            /* Fail, atom number too large */
            BaseSetLastNTError(STATUS_INVALID_PARAMETER);
            return INVALID_ATOM;
        }

        /* Return it */
        return Atom;
    }
    else
    {
        /* Check if this is a unicode atom */
        if (Unicode)
        {
            /* Use a unicode string */
            AtomNameString = &UnicodeString;
            RtlInitUnicodeString(AtomNameString, (LPWSTR)AtomName);
            Status = STATUS_SUCCESS;
        }
        else
        {
            /* Use an ansi string */
            RtlInitAnsiString(&AnsiString, AtomName );

            /* Check if we can abuse the TEB */
            if (AnsiString.MaximumLength > 260)
            {
                /* We can't, allocate a new string */
                AtomNameString = &UnicodeString;
                Status = RtlAnsiStringToUnicodeString(AtomNameString,
                                                      &AnsiString,
                                                      TRUE);
            }
            else
            {
                /* We can! Get the TEB String */
                AtomNameString = &NtCurrentTeb()->StaticUnicodeString;

                /* Convert it into the TEB */
                Status = RtlAnsiStringToUnicodeString(AtomNameString,
                                                      &AnsiString,
                                                      FALSE);
            }
        }

        /* Check for failure */
        if (!NT_SUCCESS(Status))
        {
            BaseSetLastNTError(Status);
            return Atom;
        }
    }

    /* Check if we're doing local add */
    if (Local)
    {
        /* Do a local add */
        Status = RtlAddAtomToAtomTable(InternalInitAtomTable(),
                                       AtomNameString->Buffer,
                                       &Atom);
    }
    else
    {
        /* Do a global add */
        Status = NtAddAtom(AtomNameString->Buffer,
                           AtomNameString->Length,
                           &Atom);
    }

    /* Check for failure */
    if (!NT_SUCCESS(Status)) BaseSetLastNTError(Status);

    /* Check if we were non-static ANSI */
    if (!(Unicode) && (AtomNameString == &UnicodeString))
    {
        /* Free the allocated buffer */
        RtlFreeUnicodeString(AtomNameString);
    }

    /* Return the atom */
    return Atom;
}