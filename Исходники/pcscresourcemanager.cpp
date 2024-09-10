void PCSCResourceManager::run()
{
    SCARDCONTEXT context;
    LONG rv;

    while (true)
    {
        rv = SCardEstablishContext(SCARD_SCOPE_SYSTEM, NULL, NULL, &context);

        if (rv == SCARD_S_SUCCESS)
        {
            DWORD readerNum = SCARD_AUTOALLOCATE;
            LPSTR readerNames = NULL;

            do
            {
                rv = SCardListReaders(context, NULL, (LPSTR) &readerNames, &readerNum);

                if (rv == SCARD_S_SUCCESS)
                {
                    for (LPCSTR pch = readerNames; *pch != '\0'; pch += strlen(pch) + 1)
                    {
                        int i;
                        for (i = 0; i < m_availabeReaders.size(); i++)
                            if (0 == strcmp(m_availabeReaders[i]->name(), pch))
                                break;

                        if (i == m_availabeReaders.size())
                        {
                                SCardReader *reader = new SCardReader(pch);
                                m_availabeReaders.append(reader);
                                connect(reader, SIGNAL(unavailable(LPCSTR)), SLOT(clearUnavailabeReader(LPCSTR)));
                                reader->start();

                                emit readerPluged(reader);
                        }
                    }

                    (void) SCardFreeMemory(context, readerNames);
                }
                else
                    std::cout << pcsc_stringify_error(rv) << std::endl;

                if (rv == SCARD_S_SUCCESS || rv == SCARD_E_NO_READERS_AVAILABLE)
                {
                    SCARD_READERSTATE readerStates;

                    readerStates.szReader = "\\\\?PnP?\\Notification";
                    readerStates.dwCurrentState = SCARD_STATE_UNAWARE;

                    rv = SCardGetStatusChange(context, INFINITE, &readerStates, 1);

                    if (rv != SCARD_E_TIMEOUT || rv != SCARD_S_SUCCESS)
                    {
                        (void) SCardReleaseContext(context);
                        break;
                    }
                }
                else
                {
                    (void) SCardReleaseContext(context);
                    break;
                }
            } while (true);
        }
        else
        {
            std::cout << pcsc_stringify_error(rv) << std::endl;
            QThread::sleep(PCSC_ERROR_BREAK_TIME);
        }
    }
}