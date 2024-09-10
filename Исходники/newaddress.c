static void NewAddrUnpack(PrvAddrPackedDBRecord *src, AddrDBRecordPtr dest)
{
    Int16   				index;
    AddrDBRecordFlags 		flags;
    char 					*p;

    MemMove(&(dest->options), &(src->options), sizeof(AddrOptionsType));
    MemMove(&flags, &(src->flags), sizeof(AddrDBRecordFlags));
    p = &src->firstField;

    for (index = firstAddressField; index < addrNumStringFields; index++)
    {
        // If the flag is set, point to the string else NULL

        if (GetBitMacro(flags, index) != 0)
        {
            dest->fields[index] = p;
            p += StrLen(p) + 1;
        }
        else
            dest->fields[index] = NULL;
    }

    // Unpack birthday info
    MemSet(&(dest->birthdayInfo), sizeof(BirthdayInfo), 0 );

    if(GetBitMacro(flags, birthdayDate))
    {
        MemMove(&(dest->birthdayInfo.birthdayDate), p, sizeof(DateType));
        p += sizeof(DateType);
    }

    if(GetBitMacro(flags, birthdayMask))
    {
        MemMove(&(dest->birthdayInfo.birthdayMask), p, sizeof(AddressDBBirthdayFlags));
        //Dest->birthdayInfo.birthdayMask = *((AddressDBBirthdayFlags*)p);
        p += sizeof(AddressDBBirthdayFlags);
    }

    if(GetBitMacro(flags, birthdayPreset))
    {
        dest->birthdayInfo.birthdayPreset = *((UInt8*)p);
        p += sizeof(UInt8);
    }

    // Ignore the blob part - I don't use it
}