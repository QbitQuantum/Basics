void
ServerScriptContext::EndJIT()
{
    InterlockedExchangeSubtract(&m_activeJITCount, 1);
}