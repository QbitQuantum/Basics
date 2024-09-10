bool MenuDialog::createSipPrefControl()
{
#ifdef WIN32_PLATFORM_PSPC
    return NULL != CreateWindow(TEXT("SIPPREF"), NULL, 0, -10, -10, 6, 6, handle(), NULL, GetInstance(), NULL);
#else
    return true;
#endif    
} 