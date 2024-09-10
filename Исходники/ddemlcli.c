/***************************************************************************\
* DdeNameService (DDEML API)
*
* Description:
* Registers, and Unregisters service names and sets the Initiate filter
* state for an instance.
*
* History:
* 11-1-91 sanfords Created.
\***************************************************************************/
HDDEDATA DdeNameService(
DWORD idInst,
HSZ hsz1, // service name
HSZ hsz2, // reserved for future enhancements
UINT afCmd) // DNS_ flags.
{
    BOOL fRet = TRUE;
    LATOM *plaNameService;
    PCL_INSTANCE_INFO pcii;

    EnterDDECrit;

    pcii = ValidateInstance((HANDLE)LongToHandle( idInst ));
    if (pcii == NULL) {
        BestSetLastDDEMLError(DMLERR_INVALIDPARAMETER);
        fRet = FALSE;
        goto Exit;
    }

    if ((hsz1 && ValidateHSZ(hsz1) == HSZT_INVALID) || hsz2 != 0) {
        SetLastDDEMLError(pcii, DMLERR_INVALIDPARAMETER);
        fRet = FALSE;
        goto Exit;
    }

    if (afCmd & DNS_FILTERON && !(pcii->afCmd & APPCMD_FILTERINITS)) {
        pcii->afCmd |= APPCMD_FILTERINITS;
        NtUserUpdateInstance(pcii->hInstServer, &pcii->MonitorFlags, pcii->afCmd);
    }
    if (afCmd & DNS_FILTEROFF && (pcii->afCmd & APPCMD_FILTERINITS)) {
        pcii->afCmd &= ~APPCMD_FILTERINITS;
        NtUserUpdateInstance(pcii->hInstServer, &pcii->MonitorFlags, pcii->afCmd);
    }

    if (afCmd & (DNS_REGISTER | DNS_UNREGISTER)) {
        GATOM ga;

        if (pcii->afCmd & APPCMD_CLIENTONLY) {
            SetLastDDEMLError(pcii, DMLERR_DLL_USAGE);
            fRet = FALSE;
            goto Exit;
        }

        if (hsz1 == 0) {
            if (afCmd & DNS_REGISTER) {

                /*
                 * registering NULL is not allowed!
                 */
                SetLastDDEMLError(pcii, DMLERR_INVALIDPARAMETER);
                fRet = FALSE;
                goto Exit;
            }

            /*
             * unregistering NULL is just like unregistering each
             * registered name.
             *
             * 10/19/90 - made this a synchronous event so that hsz
             * can be freed by calling app after this call completes
             * without us having to keep a copy around forever.
             */
            plaNameService = pcii->plaNameService;
            while (*plaNameService != 0) {
                ga = LocalToGlobalAtom(*plaNameService);
                DeleteAtom(*plaNameService);
                LeaveDDECrit;
                RegisterService(FALSE, ga, pcii->hwndMother);
                EnterDDECrit;
                GlobalDeleteAtom(ga);
                plaNameService++;
            }
            pcii->cNameServiceAlloc = 1;
            *pcii->plaNameService = 0;
            goto Exit;
        }

        if (afCmd & DNS_REGISTER) {
            plaNameService = (LATOM *)DDEMLReAlloc(pcii->plaNameService,
                    sizeof(LATOM) * ++pcii->cNameServiceAlloc);
            if (plaNameService == NULL) {
                SetLastDDEMLError(pcii, DMLERR_MEMORY_ERROR);
                pcii->cNameServiceAlloc--;
                fRet = FALSE;
                goto Exit;
            } else {
                pcii->plaNameService = plaNameService;
            }
            IncLocalAtomCount(LATOM_FROM_HSZ(hsz1)); // NameService copy
            plaNameService[pcii->cNameServiceAlloc - 2] = LATOM_FROM_HSZ(hsz1);
            plaNameService[pcii->cNameServiceAlloc - 1] = 0;

        } else { // DNS_UNREGISTER
            plaNameService = pcii->plaNameService;
            while (*plaNameService != 0 && *plaNameService != LATOM_FROM_HSZ(hsz1)) {
                plaNameService++;
            }
            if (*plaNameService == 0) {
                goto Exit; // not found just exit
            }
            //
            // fill empty slot with last entry and fill last entry with 0
            //
            pcii->cNameServiceAlloc--;
            *plaNameService = pcii->plaNameService[pcii->cNameServiceAlloc - 1];
            pcii->plaNameService[pcii->cNameServiceAlloc - 1] = 0;
        }

        ga = LocalToGlobalAtom(LATOM_FROM_HSZ(hsz1));
        LeaveDDECrit;
        RegisterService((afCmd & DNS_REGISTER) ? TRUE : FALSE, ga,
            pcii->hwndMother);
        EnterDDECrit;
        GlobalDeleteAtom(ga);
    }

Exit:
    LeaveDDECrit;
    return ((HDDEDATA)IntToPtr( fRet ));
}