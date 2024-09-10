void UnitTestProcessor::prependTabs()
{
    for (FdoInt32 i = 0; i < m_tabLevel; i++)
#ifdef _WIN32
        _putwch(L' ');
#else
	printf("%ls", L" ");
#endif
}