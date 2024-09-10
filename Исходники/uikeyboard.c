HACCEL uikeyboard_create_accelerator_table(void)
{
    FILE *fshortcuts;
    char *complete_path;
    char buffer[1000];
    char *p, *menustr, *metastr, *keystr, *displaystr;
    int i;

    accelnum = 0;
    menuitemmodifier_len = 0;
    for (i = 0; idmlist[i].str != NULL; i++) {
        if (idmlist[i].cmd >= menuitemmodifier_len) {
            menuitemmodifier_len = idmlist[i].cmd + 1;
        }
    }

    menuitemmodifier = lib_calloc(menuitemmodifier_len, sizeof(char*));
    memset(menuitemmodifier, 0, menuitemmodifier_len * sizeof(char*));

    fshortcuts = sysfile_open("win_shortcuts.vsc", &complete_path, MODE_READ_TEXT);
    lib_free(complete_path);
    if (fshortcuts == NULL) {
        log_error(LOG_DEFAULT, "Warning. Cannot open keyboard shortcut file win_shortcuts.vsc.");
        return NULL;
    }

    /* read the shortcut table */
    do {
        buffer[0] = 0;
        if (fgets(buffer, 999, fshortcuts)) {

            if (strlen(buffer) == 0) {
                break;
            }

            buffer[strlen(buffer) - 1] = 0; /* remove newline */

	      /* remove comments */
	      if ((p = strchr(buffer, '#'))) {
                *p = 0;
            }

            metastr = strtok(buffer, " \t:");
            keystr = strtok(NULL, " \t:");
            menustr = strtok(NULL, " \t:");
            displaystr = strtok(NULL, " \t:");
	      if (displaystr && (p = strchr(displaystr, '#'))) {
	          *p = 0;
            }

            if (metastr && keystr && menustr) {
                for (i = 0; idmlist[i].str; i++) {
                    if (strcmp(idmlist[i].str, menustr) == 0) {
                        break;
                    }
                }

                if (idmlist[i].str) {
                    ACCEL accel;

                    accel.fVirt = FVIRTKEY | FNOINVERT;
                    if (strstr(strlwr(metastr), "shift") != NULL) {
                        accel.fVirt |= FSHIFT;
                    }
                    if (strstr(strlwr(metastr), "ctrl") != NULL) {
                        accel.fVirt |= FCONTROL;
                    }
                    if (strstr(strlwr(metastr), "alt") != NULL) {
                        accel.fVirt |= FALT;
                    }

                    if (keystr[0] == '\'' && keystr[2] == '\'') {
                        accel.key = keystr[1];
                        if (displaystr == NULL || displaystr[0] == 0) {
                            displaystr = keystr + 1;
                            keystr[2] = 0;
                        }
                    } else {
                        accel.key = (unsigned short)strtol(keystr, NULL, 0);
                    }

                    accel.cmd = idmlist[i].cmd;

                    if (accel.key > 0 && accel.cmd > 0 && accelnum < MAXACCEL) {
                        accellist[accelnum++] = accel;
                    }

                    if (displaystr != NULL && menuitemmodifier[accel.cmd] == NULL) {
                        p = util_concat("\t",
                                        ((accel.fVirt & FSHIFT  ) ? "Shift+" : ""),
                                        ((accel.fVirt & FCONTROL) ? "Ctrl+" : ""),
                                        ((accel.fVirt & FALT) ? "Alt+" : ""),
                                        displaystr, NULL);

                        menuitemmodifier[accel.cmd] = p;
                    }
                }
            }
        }
    } while (!feof(fshortcuts));
    fclose(fshortcuts);

    return CreateAcceleratorTable(accellist, accelnum);
}