/****************************
TemporaryManager::GetNextTemporaryName -- gets next temp name (_t1, etc.)
*****************************/
STRING *
TemporaryManager::GetNextTemporaryName
(
    Vtypes TemporaryVtype,
    LifetimeClass Lifetime
)
{
    if (TemporaryVtype >= 0 && TemporaryVtype < _countof(m_CountOfTemporariesOfVtype))
    {
        StringBuffer NameBuffer;
        WCHAR CharacterBuffer[32];  // VS Everett security bug #515087

        NameBuffer.AppendString(VBTemporaryPrefix);

        if (m_ExtraPrefix)
        {
            NameBuffer.AppendString(m_ExtraPrefix);
            NameBuffer.AppendChar(L'$');
        }

        NameBuffer.AppendString(s_wszVOfVtype[TemporaryVtype]);
        NameBuffer.AppendChar(L'$');
        NameBuffer.AppendChar(
            (Lifetime == LifetimeLongLived) ? L'L' : (Lifetime == LifetimeShortLived) ? L'S' : L'N');

        _ultow_s(m_CountOfTemporariesOfVtype[TemporaryVtype]++, CharacterBuffer, _countof(CharacterBuffer), 10);
        NameBuffer.AppendString(CharacterBuffer);

        return m_Compiler->AddString(&NameBuffer);
    }

    return NULL;
}