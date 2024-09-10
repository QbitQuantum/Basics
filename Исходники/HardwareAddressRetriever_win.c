jbyteArray getHardwareAddress(JNIEnv* env, jstring ifName)
{
    MIB_IFTABLE* ifTable = NULL;
    ULONG size = 15000;
    int found = 0;
    jbyteArray hwaddr = NULL;
    DWORD ret = 0;
    DWORD i = 0;
    WCHAR* wname = NULL;
    MIB_IFROW ifi;
    jclass clazz = (*env)->GetObjectClass(env, ifName);
    jmethodID method = (*env)->GetMethodID(env, clazz, "compareTo", "(Ljava/lang/String;)I");

    if(method == NULL)
    {
        return NULL;
    }

    memset(&ifi, 0x00, sizeof(MIB_IFROW));

    do
    {
        ifTable = malloc(size);

        if(!ifTable)
        {
            /* out of memory */
            return NULL;
        }

        ret = GetIfTable(ifTable, &size, 1);

    }while(ret == ERROR_INSUFFICIENT_BUFFER);

    if(ret != ERROR_SUCCESS)
    {
        free(ifTable);
        return NULL;
    }

    for(i = 0 ; i < ifTable->dwNumEntries ; i++)
    {
        jstring tmp = NULL;
        ifi = ifTable->table[i];

        if(ifi.dwType == IF_TYPE_OTHER)
        {
            continue;
        }

        /* jstring created by NewStringUTF will be garbage collected at 
         * the end of the function 
         */
        tmp = (*env)->NewStringUTF(env, ifi.bDescr);

        if(!tmp)
        {
            /* printf("error\n"); */
            continue;
        }

        if((*env)->CallIntMethod(env, ifName, method, tmp) == 0)
        {
            found = 1;
            break;
        }
    }

    if(found)
    {
        DWORD hwlen = ifi.dwPhysAddrLen;

        if(hwlen > 0)
        {
            hwaddr = (*env)->NewByteArray(env, hwlen);

            if(hwaddr)
            {
                /* copy the hardware address and return it */
                (*env)->SetByteArrayRegion(env, hwaddr, 0, hwlen, ifi.bPhysAddr);
            }
        }
    }

    /* cleanup */
    free(ifTable);

    return hwaddr;
}