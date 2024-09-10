void HashFunctions()
{
    for (vector<Function>::iterator iter = functions.begin(); iter!=functions.end(); iter++)
    {
        Function &f=*iter;
        u32 hash = 0x1337babe;
        for (u32 addr = f.start; addr <= f.end; addr++)
        {
            u32 validbits = 0xFFFFFFFF;
            u32 instr = Memory::Read_Instruction(addr);
            u32 flags = MIPSGetInfo(instr);
            if (flags & IN_IMM16)
                validbits&=~0xFFFF;
            if (flags & IN_IMM26)
                validbits&=~0x3FFFFFF;
            hash = _rotl(hash,13);
            hash ^= (instr&validbits);
        }
        f.hash=hash;
        f.hasHash=true;
    }
}