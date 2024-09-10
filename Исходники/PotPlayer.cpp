BOOL NTAPI PpChooseFontW(LPCHOOSEFONTW Font)
{
    SET_FLAG(Font->Flags, 0x3000000);
    return ChooseFontW(Font);
}