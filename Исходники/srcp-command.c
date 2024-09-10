/**
 * TERM
 * negative return code (rc) will terminate current session! */
int handleTERM(sessionid_t sessionid, bus_t bus, char *device,
               char *parameter, char *reply)
{
    struct timeval akt_time;
    int rc = SRCP_UNSUPPORTEDDEVICEGROUP;
    *reply = 0x00;

    if (bus_has_devicegroup(bus, DG_GL)
        && strncasecmp(device, "GL", 2) == 0) {
        long int addr = 0;
        int nelem = 0;
        if (strlen(parameter) > 0)
            nelem = sscanf(parameter, "%ld", &addr);
        if (nelem == 1) {
            sessionid_t lockid;
            cacheGetLockGL(bus, addr, &lockid);
            if (lockid == 0) {
                rc = cacheTermGL(bus, addr);
            }
            else if (lockid == sessionid) {
                if (SRCP_OK == cacheUnlockGL(bus, addr, sessionid))
                    rc = cacheTermGL(bus, addr);
            }
            else {
                rc = SRCP_DEVICELOCKED;
            }
        }
    }
    else if (bus_has_devicegroup(bus, DG_GA)
             && strncasecmp(device, "GA", 2) == 0) {
        long int addr = 0;
        int nelem = 0;
        if (strlen(parameter) > 0)
            nelem = sscanf(parameter, "%ld", &addr);
        if (nelem == 1) {
            sessionid_t lockid;
            getlockGA(bus, addr, &lockid);
            if (lockid == 0) {
                rc = termGA(bus, addr);
            }
            else if (lockid == sessionid) {
                if (SRCP_OK == unlockGA(bus, addr, sessionid))
                    rc = termGA(bus, addr);
            }
            else {
                rc = SRCP_DEVICELOCKED;
            }
        }
    }
    else if (bus_has_devicegroup(bus, DG_LOCK)
             && strncasecmp(device, "LOCK", 4) == 0) {
        long int addr;
        char devgrp[10];
        int nelem = -1;
        if (strlen(parameter) > 0)
            nelem = sscanf(parameter, "%s %ld", devgrp, &addr);

        if (nelem <= 1) {
            rc = SRCP_LISTTOOSHORT;
        }
        else {
            rc = SRCP_UNSUPPORTEDDEVICE;
            if (strncmp(devgrp, "GL", 2) == 0) {
                rc = cacheUnlockGL(bus, addr, sessionid);
            }
            else if (strncmp(devgrp, "GA", 2) == 0) {
                rc = unlockGA(bus, addr, sessionid);
            }
        }
    }

    else if (bus_has_devicegroup(bus, DG_POWER)
             && strncasecmp(device, "POWER", 5) == 0) {
        rc = termPower(bus);
    }

    else if (bus_has_devicegroup(bus, DG_SERVER)
             && strncasecmp(device, "SERVER", 6) == 0) {
        rc = SRCP_OK;
        server_shutdown();
    }

    else if (bus_has_devicegroup(bus, DG_SESSION)
             && strncasecmp(device, "SESSION", 7) == 0) {
        sessionid_t termsession = 0;
        int nelem = 0;
        if (strlen(parameter) > 0)
            nelem = sscanf(parameter, "%ld", &termsession);
        if (nelem <= 0)
            termsession = sessionid;
        rc = termSESSION(bus, sessionid, termsession, reply);
    }

    else if (bus_has_devicegroup(bus, DG_SM)
             && strncasecmp(device, "SM", 2) == 0) {
        rc = infoSM(bus, TERM, 0, -1, 0, 0, 0, reply);
    }

    else if (bus_has_devicegroup(bus, DG_TIME)
             && strncasecmp(device, "TIME", 4) == 0) {
        rc = termTIME();
    }

    gettimeofday(&akt_time, NULL);
    srcp_fmt_msg(abs(rc), reply, akt_time);
    return rc;
}