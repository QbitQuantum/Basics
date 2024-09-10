//---------------------------------------------------------------------------
bool File_DvbSubtitle::Synchronize()
{
    //Synchronizing
    if (MustFindDvbHeader)
    {
        while(Buffer_Offset+3<=Buffer_Size)
        {
            if (Buffer[Buffer_Offset]==0x20
             && Buffer[Buffer_Offset+1]==0x00
             && (Buffer[Buffer_Offset+2]==0x0F
              || Buffer[Buffer_Offset+1]==0xFF))
                break;
            Buffer_Offset++;
        }

        if (Buffer_Offset+3>Buffer_Size)
            return false;

        Accept();
    }
    else
    {
        while(Buffer_Offset<Buffer_Size)
        {
            if (Buffer[Buffer_Offset]==0x0F
             || Buffer[Buffer_Offset]==0xFF)
                break;
            Buffer_Offset++;
        }

        if (Buffer_Offset>=Buffer_Size)
            return false;
    }

    //Synched is OK
    Synched=true;
    return true;
}