/*
 * Enumerate network interfaces using IP Helper Library routine GetIfTable.
 * We use GetIfTable rather than other IP helper routines because it's
 * available on 98 & NT SP4+.
 *
 * Returns the number of interfaces found or -1 if error. If no error
 * occurs then netifPP be returned as list of netif structures or NULL
 * if no interfaces are found.
 */
int enumInterfaces(JNIEnv *env, netif **netifPP)
{
    MIB_IFTABLE *tableP;
    MIB_IFROW *ifrowP;
    ULONG size;
    DWORD ret;
    int count;
    netif *netifP;
    DWORD i;
    int lo=0, eth=0, tr=0, fddi=0, ppp=0, sl=0, wlan=0, net=0, wlen=0;

    /*
     * Ask the IP Helper library to enumerate the adapters
     */
    size = sizeof(MIB_IFTABLE);
    tableP = (MIB_IFTABLE *)malloc(size);
    if (tableP == NULL) {
        JNU_ThrowOutOfMemoryError(env, "Native heap allocation failure");
        return -1;
    }

    ret = GetIfTable(tableP, &size, TRUE);
    if (ret == ERROR_INSUFFICIENT_BUFFER || ret == ERROR_BUFFER_OVERFLOW) {
        MIB_IFTABLE * newTableP = (MIB_IFTABLE *)realloc(tableP, size);
        if (newTableP == NULL) {
            free(tableP);
            JNU_ThrowOutOfMemoryError(env, "Native heap allocation failure");
            return -1;
        }
        tableP = newTableP;
        ret = GetIfTable(tableP, &size, TRUE);
    }

    if (ret != NO_ERROR) {
        free(tableP);

        JNU_ThrowByName(env, "java/lang/Error",
                        "IP Helper Library GetIfTable function failed");

        return -1;
    }

    /*
     * Iterate through the list of adapters
     */
    count = 0;
    netifP = NULL;

    ifrowP = tableP->table;
    for (i=0; i<tableP->dwNumEntries; i++) {
        char dev_name[8];
        netif *curr;

        /*
         * Generate a name for the device as Windows doesn't have any
         * real concept of a device name.
         */
        switch (ifrowP->dwType) {
        case MIB_IF_TYPE_ETHERNET:
            _snprintf_s(dev_name, 8, _TRUNCATE, "eth%d", eth++);
            break;

        case MIB_IF_TYPE_TOKENRING:
            _snprintf_s(dev_name, 8, _TRUNCATE, "tr%d", tr++);
            break;

        case MIB_IF_TYPE_FDDI:
            _snprintf_s(dev_name, 8, _TRUNCATE, "fddi%d", fddi++);
            break;

        case MIB_IF_TYPE_LOOPBACK:
            /* There should only be only IPv4 loopback address */
            if (lo > 0) {
                continue;
            }
            strncpy_s(dev_name, 8, "lo", _TRUNCATE);
            lo++;
            break;

        case MIB_IF_TYPE_PPP:
            _snprintf_s(dev_name, 8, _TRUNCATE, "ppp%d", ppp++);
            break;

        case MIB_IF_TYPE_SLIP:
            _snprintf_s(dev_name, 8, _TRUNCATE, "sl%d", sl++);
            break;

        case IF_TYPE_IEEE80211:
            _snprintf_s(dev_name, 8, _TRUNCATE, "wlan%d", wlan++);
            break;

        default:
            _snprintf_s(dev_name, 8, _TRUNCATE, "net%d", net++);
        }

        /*
         * Allocate a netif structure and space for the name and
         * display name (description in this case).
         */
        curr = (netif *)calloc(1, sizeof(netif));
        if (curr != NULL) {
            wlen = MultiByteToWideChar(CP_OEMCP, 0, ifrowP->bDescr,
                                       ifrowP->dwDescrLen, NULL, 0);
            if(wlen == 0) {
                // MultiByteToWideChar should not fail
                // But in rare case it fails, we allow 'char' to be displayed
                curr->displayName = (char *)malloc(ifrowP->dwDescrLen + 1);
            } else {
                curr->displayName = (wchar_t *)malloc(wlen*(sizeof(wchar_t))+1);
            }

            curr->name = (char *)malloc(strlen(dev_name) + 1);

            if (curr->name == NULL || curr->displayName == NULL) {
                if (curr->name) free(curr->name);
                if (curr->displayName) free(curr->displayName);
                curr = NULL;
            }
        }
        if (curr == NULL) {
            JNU_ThrowOutOfMemoryError(env, "Native heap allocation failure");
            free_netif(netifP);
            free(tableP);
            return -1;
        }

        /*
         * Populate the interface. Note that we need to convert the
         * index into its "friendly" value as otherwise we will expose
         * 32-bit numbers as index values.
         */
        strcpy(curr->name, dev_name);
        if (wlen == 0) {
            // display char type in case of MultiByteToWideChar failure
            strncpy(curr->displayName, ifrowP->bDescr, ifrowP->dwDescrLen);
            curr->displayName[ifrowP->dwDescrLen] = '\0';
        } else {
            // call MultiByteToWideChar again to fill curr->displayName
            // it should not fail, because we have called it once before
            if (MultiByteToWideChar(CP_OEMCP, 0, ifrowP->bDescr,
                                    ifrowP->dwDescrLen, curr->displayName, wlen) == 0) {
                JNU_ThrowByName(env, "java/lang/Error",
                                "Cannot get multibyte char for interface display name");
                free_netif(netifP);
                free(tableP);
                free(curr->name);
                free(curr->displayName);
                free(curr);
                return -1;
            } else {
                curr->displayName[wlen*(sizeof(wchar_t))] = '\0';
                curr->dNameIsUnicode = TRUE;
            }
        }

        curr->dwIndex = ifrowP->dwIndex;
        curr->ifType = ifrowP->dwType;
        curr->index = GetFriendlyIfIndex(ifrowP->dwIndex);

        /*
         * Put the interface at tail of list as GetIfTable(,,TRUE) is
         * returning the interfaces in index order.
         */
        count++;
        if (netifP == NULL) {
            netifP = curr;
        } else {
            netif *tail = netifP;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = curr;
        }

        /* onto the next interface */
        ifrowP++;
    }

    /*
     * Free the interface table and return the interface list
     */
    if (tableP) {
        free(tableP);
    }
    *netifPP = netifP;
    return count;
}