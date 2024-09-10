void CT_cbGetOtherSeed()
{
    unsigned int eip=GetContextData(UE_EIP);
    DeleteBPX(eip);
    unsigned char reg_byte=0;
    if(!ReadProcessMemory(fdProcessInfo->hProcess, (void*)(eip+1), &reg_byte, 1, 0))
    {
        CT_FatalError(rpmerror());
        return;
    }
    CT_cert_data->decrypt_addvals[other_seed_counter]=GetContextData(CT_DetermineRegisterFromByte(reg_byte));
    other_seed_counter++;
    if(other_seed_counter==4)
    {
        other_seed_counter=0;
        if(!magic_value_addr)
            CT_RetrieveSaltValue();
    }
}