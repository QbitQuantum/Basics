int skapmot(void) {
    struct ShortUser *shortUser;
    int mad, setPermission, changed, ch, i, fidoDomainId, highestId;
    struct FidoDomain *fidoDomain;
    BPTR lock;
    struct User user;
    struct Mote tmpConf,*searchConf,*newConf;

    memset(&tmpConf, 0, sizeof(struct Mote));
    if(argument[0] == '\0') {
        SendString("\r\n\nNamn på mötet: ");
        if(GetString(40,NULL)) {
            return 1;
        }
        strcpy(tmpConf.namn, inmat);
    } else {
        strcpy(tmpConf.namn, argument);
    }
    if(parsemot(tmpConf.namn) != -1) {
        SendString("\r\n\nFinns redan ett sådant möte!\r\n");
        return 0;
    }
    tmpConf.skapat_tid = time(NULL);;
    tmpConf.skapat_av = inloggad;
    for(;;) {
        SendString("\r\nMötesAdministratör (MAD) : ");
        if(GetString(5,NULL)) {
            return 1;
        }
        if(inmat[0]) {
            if((mad = parsenamn(inmat)) == -1) {
                SendString("\r\nFinns ingen sådan användare!");
            } else {
                tmpConf.mad = mad;
                break;
            }
        }
    }
    SendString("\n\rSorteringsvärde: ");
    tmpConf.sortpri = GetNumber(0, LONG_MAX, NULL);

    if(EditBitFlagShort("\r\nSka mötet vara slutet?", 'j', 'n', "Slutet", "Öppet",
                        &tmpConf.status, SLUTET)) {
        return 1;
    }
    if(tmpConf.status & SLUTET) {
        SendString("\r\nVilka grupper ska ha tillgång till mötet? (? för lista)\r\n");
        if(editgrupp((char *)&tmpConf.grupper)) {
            return 1;
        }
    }
    if(EditBitFlagShort("\r\nSka mötet vara skrivskyddat?", 'j', 'n',
                        "Skyddat", "Oskyddat", &tmpConf.status, SKRIVSKYDD)) {
        return 1;
    }
    if(EditBitFlagShort("\r\nSka mötet vara kommentarsskyddat?", 'j', 'n',
                        "Skyddat", "Oskyddat", &tmpConf.status, KOMSKYDD)) {
        return 1;
    }
    if(EditBitFlagShort("\r\nSka mötet vara hemligt?", 'j', 'n',
                        "Hemligt", "Ej hemligt", &tmpConf.status, HEMLIGT)) {
        return 1;
    }
    if(!(tmpConf.status & SLUTET)) {
        if(EditBitFlagShort("\r\nSka alla användare bli medlemmar automagiskt?", 'j', 'n',
                            "Ja", "Nej", &tmpConf.status, AUTOMEDLEM)) {
            return 1;
        }
        if(EditBitFlagShort("\r\nSka rättigheterna styra skrivmöjlighet?", 'j', 'n',
                            "Ja", "Nej", &tmpConf.status, SKRIVSTYRT)) {
            return 1;
        }
        if(tmpConf.status & SKRIVSTYRT) {
            SendString("\r\nVilka grupper ska ha tillgång till mötet? (? för lista)\r\n");
            if(editgrupp((char *)&tmpConf.grupper)) {
                return 1;
            }
        }
    }
    if(EditBitFlagShort("\r\nSka mötet enbart kommas åt från ARexx?", 'j', 'n',
                        "Ja", "Nej", &tmpConf.status, SUPERHEMLIGT)) {
        return 1;
    }

    SendString("\n\n\rVilken typ av möte ska det vara?\n\r");
    SendString("1: Lokalt möte\n\r");
    SendString("2: Fido-möte\n\n\r");
    SendString("Val: ");
    for(;;) {
        ch = GetChar();
        if(ch == GETCHAR_LOGOUT) {
            return 1;
        }
        if(ch == '1' || ch == '2') {
            break;
        }
    }
    if(ch == '1') {
        SendString("Lokalt möte\n\n\r");
        tmpConf.type = MOTE_ORGINAL;
    } else {
        SendString("Fido-möte\n\n\r");
        tmpConf.type = MOTE_FIDO;
        if(EditString("Katalog for .msg-filerna", tmpConf.dir, 79, TRUE)) {
            return 1;
        }
        if(!(lock = Lock(tmpConf.dir, SHARED_LOCK))) {
            if(!(lock = CreateDir(tmpConf.dir)))
                SendString("\n\rKunde inte skapa katalogen\n\r");
        }
        if(lock) {
            UnLock(lock);
        }
        if(EditString("FidoNet tag-namn", tmpConf.tagnamn, 49, TRUE)) {
            return 1;
        }
        strcpy(tmpConf.origin, Servermem->fidodata.defaultorigin);
        if(MaybeEditString("Origin-rad", tmpConf.origin, 69)) {
            return 1;
        }

        SendString("\n\n\rVilken teckenuppsättning ska användas för utgående texter?\n\r");
        SendString("1: ISO Latin 1 (ISO 8859-1)\n\r");
        SendString("2: SIS-7 (SF7, 'Måsvingar')\n\r");
        SendString("3: IBM CodePage\n\r");
        SendString("4: Mac\n\n\r");
        SendString("Val: ");
        for(;;) {
            ch = GetChar();
            if(ch == GETCHAR_LOGOUT) {
                return 1;
            }
            if(ch == '1' || ch == '2' || ch == '3' || ch == '4') {
                break;
            }
        }
        switch(ch) {
        case '1':
            SendString("ISO Latin 1\n\n\r");
            tmpConf.charset = CHRS_LATIN1;
            break;
        case '2':
            SendString("SIS-7\n\n\r");
            tmpConf.charset = CHRS_SIS7;
            break;
        case '3':
            SendString("IBM CodePage\n\n\r");
            tmpConf.charset = CHRS_CP437;
            break;
        case '4':
            SendString("Mac\n\n\r");
            tmpConf.charset = CHRS_MAC;
            break;
        }
        SendString("Vilken domän är mötet i?\n\r");
        highestId = 0;
        for(i = 0; i < 10; i++) {
            if(!Servermem->fidodata.fd[i].domain[0]) {
                break;
            }
            highestId = max(highestId, Servermem->fidodata.fd[i].nummer);
            SendString("%3d: %s (%d:%d/%d.%d)\n\r",
                       Servermem->fidodata.fd[i].nummer,
                       Servermem->fidodata.fd[i].domain,
                       Servermem->fidodata.fd[i].zone,
                       Servermem->fidodata.fd[i].net,
                       Servermem->fidodata.fd[i].node,
                       Servermem->fidodata.fd[i].point);
        }
        if(i == 0) {
            SendString("\n\rDu måste definiera en domän i NiKomFido.cfg först!\n\r");
            return 0;
        }
        for(;;) {
            SendString("\r\nDomän: ");
            if(GetString(5, NULL)) {
                return 1;
            }
            fidoDomainId = atoi(inmat);
            if(fidoDomain = getfidodomain(fidoDomainId, 0)) {
                break;
            } else {
                SendString("\n\rFinns ingen sådan domän.\n\r");
            }
        }
        tmpConf.domain = fidoDomain->nummer;
        SendString("%s\n\n\r", fidoDomain->domain);
    }
    for(i = 0; i < MAXMOTE; i++) {
        if(getmotpek(i) == NULL) {
            break;
        }
    }
    if(i >= MAXMOTE) {
        SendString("\n\n\rDet finns inte plats för fler möten.\n\r");
        return 0;
    }
    tmpConf.nummer = i;
    if(!(newConf = (struct Mote *)AllocMem(sizeof(struct Mote),
                                           MEMF_CLEAR | MEMF_PUBLIC))) {
        LogEvent(SYSTEM_LOG, ERROR, "Could not allocate %d bytes.", sizeof(struct Mote));
        DisplayInternalError();
        return 0;
    }
    memcpy(newConf, &tmpConf, sizeof(struct Mote));
    ITER_EL(searchConf, Servermem->mot_list, mot_node, struct Mote *) {
        if(searchConf->sortpri > newConf->sortpri) {
            break;
        }
    }

    searchConf = (struct Mote *)searchConf->mot_node.mln_Pred;
    Insert((struct List *)&Servermem->mot_list, (struct Node *)newConf,
           (struct Node *)searchConf);
    writemeet(newConf);

    if((newConf->status & AUTOMEDLEM) && !(newConf->status & SKRIVSTYRT)) {
        return 0;
    }
    if(newConf->status & SUPERHEMLIGT) {
        return 0;
    }

    setPermission = (newConf->status & (SLUTET | SKRIVSTYRT)) ? FALSE : TRUE;
    for(i = 0; i < MAXNOD; i++) {
        BAMCLEAR(Servermem->inne[i].motmed, newConf->nummer);
        if(setPermission) {
            BAMSET(Servermem->inne[i].motratt, newConf->nummer);
        } else {
            BAMCLEAR(Servermem->inne[i].motratt, newConf->nummer);
        }
    }

    SendString("\r\nÄndrar i användardata..\r\n");
    ITER_EL(shortUser, Servermem->user_list, user_node, struct ShortUser *) {
        if(!(shortUser->nummer % 10)) {
            SendString("\r%d", shortUser->nummer);
        }
        if(readuser(shortUser->nummer, &user)) {
            LogEvent(SYSTEM_LOG, ERROR, "Could not read user %d to set "
                     "membership/permissions for new conference.", shortUser->nummer);
            DisplayInternalError();
            return 0;
        }
        changed = FALSE;
        if(setPermission != BAMTEST(user.motratt, newConf->nummer)) {
            if(setPermission) {
                BAMSET(user.motratt, newConf->nummer);
            } else {
                BAMCLEAR(user.motratt, newConf->nummer);
            }
            changed = TRUE;
        }
        if(!(newConf->status & AUTOMEDLEM) && BAMTEST(user.motmed, newConf->nummer)) {
            BAMCLEAR(user.motmed, newConf->nummer);
            changed = TRUE;
        }
        if(changed && writeuser(shortUser->nummer, &user)) {
            LogEvent(SYSTEM_LOG, ERROR, "Could not write user %d to set "
                     "membership/permissions for new conference.", shortUser->nummer);
            DisplayInternalError();
            return 0;
        }

    }
    for(i = 0; i < MAXNOD; i++) {
        BAMCLEAR(Servermem->inne[i].motmed, newConf->nummer);
        if(setPermission) {
            BAMSET(Servermem->inne[i].motratt, newConf->nummer);
        } else {
            BAMCLEAR(Servermem->inne[i].motratt, newConf->nummer);
        }
    }
    BAMSET(Servermem->inne[nodnr].motratt, newConf->nummer);
    BAMSET(Servermem->inne[nodnr].motmed, newConf->nummer);
    if(newConf->type == MOTE_FIDO) {
        ReScanFidoConf(newConf, 0);
    }
    return 0;
}