static void get_uuid(char *str)
{
#ifdef HAVE_WINDOWS_H
    UUID guid;
    UuidCreate(&guid);
    sprintf(str, "%08lX-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
	guid.Data1, guid.Data2, guid.Data3,
	guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
	guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
#elif defined(HAVE_CFUUIDCREATE)
    CFUUIDRef       myUUID;
    CFStringRef     myUUIDString;
    char            strBuffer[100];
    myUUID = CFUUIDCreate(kCFAllocatorDefault);
    myUUIDString = CFUUIDCreateString(kCFAllocatorDefault, myUUID);/* This is the safest way to obtain a C string from a CFString.*/
    CFStringGetCString(myUUIDString, str, SMPD_MAX_DBS_NAME_LEN, kCFStringEncodingASCII);
    CFRelease(myUUIDString);
#elif defined(HAVE_UUID_GENERATE)
    uuid_t guid;
    uuid_generate(guid);
    uuid_unparse(guid, str);
#else
    sprintf(str, "%X%X%X%X", rand(), rand(), rand(), rand());
#endif
}