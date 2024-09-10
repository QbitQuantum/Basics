u8 MbcRomOnly::LoadRam(u16 addr)
{
    if (_rom.HasRam)
    {
        __debugbreak();
        return 0;
    }
    return 0;
}